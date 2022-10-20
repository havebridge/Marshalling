#include "../serialization.h"


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	
#if DEBUG
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
	std::cout << Hashtable;
	Test::RemoveTest<std::string, std::string, tableSize>(Hashtable, Users);
	std::cout << std::endl;
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

#if TEST_DESERIALIZE
	uint8_t a = 25;
	std::unique_ptr<ObjectModel::Primitive> p = ObjectModel::Primitive::createPrimitive("pidor", ObjectModel::Type::U8, a);
	Core::Utility::saveAll(p.get());

	std::vector<uint8_t> tests = Core::Utility::load("Data/pidor.hsbrdg");
	ObjectModel::Primitive pp = ObjectModel::Primitive::unpack(tests);

#endif

#endif


#if RELEASE
	TestFrame::Test();
#endif

	return 0;
}