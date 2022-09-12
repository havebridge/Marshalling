#include "object.h"

namespace ObjectModel
{
	Object::Object(std::string name)
	{
		setName(name);
		wrapper = static_cast<uint8_t>(Wrapper::OBJECT);
		size += sizeof count;
	}


	void Object::addEntitie(Root* r)
	{
		this->entities.push_back(r);
		count++;
		size += r->getSize();
	}


	void Object::pack(std::vector<uint8_t>& buffer, uint8_t& iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, nameLength);
		Core::encode<uint8_t>(buffer, iterator, wrapper);
		Core::encode<uint8_t>(buffer, iterator, count);

		for (Root* r : entities)
		{
			r->pack(buffer, iterator);
		}
		Core::encode<uint8_t>(buffer, iterator, size);
	}

}