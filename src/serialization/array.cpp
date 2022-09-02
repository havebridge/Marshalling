#include "array.h"


namespace ObjectModel
{
	Array::Array()
	{
		size += sizeof type + sizeof count;
	}

	void Array::pack(std::vector<uint8_t>& buffer, uint8_t& iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, nameLength);
		Core::encode<uint8_t>(buffer, iterator, wrapper);
		Core::encode<uint8_t>(buffer, iterator, type);
		Core::encode<uint8_t>(buffer, iterator, count);
		Core::encode<uint8_t>(buffer, iterator, *data);
		Core::encode<uint8_t>(buffer, iterator, size);
	}
}