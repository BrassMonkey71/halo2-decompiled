// @flags /O2 /GL-
// Havok (third-party physics library): a three-axis sweep of boxes
// (axis_sweep_2e1090.h): moving boxes to new bounds, endpoint by endpoint
// along each axis, and listing the pairs that start and stop overlapping.
#include "axis_sweep_2e1090.h"

// whether two boxes' y and z intervals overlap (the slots hold the lower y
// and z, then the upper y and z, as two pairs of words)
__forceinline bool overlap_yz_2e0350(element_2e1090 const *box, element_2e1090 const *other)
{
	unsigned long const *box_pairs = (unsigned long const *)box->slots;
	unsigned long const *other_pairs = (unsigned long const *)other->slots;
	return (((other_pairs[1] - box_pairs[0]) | (box_pairs[1] - other_pairs[0])) & 0x80008000) == 0;
}

// whether two boxes' z and x intervals overlap
__forceinline bool overlap_zx_2e0350(element_2e1090 const *box, element_2e1090 const *other)
{
	return (((unsigned short)(box->slots[3] - other->slots[1]) | (unsigned short)(other->slots[3] - box->slots[1])
		| (unsigned short)(box->slots[5] - other->slots[4]) | (unsigned short)(other->slots[5] - box->slots[4])) & 0x8000) == 0;
}

// whether two boxes' x and y intervals overlap
__forceinline bool overlap_xy_2e0350(element_2e1090 const *box, element_2e1090 const *other)
{
	return (((unsigned short)(other->slots[5] - box->slots[4]) | (unsigned short)(box->slots[5] - other->slots[4])
		| (unsigned short)(other->slots[2] - box->slots[0]) | (unsigned short)(box->slots[2] - other->slots[0])) & 0x8000) == 0;
}

__forceinline bool overlap_2e0350(int axis, element_2e1090 const *box, element_2e1090 const *other)
{
	if (axis == 0)
	{
		return overlap_yz_2e0350(box, other);
	}
	if (axis == 1)
	{
		return overlap_zx_2e0350(box, other);
	}
	return overlap_xy_2e0350(box, other);
}

// a pair that starts or stops overlapping
__forceinline void add_pair_2e0350(pairs_2e1090 *pairs, element_2e1090 const *box, element_2e1090 const *other)
{
	pair_2e1090 &pair = pairs->next_slot();
	pair.first = (long *)box->owner;
	pair.second = other->owner;
}

// where `value` sits in the cell's list of boxes, or -1
__forceinline long find_box_2e0350(cell_2e1090 const *cell, unsigned short value)
{
	for (long position = 0; position < cell->boxes.size; position++)
	{
		if (cell->boxes.data[position] == value)
		{
			return position;
		}
	}
	return -1;
}

