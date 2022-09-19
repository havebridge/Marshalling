#include "../serialization.h"


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

#if 0
	uint8_t foo = 5;

	ObjectModel::Primitive* p = ObjectModel::Primitive::createPrimitive("foo", ObjectModel::Type::U8, foo);

	Core::Utility::saveAll(p);


	std::string name = "hyesos";

	ObjectModel::Array* p1 = ObjectModel::Array::createString("n", ObjectModel::Type::U8, name);

	Core::Utility::saveAll(p1);

	ObjectModel::Object object("object");

	object.addEntitie(p);
	object.addEntitie(p1);

	Core::Utility::saveAll(&object);
#endif

#if 0
	assert(Core::Utility::isLittleEndian());

	TestFrame::testPrimitive();
	TestFrame::testArray();
	TestFrame::testString();


	TestFrame::testObject();
#endif
	
#if 1
	const int tableSize = 100;
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
	std::cout << Test::GetTest<std::string, std::string, tableSize>(Hashtable);
#endif

#if TEST_SERIALIZE
	Hashtable.Serialize();
#endif


#endif

	return 0;
}