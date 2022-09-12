#ifndef ARRAY_H
#define ARRAY_H

#include "core.h"

namespace ObjectModel
{
	class Array : public Root
	{
	private:
		uint8_t type = 0;
		uint8_t count;
		std::vector<uint8_t>* data = nullptr;
	private:
		Array();
	public:
		template<typename T>
		static Array* createArray(std::string name, Type type, std::vector<T> value);

		template<typename T>
		static Array* createString(std::string name, Type type, T value);

		virtual void pack(std::vector<uint8_t>& buffer, uint8_t& iterator) override;
	};


	//definition
	template<typename T>
	static Array* Array::createArray(std::string name, Type type, std::vector<T> value)
	{
		Array* arr = new Array();
		arr->setName(name);
		arr->wrapper = static_cast<uint8_t>(Wrapper::ARRAY);
		arr->type = static_cast<uint8_t>(type);
		arr->data = new std::vector<uint8_t>(value.size() * sizeof T);
		arr->count = static_cast<uint8_t>(value.size());

		arr->size += static_cast<uint8_t>(value.size() * sizeof T);

		uint8_t iterator = 0;
		Core::template encode<T>(*arr->data, iterator, value);

		return arr;
	}

	template<typename T>
	static Array* Array::createString(std::string name, Type type, T value)
	{
		Array* str = new Array();
		str->setName(name);
		str->wrapper = static_cast<uint8_t>(Wrapper::STRING);
		str->type = static_cast<uint8_t>(type);
		str->data = new std::vector<uint8_t>(value.size());
		str->count = static_cast<uint8_t>(value.size());

		str->size += static_cast<uint8_t>(value.size());

		uint8_t iterator = 0;
		Core::template encode<T>(*str->data, iterator, value);

		return str;
	}

}

#endif 