// a box's endpoints on one axis moved to their new values: each endpoint
// passed moves one slot over, and when a box's interval starts (or stops)
// overlapping on this axis while the other two overlap already, the pair is
// added (or removed); on the x axis a grid cell's box instead gains (or
// loses) the box
__forceinline void move_on_axis_2e0350(class_2e1090 *sweep, element_2e1090 *elements, int axis, element_2e1090 *box, unsigned short id,
	int low_slot, int high_slot, long low, long high, pairs_2e1090 *added, pairs_2e1090 *removed)
{
	// the lower end moves down
	{
		unsigned long position = box->slots[low_slot];
		endpoint_2e0f80 *endpoint = &sweep->axes[axis].data[position];
		for (;;)
		{
			unsigned long const value = endpoint[-1].value;
			if (low >= (long)value)
			{
				break;
			}
			unsigned short const other_id = endpoint[-1].id;
			element_2e1090 *const other = &elements[other_id];
			endpoint->value = (unsigned short)value;
			endpoint->id = other_id;
			if (value & 1)
			{
				other->slots[high_slot] = (unsigned short)position;
				if (overlap_2e0350(axis, box, other))
				{
					if (axis != 0 || (other->owner & 1) == 0)
					{
						add_pair_2e0350(added, box, other);
					}
					else
					{
						((cell_2e1090 *)((char *)sweep->cells + (other->owner & ~1)))->boxes.append(id);
					}
				}
			}
			else
			{
				other->slots[low_slot] = (unsigned short)position;
			}
			endpoint--;
			position--;
			endpoint->id = id;
			box->slots[low_slot] = (unsigned short)position;
		}
		endpoint->value = (unsigned short)low;
	}
	// the upper end moves up
	{
		endpoint_2e0f80 *next = &sweep->axes[axis].data[box->slots[high_slot]] + 1;
		for (;;)
		{
			unsigned long const value = next->value;
			if (high <= (long)value)
			{
				break;
			}
			box->slots[high_slot]++;
			element_2e1090 *const other = &elements[next->id];
			next[-1] = next[0];
			next->id = id;
			if (value & 1)
			{
				other->slots[high_slot]--;
			}
			else
			{
				other->slots[low_slot]--;
				if (overlap_2e0350(axis, box, other))
				{
					if (axis != 0 || (other->owner & 1) == 0)
					{
						add_pair_2e0350(added, box, other);
					}
					else
					{
						((cell_2e1090 *)((char *)sweep->cells + (other->owner & ~1)))->boxes.append(id);
					}
				}
			}
			next++;
		}
	}
	// the upper end moves down
	{
		endpoint_2e0f80 *endpoint = &sweep->axes[axis].data[box->slots[high_slot]];
		for (;;)
		{
			unsigned long const value = endpoint[-1].value;
			if (high >= (long)value)
			{
				break;
			}
			endpoint--;
			box->slots[high_slot]--;
			element_2e1090 *const other = &elements[endpoint->id];
			endpoint[1] = endpoint[0];
			endpoint->id = id;
			if (value & 1)
			{
				other->slots[high_slot]++;
			}
			else
			{
				other->slots[low_slot]++;
				if (overlap_2e0350(axis, box, other))
				{
					if (axis != 0 || (other->owner & 1) == 0)
					{
						add_pair_2e0350(removed, box, other);
					}
					else
					{
						cell_2e1090 *const cell = (cell_2e1090 *)((char *)sweep->cells + (other->owner & ~1));
						long const found = find_box_2e0350(cell, id);
						cell->boxes.size--;
						cell->boxes.data[found] = cell->boxes.data[cell->boxes.size];
					}
				}
			}
		}
		endpoint->value = (unsigned short)high;
	}
	// the lower end moves up
	{
		endpoint_2e0f80 *endpoint = &sweep->axes[axis].data[box->slots[low_slot]];
		for (;;)
		{
			unsigned long const value = endpoint[1].value;
			if (low <= (long)value)
			{
				break;
			}
			endpoint++;
			box->slots[low_slot]++;
			element_2e1090 *const other = &elements[endpoint->id];
			endpoint[-1] = endpoint[0];
			endpoint->id = id;
			if (value & 1)
			{
				other->slots[high_slot]--;
				if (overlap_2e0350(axis, box, other))
				{
					if (axis != 0 || (other->owner & 1) == 0)
					{
						add_pair_2e0350(removed, box, other);
					}
					else
					{
						cell_2e1090 *const cell = (cell_2e1090 *)((char *)sweep->cells + (other->owner & ~1));
						long const found = find_box_2e0350(cell, id);
						cell->boxes.size--;
						cell->boxes.data[found] = cell->boxes.data[cell->boxes.size];
					}
				}
			}
			else
			{
				other->slots[low_slot]--;
			}
		}
		endpoint->value = (unsigned short)low;
	}
}

// moves each box to its new bounds, adding the pairs that start overlapping
// to `added` and those that stop to `removed`
// Near miss: 3188 against 3107 bytes, the same twelve endpoint walks in the
// same order; the first difference is at +0xd, where retail keeps `this` at
// the bottom of the frame. Retail also keeps the box's id in a slot of its
// own and the walk's position in ecx, so the registers differ through the
// walks, and it reads the cells pointer before testing an owner's low bit.
// @retail 0x2e0350
void class_2e1090::function_2e0350(long *const *owners, bounds_2e0020 const *bounds, long count, pairs_2e1090 *added, pairs_2e1090 *removed)
{
	for (long *const *owner = owners; owner < owners + count; owner++, bounds++)
	{
		long low[3];
		long high[3];
		{
			union
			{
				__m128 vector;
				unsigned long bits[4];
			} quantized, quantized_upper;
			unsigned short low_words[3];
			__m128 const ceiling = *(__m128 const *)g_4125d0;
			__m128 const floor = *(__m128 const *)g_4125e0;
			__m128 const bias = *(__m128 const *)g_4125c0;
			quantized.vector = _mm_add_ps(_mm_max_ps(_mm_min_ps(
				_mm_mul_ps(_mm_add_ps(bounds->lower, lower_offset), scale), ceiling), floor), bias);
			low_words[0] = (unsigned short)(quantized.bits[0] >> 7);
			low_words[1] = (unsigned short)(quantized.bits[1] >> 7);
			low_words[2] = (unsigned short)(quantized.bits[2] >> 7);
			quantized_upper.vector = _mm_add_ps(_mm_max_ps(_mm_min_ps(
				_mm_mul_ps(_mm_add_ps(bounds->upper, upper_offset), scale), ceiling), floor), bias);
			high[0] = (unsigned short)(quantized_upper.bits[0] >> 7) | 1;
			high[1] = (unsigned short)(quantized_upper.bits[1] >> 7) | 1;
			high[2] = (unsigned short)(quantized_upper.bits[2] >> 7) | 1;
			low[0] = low_words[0] & 0xfffe;
			low[1] = low_words[1] & 0xfffe;
			low[2] = low_words[2] & 0xfffe;
		}
		long const index = **owner;
		element_2e1090 *const data = elements.data;
		element_2e1090 *const box = &data[index];
		move_on_axis_2e0350(this, data, 0, box, (unsigned short)index, 4, 5, low[0], high[0], added, removed);
		move_on_axis_2e0350(this, data, 1, box, (unsigned short)index, 0, 2, low[1], high[1], added, removed);
		move_on_axis_2e0350(this, data, 2, box, (unsigned short)index, 1, 3, low[2], high[2], added, removed);
	}
}
