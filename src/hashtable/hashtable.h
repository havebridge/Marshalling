#ifndef HASHTABLE_H
#define HASHTABLE_H

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
		User* next;
	public:
		bool isSerialized = false;
	public:
		template<typename T, typename U>
		friend std::istream& operator>>(std::istream& stream, User<T, U>& User);

		inline T getLogin() const { return login; }
		inline U getPassword() const { return password; }
		inline User* getNext() const { return next; }

		inline void setLogin(T login) { this->login = login; }
		inline void setPassword(U password) { this->password = password; }
		inline void setNext(User* next) { this->next = next; }

	public:
		User(const T& login, const U& password)
			:
			login(login),
			password(password),
			next(nullptr) {}

		User() = default;
		~User() = default;
	};


	template<typename T, typename U, uint8_t tableSize>
	class Hashtable
	{
	private:
		User<T, U>* ht[tableSize];

	public:
		template<typename T, typename U, uint8_t tableSize>
		friend std::ostream& operator<<(std::ostream& stream, const Hashtable<T, U, tableSize>& Hashtable);

		uint8_t Hash(const T& login) const;
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
	template<typename T, typename U, uint8_t tableSize>
	Hashtable<T, U, tableSize>::Hashtable()
		:
		ht() {}


	template<typename T, typename U, uint8_t tableSize>
	Hashtable<T, U, tableSize>::~Hashtable()
	{
		for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
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


	template<typename T, typename U, uint8_t tableSize>
	std::ostream& operator<<(std::ostream& stream, const Hashtable<T, U, tableSize>& hashtable)
	{
		for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
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


	template<typename T, typename U, uint8_t tableSize>
	uint8_t Hashtable<T, U, tableSize>::Hash(const T& login) const
	{
		uint8_t hashKey = 0;

		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<std::mt19937::result_type> distribution(0, tableSize - 1);

		hashKey = (distribution(generator) + login.size()) % tableSize;

		return hashKey;
	}


	template<typename T, typename U, uint8_t tableSize>
	void Hashtable<T, U, tableSize>::Put(const T& login, const U& password)
	{
		uint8_t key = Hash(login);
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
	}


	template<typename T, typename U, uint8_t tableSize>
	void Hashtable<T, U, tableSize>::Remove(const T& login, const U& password)
	{
		bool isRemoved = false;

		User<T, U>* tmp = nullptr;
		User<T, U>* prev = nullptr;

		for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
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

				while (tmp->getLogin() != login && tmp->getNext() != nullptr)
				{
					if (tmp->getPassword() == password)
					{
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
					}
				}
				else
				{
					if (tmp->getLogin() == login && tmp->getPassword() == password)
					{
						prev->setNext(tmp->getNext());
						delete tmp;
						isRemoved = true;
					}
				}
			}

			if (isRemoved == false)
			{
				bool isSameLogins = false;
				std::vector<User<T, U>*> sameLogins;

				for (auto i = ht[bucket]; i != nullptr; i = i->getNext())
				{
					if (i->getLogin() == login && i->getPassword() == password)
					{
						sameLogins.push_back(i);
						isSameLogins = true;
					}
				}

				if (isSameLogins == true)
				{
					User<T, U>* entity = ht[bucket];
					User<T, U>* prevEntity = nullptr;

					while (entity->getPassword() != sameLogins[0]->getPassword())
					{
						prevEntity = entity;
						entity = entity->getNext();
					}
					if (prevEntity == nullptr)
					{
						ht[bucket] = entity->getNext();
						delete entity;
					}
					else
					{
						prevEntity->setNext(entity->getNext());
						delete entity;
					}
				}
			}
		}
	}


	template<typename T, typename U, uint8_t tableSize>
	User<T, U>* Hashtable<T, U, tableSize>::Get(const T& login, const U& password) const
	{
		bool isFounded = false;

		User<T, U>* tmp = nullptr;
		User<T, U>* prev = nullptr;

		for (uint8_t bucket = 0; bucket != tableSize; ++bucket)
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
				for (auto i = ht[bucket]; i != nullptr; i = i->getNext())
				{
					if (i->getLogin() == login && i->getPassword() == password)
					{
						return i;
					}
				}
			}
		}
	}


	template<typename T, typename U, uint8_t tableSize>
	int Hashtable<T, U, tableSize>::hashTest()
	{
		User<T, U> user;

		std::cin >> user;

		return static_cast<int>(Hash(user.getLogin())); // uint8_t doesn`t work with ASCII
	}


	template<typename T, typename U, uint8_t tableSize>
	void Hashtable<T, U, tableSize>::Serialize()
	{
		ObjectModel::Object hashtable("Hashtable");


		for (uint8_t slot = 0; slot != tableSize; ++slot)
		{
			User<T, U>* user = ht[slot];
			User<T, U>* userNext = user->getNext();

			if (user->isSerialized == true)
			{
				continue;
			}


			ObjectModel::Array* Login = ObjectModel::Array::createString(user->getLogin(), ObjectModel::Type::U8, user->getLogin());
			ObjectModel::Array* Password = ObjectModel::Array::createString(user->getPassword(), ObjectModel::Type::U8, user->getPassword());
			ObjectModel::Primitive* Next = ObjectModel::Primitive::createPrimitive("Next" , ObjectModel::Type::U32, &userNext);

			hashtable.addEntitie(Login);
			hashtable.addEntitie(Password);
			hashtable.addEntitie(Next);

			Core::Util::saveAll(&hashtable);
			
			user->isSerialized = true;
		}
	}
};

#endif