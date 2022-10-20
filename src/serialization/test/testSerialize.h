#pragma once

#include "../../serialization.h"

namespace TestFrame
{
	inline void Test()
	{
		const int tableSize = 100;
		HashTable::Hashtable<std::string, std::string, tableSize> Hashtable;
		std::vector<HashTable::User<std::string, std::string>> Users;

		int k = 0;
		for (;;)
		{
			std::cout << "Enter the command: 1)Add 2)Delete 3)Print 4)Exit";
			std::cin >> k;
			std::cout << std::endl;

			switch (k)
			{
			case 1:
			{
				std::string login, password;

				std::cout << "Enter Login: ";
				std::cin >> login;
				std::cout << "Enter Password: ";
				std::cin >> password;

				Hashtable.Put(login, password);
			} break;
			case 2:
			{
				std::string login, password;

				std::cout << "Enter Login: ";
				std::cin >> login;
				std::cout << "Enter Password: ";
				std::cin >> password;

				Hashtable.Remove(login, password);
			} break;
			
			case 3: std::cout << Hashtable; break;
			case 4: exit(0);
			}
		}
	}
}