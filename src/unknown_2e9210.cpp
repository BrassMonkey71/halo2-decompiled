// @flags /O2 /GL-
// Havok (third-party physics library): bringing the objects kept for a
// wrapped collection's children up to date, with the two sides the other way
// round: a new object for each newly accepted child, the kept object told
// about each child still accepted, and the object of each child no longer
// accepted let go and replaced by the empty one.
#include "bounded_2e9530.h"
#include "child_refresh_2e9210.h"

// @retail 0x2e9210
void bounded_2e9530::function_2e9210(typed_2e9210 **other, description_2e9210 const *description, context_2e9210 const *context)
{
	child_buffer_2e9210 buffer;
	child_description_2e9210 child;
	collection_2e9210 const *shape = (collection_2e9210 const *)description->shape->inner;
	for (long i = 0; i < elements.size; i++)
	{
		typed_2e9210 const *element_part = shape->child(elements.data[i].value_0, &buffer);
		child.parent = description;
		child.field_8 = description->field_8;
		child.index = elements.data[i].value_0;
		child.key = (long)element_part;
		if (context->filter->accept(context, other, description, shape, elements.data[i].value_0).value)
		{
			kept_child_2e9210 *agent = (kept_child_2e9210 *)elements.data[i].value_8;
			if ((object_4805a4 *)agent == function_301a40())
			{
				long arg_3 = value;
				dispatcher_2e9210 *table = context->dispatcher;
				long first = (*other)->type();
				long second = ((typed_2e9210 *)child.key)->type();
				handler_2e9210 handler = table->handlers[first][second];
				elements.data[i].value_8 = handler(other, &child, context, arg_3);
			}
			else
			{
				agent->refresh(other, &child, context);
			}
		}
		else if ((object_4805a4 *)elements.data[i].value_8 != function_301a40())
		{
			((kept_child_2e9210 *)elements.data[i].value_8)->release();
			elements.data[i].value_8 = (long)function_301a40();
		}
	}
}
