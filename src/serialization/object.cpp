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
		Core::encode<uint8_t>(buffer, iterator, nameLength);
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<uint8_t>(buffer, iterator, wrapper);

		Core::encode<uint16_t>(buffer, iterator, primitiveCount);
		for (auto p : primitives)
		{
			p.pack(buffer, iterator);
		}

		Core::encode<uint16_t>(buffer, iterator, arrayCount);
		for (auto arr : arrays)
		{
			arr.pack(buffer, iterator);
		}

		Core::encode<uint16_t>(buffer, iterator, stringCount);
		for (auto str : strings)
		{
			str.pack(buffer, iterator);
		}

		Core::encode<uint16_t>(buffer, iterator, objectCount);
		for (auto o : objects)
		{
			o.pack(buffer, iterator);
		}

		Core::encode<uint32_t>(buffer, iterator, size);
	}


	Object Object::unpack(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		Object o;
		o.nameLength = Core::decode<uint8_t>(buffer, iterator);
		o.name = Core::decode<std::string>(buffer, iterator);
		o.wrapper = Core::decode<uint8_t>(buffer, iterator);

		o.primitiveCount = Core::decode<uint16_t>(buffer, iterator);
		for (int i = 0; i != o.primitiveCount; ++i)
		{
			o.primitives.push_back(Primitive::unpack(buffer, iterator));
		}


		o.arrayCount = Core::decode<uint16_t>(buffer, iterator);
		for (int i = 0; i != o.arrayCount; ++i)
		{
			o.arrays.push_back(Array::unpackArr(buffer, iterator));
		}

		o.stringCount = Core::decode<uint16_t>(buffer, iterator);
		for (int i = 0; i != o.stringCount; ++i)
		{
			o.strings.push_back(Array::unpackStr(buffer, iterator));
		}

		o.objectCount = Core::decode<uint16_t>(buffer, iterator);
		for (int i = 0; i != o.objectCount; ++i)
		{
			o.objects.push_back(unpack(buffer, iterator));
		}

		o.size = Core::decode<uint32_t>(buffer, iterator);

		return o;
	}
}