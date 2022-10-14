#include "../serialization.h"


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	
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
#endif
	return 0;
}