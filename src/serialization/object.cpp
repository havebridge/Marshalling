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
		switch (entity->wrapper)
		{
		case 1: primitives.push_back(*dynamic_cast<Primitive*>(entity)); primitiveCount++; break;
		case 2: arrays.push_back(*dynamic_cast<Array*>(entity)); arrayCount++; break;
		case 3: strings.push_back(*dynamic_cast<Array*>(entity)); stringCount++; break;
		case 4: objects.push_back(*dynamic_cast<Object*>(entity)); objectCount++; break;
		}

		size += entity->getSize();
	}

	void Object::pack(std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, nameLenght);
		Core::encode<uint8_t>(buffer, iterator, wrapper);

		Core::encode<int16_t>(buffer, iterator, primitiveCount);
		for (auto p : primitives)
		{
			p.pack(buffer, iterator);
		}

		Core::encode<int16_t>(buffer, iterator, arrayCount);
		for (auto arr : arrays)
		{
			arr.pack(buffer, iterator);
		}

		Core::encode<int16_t>(buffer, iterator, stringCount);
		for (auto str : strings)
		{
			str.pack(buffer, iterator);
		}

		Core::encode<int16_t>(buffer, iterator, objectCount);
		for (auto o : objects)
		{
			o.pack(buffer, iterator);
		}

		Core::encode<uint32_t>(buffer, iterator, size);
	}
}