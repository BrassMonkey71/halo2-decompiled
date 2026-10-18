// @flags /O2 /GL-
// Havok (third-party physics library): whether a body is active: false when
// it is in no group, else the group's flag at +0x29.

class hkBool
{
public:
	hkBool() {}

	char m_bool;
};

struct group_30bc40
{
	char unknown0[0x29];
	char active;
};

class hkRigidBody
{
public:
	char unknown0[0x44];
	group_30bc40 *group;

	hkBool isActive(void) const;
};

// @retail 0x30bc40
hkBool hkRigidBody::isActive(void) const
{
	hkBool result;
	if (group == 0)
	{
		result.m_bool = false;
		return result;
	}
	result.m_bool = group->active;
	return result;
}
