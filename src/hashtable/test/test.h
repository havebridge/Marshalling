#pragma once

#include "../hashtable.h"


namespace Test
{
	template<typename T, typename U, int tableSize>
	bool isGoodHashTest()
	{
		HashTable::Hashtable<T, U, tableSize> foo;
		std::vector<std::string> same;

		const int num = tableSize * 2;

		for (int i = 0; i != num; ++i)
		{
			same.push_back(to_string(foo.hashTest()));
		}


		int k = 0;
		for (int i = 1; i < num; ++i)
		{
			k = 1;
			for (int j = 0; j < i; ++j)
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


	template<typename T, typename U, int tableSize>
	std::vector<HashTable::User<T, U>> PutTest(HashTable::Hashtable<T, U, tableSize>& foo)
	{
		const std::string Characters = " abcd";

		std::vector<HashTable::User<T, U>> u;

		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<std::mt19937::result_type> distribution(1, Characters.size() - 1);

		T login_put;
		U password_put;

		for (int i = 0; i != tableSize * 2; ++i)
		{
			HashTable::User<T, U> user;

			int number = distribution(generator);

			for (int j = 0; j != number; ++j)
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



	template<typename T, typename U, int tableSize>
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


	template<typename T, typename U, int tableSize>
	bool GetTest(const HashTable::Hashtable<T, U, tableSize>& entity)
	{
		bool isFound = false;

		HashTable::User<T, U> user;

		std::cin >> user;
	
		for (int slot = 0; slot != tableSize; ++slot)
		{
			HashTable::User<T, U>* tmp = entity.ht[slot];				//TODO: doesn`t work with the private data(hashtable)

			while (tmp != nullptr)
			{
				if (tmp->getLogin() == user.getLogin() && tmp->getPassword() == user.getPassword())
				{
					isFound = true;
					break;
				}

				tmp = tmp->getNext();
			}
		}

		return isFound;
	}
}