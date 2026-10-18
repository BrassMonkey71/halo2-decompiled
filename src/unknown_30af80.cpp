// @flags /O2 /GL-
// Havok (third-party physics library): telling every listener, from the
// last, about an event.

class class_30af80;

struct s_30af80_event
{
	class_30af80 *source;
	long value;
	bool flag;
};

class class_30af80_listener
{
public:
	virtual void slot0() = 0;
	virtual void notify(s_30af80_event *event) = 0;
};

class class_30af80
{
public:
	char unknown0[0x3c];
	class_30af80_listener **listeners;
	int listener_count;

	void function_30af80(long value, bool flag);
};

// @retail 0x30af80
void class_30af80::function_30af80(long value, bool flag)
{
	s_30af80_event event;
	event.value = value;
	event.source = this;
	event.flag = flag;
	for (int i = listener_count - 1; i >= 0; i--)
	{
		class_30af80_listener *listener = listeners[i];
		if (listener)
		{
			listener->notify(&event);
		}
	}
}
