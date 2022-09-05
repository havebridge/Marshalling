#include "../serialization.h"


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

#if 1
	assert(Core::Util::isLittleEndian());

	TestFrame::testPrimitive();
	TestFrame::testArray();
	TestFrame::testString();


	TestFrame::testObject();
#endif
	


#if 0
	const uint8_t tableSize = 10;
	HashTable::Hashtable<std::string, std::string, tableSize> Hashtable;
	std::vector<HashTable::User<std::string, std::string>> Users;

#if TEST_PUT
	Users = Test::PutTest<std::string, std::string, tableSize>(Hashtable);
#endif

#if TEST_HASH
	std::cout << Test::isGoodHashTest<std::string, std::string, tableSize>();
#endif


#if TEST_REMOVE
	Test::RemoveTest<std::string, std::string, tableSize>(Hashtable, Users);
#endif

#if TEST_PRINT
	std::cout << Hashtable;
#endif

#if TEST_GET
	//TODO:
#endif

#if TEST_SERIALIZE
	Hashtable.Serialize();
#endif


#endif

	return 0;
}