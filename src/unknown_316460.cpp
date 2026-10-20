// @flags /O2 /GL-
// Havok (third-party physics library): searching for the time at which two
// moving bodies first come within a tolerance. Both bodies are moved to a
// common time and their contacts collected again; the time is then halved
// back and forth until the step falls below the world's smallest step. When
// no time leaves them clear, the pair is marked and its contacts are
// collected once more with a very low tolerance. (Its own file, not
// src/unknown_3169c0.cpp beside it.)
#include <math.h>

// a body's motion: its time, and the slot that moves it to another time
class motion_316460
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void slot_4() {}
	virtual void slot_5() {}
	virtual void slot_6() {}
	virtual void slot_7() {}
	virtual void slot_8() {}
	virtual void slot_9() {}
	virtual void slot_10() {}
	virtual void slot_11() {}
	virtual void slot_12() {}
	virtual void slot_13() {}
	virtual void slot_14() {}
	virtual void slot_15() {}
	virtual void slot_16() {}
	virtual void slot_17() {}
	virtual void slot_18() {}
	virtual void slot_19() {}
	virtual void slot_20() {}
	virtual void slot_21() {}
	virtual void slot_22() {}
	virtual void slot_23() {}
	virtual void slot_24() {}
	virtual void slot_25() {}
	virtual void slot_26() {}
	virtual void slot_27() {}
	virtual void slot_28() {}
	virtual void move_to_time(float time, long context) {}

	char unknown04[0x78];
	float time;
};

struct body_316460
{
	char unknown00[0x3c];
	motion_316460 *motion;
};

// a pair's member: its body, 0x10 bytes into the object the collector takes
struct member_316460
{
	char unknown00[0x10];
	body_316460 *body;
};

struct input_316460
{
	char unknown00[0x10];
	long context;
};

struct contact_316460
{
	char unknown00[0xc];
	float distance;
	char unknown10[0x20];
};

struct contacts_316460
{
	contact_316460 *data;
	long size;
};

struct output_316460
{
	contacts_316460 *contacts;
};

// collects a pair's contacts
class collector_316460
{
public:
	virtual void slot_0() {}
	virtual void slot_1() {}
	virtual void slot_2() {}
	virtual void slot_3() {}
	virtual void collect(void *first, void *second, input_316460 *input, output_316460 *output) {}
};

struct pair_316460
{
	member_316460 *first;
	member_316460 *second;
	collector_316460 *collector;
	long result;
};

struct search_state_316460
{
	char unknown00[0xc];
	long mode;
	float tolerance;
};

struct world_316460
{
	char unknown00[0x24c];
	float smallest_step;
	char unknown250[4];
	search_state_316460 *state;
};

class time_search_316460
{
public:
	void function_316460(input_316460 *input, pair_316460 *pair, output_316460 *output, float tolerance);

	// 0: a contact is within the tolerance (or the search was stopped);
	// 1: all contacts are clear; 2: there are none
	__forceinline long classify(output_316460 const *output, float tolerance)
	{
		if (world->state->mode == 0)
		{
			return 0;
		}
		long result = 2;
		for (long index = 0; index < output->contacts->size; index++)
		{
			if (output->contacts->data[index].distance < tolerance)
			{
				return 0;
			}
			result = 1;
		}
		return result;
	}

	char unknown00[0x20];
	world_316460 *world;
};

// @retail 0x316460
void time_search_316460::function_316460(input_316460 *input, pair_316460 *pair, output_316460 *output, float tolerance)
{
	motion_316460 *first = pair->first->body->motion;
	motion_316460 *second = pair->second->body->motion;
	float const first_time = first->time;
	float const second_time = second->time;
	float const earliest = first_time < second_time ? first_time : second_time;
	if (first_time != second_time)
	{
		motion_316460 *later = first_time > second_time ? first : second;
		later->move_to_time(earliest, input->context);
		output->contacts->size = 0;
		world->state->mode = 2;
		world->state->tolerance = tolerance;
		pair->collector->collect((char *)pair->first - 0x10, (char *)pair->second - 0x10, input, output);
		switch (classify(output, tolerance))
		{
		case 1:
			return;
		case 2:
			{
				float step = (float)fabs(first_time - second_time) * 0.5f;
				float time = earliest + step;
				while (step > world->smallest_step)
				{
					later->move_to_time(time, input->context);
					output->contacts->size = 0;
					world->state->mode = 2;
					world->state->tolerance = tolerance;
					pair->collector->collect((char *)pair->first - 0x10, (char *)pair->second - 0x10, input, output);
					switch (classify(output, tolerance))
					{
					case 0:
						step *= 0.5f;
						time -= step;
						break;
					case 1:
						return;
					case 2:
						step *= 0.5f;
						time += step;
						break;
					}
				}
				if (classify(output, tolerance) == 0)
				{
					later->move_to_time(earliest, input->context);
					pair->result = -3;
					output->contacts->size = 0;
					world->state->mode = 2;
					world->state->tolerance = -1000.0f;
					pair->collector->collect((char *)pair->first - 0x10, (char *)pair->second - 0x10, input, output);
					return;
				}
			}
			break;
		}
	}
	float time = (first->time < second->time ? first->time : second->time) * 0.5f;
	float step = time;
	while (step > world->smallest_step)
	{
		first->move_to_time(time, input->context);
		second->move_to_time(time, input->context);
		world->state->mode = 2;
		world->state->tolerance = tolerance;
		output->contacts->size = 0;
		pair->collector->collect((char *)pair->first - 0x10, (char *)pair->second - 0x10, input, output);
		switch (classify(output, tolerance))
		{
		case 0:
			step *= 0.5f;
			time -= step;
			break;
		case 1:
			return;
		case 2:
			step *= 0.5f;
			time = step + time;
			break;
		}
	}
	if (step <= world->smallest_step)
	{
		if (classify(output, tolerance) == 0)
		{
			pair->result = -3;
			first->move_to_time(first_time, input->context);
			second->move_to_time(second_time, input->context);
			world->state->tolerance = -1000.0f;
			output->contacts->size = 0;
			pair->collector->collect((char *)pair->first - 0x10, (char *)pair->second - 0x10, input, output);
		}
	}
}
