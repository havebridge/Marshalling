#include "array.h"

namespace ObjectModel
{
	Array::Array()
	{
		size += sizeof count + sizeof type;
	}

	void Array::pack(std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Core::encode<uint8_t>(buffer, iterator, nameLength);
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, wrapper);
		Core::encode<uint8_t>(buffer, iterator, type);
		Core::encode<uint32_t>(buffer, iterator, count);
		Core::encode<uint8_t>(buffer, iterator, *data);
		Core::encode<uint32_t>(buffer, iterator, size);
	}

	Array Array::unpackStr(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Array str;

		str.nameLength = Core::decode<uint8_t>(buffer, iterator);
		str.name = Core::decode<std::string>(buffer, iterator);
		str.wrapper = Core::decode<uint8_t>(buffer, iterator);
		str.type = Core::decode<uint8_t>(buffer, iterator);
		str.count = Core::decode<uint32_t>(buffer, iterator);

		str.data = new std::vector<uint8_t>(str.count);

		Core::decode<uint8_t>(buffer, iterator, *str.data);
		str.size = Core::decode<uint32_t>(buffer, iterator);


		return str;
	}


	Array Array::unpackArr(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Array arr;

		arr.nameLength = Core::decode<uint8_t>(buffer, iterator);
		arr.name = Core::decode<std::string>(buffer, iterator);
		arr.wrapper = Core::decode<uint8_t>(buffer, iterator);
		arr.type = Core::decode<uint8_t>(buffer, iterator);
		arr.count = Core::decode<uint32_t>(buffer, iterator);

		arr.data = new std::vector<uint8_t>(arr.count * getTypeSize(static_cast<Type>(arr.type)));

		Core::decode<uint8_t>(buffer, iterator, *arr.data);
		arr.size = Core::decode<uint32_t>(buffer, iterator);


		return arr;
	}

}