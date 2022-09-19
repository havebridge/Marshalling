#include "object.h"


namespace ObjectModel
{
	Object::Object(std::string name)
	{
		setName(name);
		wrapper = static_cast<uint8_t>(Wrapper::OBJECT);
		size += (sizeof uint16_t) * 4;
	}

	void Object::addEntitie(Root* entity)
	{
		entities.push_back(entity);
		count += 1;
		size += entity->getSize();
	}

	void Object::pack(std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, nameLenght);
		Core::encode<uint8_t>(buffer, iterator, wrapper);

		for (auto e : entities)
		{
			e->pack(buffer, iterator);
		}

		Core::encode<uint32_t>(buffer, iterator, size);
	}
}