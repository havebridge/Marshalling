#pragma once

#include <random>
#include <cstring>

#include "../serialization/object.h"
#include "../serialization/array.h"
#include "../serialization/primitive.h"


namespace HashTable
{
	template<typename T, typename U>
	class User
	{
	private:
		T login;
		U password;
		User* next ;
		bool isSerialized;
		bool isNext;
	public:
		template<typename T, typename U>
		friend std::istream& operator>>(std::istream& stream, User<T, U>& User);

		T getLogin() const { return login; }
		U getPassword() const { return password; }
		User* getNext() const { return next; }
		bool getIsSerialized() const { return isSerialized; }
		bool getIsNext() const { return isNext; }

		void setLogin(T login) { this->login = login; }
		void setPassword(U password) { this->password = password; }
		void setNext(User* next) { this->next = next; }
		void setIsSerialized(bool isSerialized) { this->isSerialized = isSerialized; }
		void setIsNext(bool isNext) { this->isNext = isNext; }

	public:
		User(const T& login, const U& password)
			:
			login(login),
			password(password),
			next(nullptr),
			isSerialized(false),
			isNext(false) {}

		User() = default;
		~User() = default;
	};


	template<typename T, typename U, int tableSize>
	class Hashtable
	{
	private:
		User<T, U>** ht;

		int inTable = 0;

	public:
		template<typename T, typename U, int tableSize>
		friend std::ostream& operator<<(std::ostream& stream, const Hashtable<T, U, tableSize>& Hashtable);

		int Hash(const T& login) const;
		void Put(const T& login, const U& password);
		void Remove(const T& login, const U& password);
		User<T, U>* Get(const T& login, const U& password) const;
		int hashTest();

		void Serialize();
	public:
		Hashtable();
		~Hashtable();
	};


	//definition
	template<typename T, typename U, int tableSize>
	Hashtable<T, U, tableSize>::Hashtable()
	{
		ht = new User<T, U> * [tableSize];
		for (int slot = 0; slot != tableSize; ++slot)
		{
			ht[slot] = new User<T, U>();
			ht[slot] = nullptr;
		}
	}

	template<typename T, typename U, int tableSize>
	Hashtable<T, U, tableSize>::~Hashtable()
	{
		for (int bucket = 0; bucket != tableSize; ++bucket)
		{
			User<T, U>* entry = ht[bucket];

			while (entry != nullptr)
			{
				User<T, U>* prev = entry;
				entry = entry->getNext();

				delete prev;
			}

			ht[bucket] = nullptr;
		}
	}


	template<typename T, typename U>
	std::istream& operator>>(std::istream& stream, User<T, U>& user)
	{
		std::cout << "Login: ";
		stream >> user.login;

		std::cout << "Password: ";
		stream >> user.password;

		return stream;
	}


	template<typename T, typename U, int tableSize>
	std::ostream& operator<<(std::ostream& stream, const Hashtable<T, U, tableSize>& hashtable)
	{
		for (int bucket = 0; bucket != tableSize; ++bucket)
		{
			User<T, U>* user = hashtable.ht[bucket];

			if (user == nullptr)
			{
				continue;
			}

			std::cout << "slot[ " << static_cast<int>(bucket) << " ] = ";	//uint8_t doesn`t work with ASCII

			for (;;)
			{
				stream << "Login: " << user->getLogin() << " Password: " << user->getPassword() << ' ';

				if (user->getNext() == nullptr)
				{
					break;
				}

				user = user->getNext();
			}
			std::cout << '\n';
		}

		return stream;
	}


	template<typename T, typename U, int tableSize>
	int Hashtable<T, U, tableSize>::Hash(const T& login) const
	{
		int hashKey = 0;

		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<std::mt19937::result_type> distribution(1, tableSize);

		hashKey = (distribution(generator) + login.size()) % tableSize;

		return hashKey;
	}


	template<typename T, typename U, int tableSize>
	void Hashtable<T, U, tableSize>::Put(const T& login, const U& password)
	{
		int key = Hash(login);
		User<T, U>* entry = ht[key];
		User<T, U>* prev = nullptr;

		while (entry != nullptr)
		{
			prev = entry;
			entry = entry->getNext();
		}

		if (prev == nullptr)
		{
			entry = new User<T, U>(login, password);
			ht[key] = entry;
		}
		else
		{
			entry = new User<T, U>(login, password);
			prev->setNext(entry);
		}

		inTable++;
	}


