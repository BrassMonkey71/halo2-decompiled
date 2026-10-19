// @flags /O2 /GL-
// Havok (third-party physics library): two steps run on a member with the
// owner's flag at +0x12c set, then put back as it was.

struct member_30c8e0;

class owner_30c8e0
{
public:
	char unknown0[0x12c];
	char flag_12c;

	void function_30c8e0(member_30c8e0 *member);
	void function_30df80(member_30c8e0 *member);
	void function_30f340(member_30c8e0 *member);
};

// @retail 0x30f340
void owner_30c8e0::function_30f340(member_30c8e0 *member)
{
	int flag = flag_12c;
	flag_12c = 1;
	function_30c8e0(member);
	function_30df80(member);
	flag_12c = flag;
}
