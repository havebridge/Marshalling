#pragma once

#include "core.h"

namespace ObjectModel
{
	class Array : public Root
	{
	private:
		uint32_t count = 0;
		uint8_t type = 0;
		std::vector<uint8_t>* data = nullptr;
	private:
		Array();
	public:

		template<typename T>
		static Array* createArray(std::string name, Type type, T value)
		{
			Array* arr(new Array());
			arr->setName(name);
			arr->wrapper = static_cast<uint8_t>(Wrapper::ARRAY);
			arr->type = static_cast<uint8_t>(type);
			arr->count = static_cast<uint32_t>(value.size());

			arr->data = new std::vector<uint8_t>(sizeof T * arr->count);

			arr->size += static_cast<uint32_t>(sizeof T * arr->count);

			uint16_t iterator = 0;
			Core::template encode<T>(*arr->data, iterator, value);

			return arr;
		}

		template<typename T>
		static Array* createString(std::string name, Type type, T value)
		{
			Array* str(new Array());
			str->setName(name);
			str->wrapper = static_cast<uint8_t>(Wrapper::STRING);
			str->type = static_cast<uint8_t>(type);
			str->count = static_cast<uint32_t>(value.size());

			str->data = new std::vector<uint8_t>(str->count);

			str->size += static_cast<uint32_t>(str->count);

			uint16_t iterator = 0;
			Core::template encode<T>(*str->data, iterator, value);

			return str;
		}

		virtual void pack(std::vector<uint8_t>&, uint16_t&) override;
	};
}