	template<typename T, typename U, int tableSize>
	void Hashtable<T, U, tableSize>::Remove(const T& login, const U& password)
	{
		bool isRemoved = false;
		bool fix = false;


		User<T, U>* tmp = nullptr;
		User<T, U>* prev = nullptr;

		for (int bucket = 0; bucket != tableSize; ++bucket)
		{
			if (isRemoved == true)
			{
				break;
			}

			if (ht[bucket] == nullptr)
			{
				continue;
			}
			else
			{
				isRemoved = false;

				tmp = ht[bucket];
				prev = nullptr;

				while ((tmp->getLogin() != login && tmp->getPassword() != password) && tmp->getNext() != nullptr)
				{
					if (tmp->getPassword() == password)
					{
						fix = true;
						break;
					}

					prev = tmp;
					tmp = tmp->getNext();
				}

				if (prev == nullptr)
				{
					if (tmp->getLogin() == login && tmp->getPassword() == password)
					{
						ht[bucket] = tmp->getNext();
						delete tmp;
						isRemoved = true;
						inTable--;
					}
				}
				else
				{
					if (tmp->getLogin() == login && tmp->getPassword() == password)
					{
						prev->setNext(tmp->getNext());
						delete tmp;
						isRemoved = true;
						inTable--;
					}
				}
			}

			if (isRemoved == false && fix == true)
			{
				bool isSameLogins = false;
				std::vector<User<T, U>*> sameLogins;
				User<T, U>* tmp = ht[bucket];


				while (tmp->getNext() != nullptr)
				{
					if (tmp->getLogin() == login && tmp->getPassword() == password)
					{
						sameLogins.push_back(tmp);
						isSameLogins = true;
					}


					tmp = tmp->getNext();
				}


				if (isSameLogins == true)
				{
					User<T, U>* entity = ht[bucket];
					User<T, U>* prevEntity = nullptr;
					User<T, U>* sameLog = sameLogins.front();


					while (entity->getPassword() != sameLog->getPassword())
					{
						prevEntity = entity;
						entity = entity->getNext();
					}


					if (prevEntity == nullptr)
					{
						ht[bucket] = entity->getNext();
						delete entity;
						isRemoved = true;
						inTable--;
					}
					else
					{
						prevEntity->setNext(entity->getNext());
						delete entity;
						isRemoved = true;
						inTable--;
					}
				}
			}
		}

		if (isRemoved == false)
		{
			std::cerr << "The key is not found" << std::endl;
		}
	}


	template<typename T, typename U, int tableSize>
	User<T, U>* Hashtable<T, U, tableSize>::Get(const T& login, const U& password) const
	{
		bool isFounded = false;

		User<T, U>* tmp = nullptr;
		User<T, U>* prev = nullptr;

		for (int bucket = 0; bucket != tableSize; ++bucket)
		{
			if (ht[bucket] == nullptr)
			{
				continue;
			}
			else
			{
				if (isFounded == true)
				{
					break;
				}

				isFounded = false;

				tmp = ht[bucket];

				while (tmp->getLogin() != login && tmp->getNext() != nullptr)
				{
					if (tmp->getPassword() == password)
					{
						break;
					}

					prev = tmp;
					tmp = tmp->getNext();
				}

				if (tmp->getLogin() == login && tmp->getPassword() == password)
				{
					isFounded = true;
					return tmp;
				}

			}

			if (isFounded == false)
			{
				User<T, U>* tmp = ht[bucket];
				while (tmp != nullptr)
				{
					if (tmp->getLogin() == login && tmp->getPassword() == password)
					{
						return tmp;
					}
					tmp = tmp->getNext();
				}
			}
		}

		if (isFounded == false)
		{
			std::cerr << "The key is not found" << std::endl;
		}
	}


	template<typename T, typename U, int tableSize>
	int Hashtable<T, U, tableSize>::hashTest()
	{
		User<T, U> user;

		std::cin >> user;

		return static_cast<int>(Hash(user.getLogin())); // uint8_t doesn`t work with ASCII
	}


	template<typename T, typename U, int tableSize>
	void Hashtable<T, U, tableSize>::Serialize()
	{
		ObjectModel::Object hashtable("hashtable");

		for (int slot = 0; slot != tableSize; ++slot)
		{
			User<T, U>* tmp = ht[slot];

			if (tmp == nullptr || tmp->getIsSerialized() == true)
			{
				continue;
			}

			std::unique_ptr<ObjectModel::Array> Login = ObjectModel::Array::createString("Login:", ObjectModel::Type::U8, tmp->getLogin());
			std::unique_ptr<ObjectModel::Array> Password = ObjectModel::Array::createString("Password:", ObjectModel::Type::U8, tmp->getPassword());

			hashtable.addEntitie(Login.get());
			hashtable.addEntitie(Password.get());

			while (tmp->getNext() != nullptr)
			{
				tmp = tmp->getNext();

				std::unique_ptr<ObjectModel::Array> Login = ObjectModel::Array::createString("Login:", ObjectModel::Type::U8, tmp->getLogin());
				std::unique_ptr<ObjectModel::Array> Password = ObjectModel::Array::createString("Password:", ObjectModel::Type::U8, tmp->getPassword());

				hashtable.addEntitie(Login.get());
				hashtable.addEntitie(Password.get());

				tmp->setIsSerialized(true);
				tmp->setIsNext(true);
			}

			tmp->setIsSerialized(true);
		}


		std::unique_ptr<ObjectModel::Primitive> numUsers = ObjectModel::Primitive::createPrimitive("inTable", ObjectModel::Type::U32, inTable);
		hashtable.addEntitie(numUsers.get());

		Core::Utility::saveAll(&hashtable);
	}
};