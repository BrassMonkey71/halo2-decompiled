// @flags /O2 /GL-
// Havok (third-party physics library): adding a contact for a feature of a
// pair of objects to the pair's table of at most eight: skipped when a kept
// contact already lies within the pair's radius of the feature's point; the
// contact made by the kind of feature; dropped again when it faces against the
// one before it, or when no id is handed out for it.
#include <xmmintrin.h>
#include "growable_array_2d91d0.h"

struct transform_305f60
{
	__m128 rotation[3];
	__m128 translation;
};

// a point placed by a transform
inline __m128 transform_305f60_apply(transform_305f60 const *transform, __m128 const &p)
{
	__m128 z = _mm_add_ps(_mm_mul_ps(transform->rotation[2], _mm_shuffle_ps(p, p, 0xaa)), transform->translation);
	__m128 y = _mm_mul_ps(transform->rotation[1], _mm_shuffle_ps(p, p, 0x55));
	__m128 x = _mm_mul_ps(transform->rotation[0], _mm_shuffle_ps(p, p, 0x00));
	return _mm_add_ps(_mm_add_ps(x, y), z);
}

// a feature's points on the two objects, and its kind
struct feature_305f60
{
	__m128 first_point;
	__m128 second_point;
	char unknown20[0x38 - 0x20];
	unsigned short kind;
};

struct key_305f60
{
	unsigned short index;
	unsigned short field_2;
	unsigned short id;
};

struct contact_305f60
{
	__m128 point;
	__m128 normal;
	unsigned short id;
};

ELEMENTS_2D91D0_ALIGNED(contacts_305f60, contact_305f60);

struct entry_305f60
{
	unsigned short first;
	unsigned short second;
	unsigned short id;
};

class table_305f60
{
public:
	char unknown0[0x20];
	entry_305f60 entries[8];
	long field_50;
	int count;

};

struct s_3058b0_entry;

class class_3058b0
{
public:
	int function_308200(long arg_0, long arg_1, const s_3058b0_entry *entry);
};

class class_308180
{
public:
	void remove(int index, long a, long b);
};

class owner_305f60
{
public:
	virtual void slot_0() {}
	virtual unsigned short add_contact(long first, long second, long arg_2, contact_305f60 *contact) { return 0; }
};

struct contact_305ca0;
struct key_305ca0;
struct feature_305ca0;
struct contact_305e10;
struct key_305e10;
struct feature_305e10;
struct contact_305eb0;
struct key_305eb0;
struct feature_305eb0;

class pair_305ca0
{
public:
	void function_305ca0(contact_305ca0 *out, key_305ca0 const *key, feature_305ca0 const *feature) const;
};

class pair_305e10
{
public:
	void function_305e10(contact_305e10 *out, key_305e10 const *key, feature_305e10 const *feature) const;
};

class pair_305eb0
{
public:
	void function_305eb0(contact_305eb0 *out, key_305eb0 const *key, feature_305eb0 const *feature) const;
};

class pair_305f60
{
public:
	long field_0;
	long field_4;
	long field_8;
	owner_305f60 *owner;
	contacts_305f60 **contacts;
	transform_305f60 const *first_transform;
	transform_305f60 const *second_transform;
	char unknown1c[0x60 - 0x1c];
	float radius;

	void function_305f60(table_305f60 *table, feature_305f60 const *feature, key_305f60 *key);
};

// @retail 0x305f60
void pair_305f60::function_305f60(table_305f60 *table, feature_305f60 const *feature, key_305f60 *key)
{
	if (key->index <= 5)
	{
		transform_305f60 const *transform;
		__m128 local;
		if (key->index <= 2)
		{
			transform = second_transform;
			local = feature->second_point;
		}
		else
		{
			transform = first_transform;
			local = feature->first_point;
		}
		__m128 point = transform_305f60_apply(transform, local);
		for (int i = 0; i < table->count; i++)
		{
			if (table->entries[i].first <= 5)
			{
				__m128 offset = _mm_sub_ps(point, (*contacts)->data[i].point);
				__m128 squares = _mm_mul_ps(offset, offset);
				float distance_squared;
				_mm_store_ss(&distance_squared, _mm_add_ss(_mm_shuffle_ps(squares, squares, 0xaa), _mm_add_ss(_mm_shuffle_ps(squares, squares, 0x55), squares)));
				if (distance_squared <= radius * radius + 1.192092896e-07f)
				{
					return;
				}
			}
		}
	}
	if (table->count >= 8)
	{
		return;
	}
	int index = ((class_3058b0 *)table)->function_308200(field_0, field_4, (s_3058b0_entry const *)key);
	if (index < 0)
	{
		return;
	}
	contact_305f60 *contact = &(*contacts)->next_slot();
	int kind = feature->kind;
	if (kind <= 2)
	{
		((pair_305ca0 const *)this)->function_305ca0((contact_305ca0 *)contact, (key_305ca0 const *)key, (feature_305ca0 const *)feature);
	}
	else if (kind <= 5)
	{
		((pair_305e10 const *)this)->function_305e10((contact_305e10 *)contact, (key_305e10 const *)key, (feature_305e10 const *)feature);
	}
	else
	{
		((pair_305eb0 const *)this)->function_305eb0((contact_305eb0 *)contact, (key_305eb0 const *)key, (feature_305eb0 const *)feature);
	}
	if (table->count > 1)
	{
		contacts_305f60 *list = *contacts;
		__m128 products = _mm_mul_ps(list->data[list->size - 2].normal, contact->normal);
		float dot;
		_mm_store_ss(&dot, _mm_add_ss(_mm_shuffle_ps(products, products, 0xaa), _mm_add_ss(_mm_shuffle_ps(products, products, 0x55), products)));
		if (dot <= 0.0f)
		{
			(*contacts)->size--;
			((class_308180 *)table)->remove(index, field_0, field_4);
			return;
		}
	}
	unsigned short id = owner->add_contact(field_0, field_4, field_8, contact);
	table->entries[index].id = id;
	if (id == 0xffff)
	{
		(*contacts)->size--;
		((class_308180 *)table)->remove(index, field_0, field_4);
		return;
	}
	key->id = id;
	contact->id = table->entries[index].id;
	if (key->index <= 5)
	{
		table->field_50++;
	}
}
