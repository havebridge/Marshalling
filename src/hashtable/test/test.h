#include "../hashtable.h"


namespace Test
{
	template<typename T, typename U, uint8_t tableSize>
	bool isGoodHashTest()
	{
		HashTable::Hashtable<T, U, tableSize> foo;
		std::vector<std::string> same;

		const uint8_t num = tableSize * 2;

		for (uint8_t i = 0; i != num; ++i)
		{
			same.push_back(to_string(foo.hashTest()));
		}


		uint8_t k = 0;
		for (uint8_t i = 1; i < num; ++i)
		{
			k = 1;
			for (uint8_t j = 0; j < i; ++j)
			{
				if (same.at(i) == same.at(j))
				{
					k++;
				}
			}
		}

		if (k >= num - (num / 2))
		{
			return false;
		}

		return true;
	}


	template<typename T, typename U, uint8_t tableSize>
	std::vector<HashTable::User<T, U>> PutTest(HashTable::Hashtable<T, U, tableSize>& foo)
	{
		const std::string Characters = " ab";

		std::vector<HashTable::User<T, U>> u;

		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<std::mt19937::result_type> distribution(1, Characters.size() - 1);

		T login_put;
		U password_put;

		for (uint16_t i = 0; i != tableSize * 2; ++i)
		{
			HashTable::User<T, U> user;

			uint8_t number = distribution(generator);

			for (uint8_t j = 0; j != number; ++j)
			{
				login_put += Characters[distribution(generator)];
				password_put += Characters[distribution(generator)];
			}

			foo.Put(login_put, password_put);

			user.setLogin(login_put);
			user.setPassword(password_put);

			u.push_back(user);

			login_put = "";
			password_put = "";
		}

		return u;
	}



	template<typename T, typename U, uint8_t tableSize>
	void RemoveTest(HashTable::Hashtable<T, U, tableSize>& foo, std::vector<HashTable::User<std::string, std::string>> Users)
	{
		int i = 1;
		std::cout << "Users to delete: " << '\n';
		for (auto it : Users)
		{
			std::cout << i++ << ')' << it.getLogin() << ' ' << it.getPassword() << '\n';
		}
		std::cout << std::endl;

		std::string login_remove, password_remove;
		std::cin >> login_remove >> password_remove;

		foo.Remove(login_remove, password_remove);
	}


	template<typename T, typename U, uint8_t tableSize>
	bool GetTest(HashTable::Hashtable<T, U, tableSize>& foo, const T& Login, const U& Password)
	{
		//TODO:
	}
}