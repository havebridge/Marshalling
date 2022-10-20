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
}