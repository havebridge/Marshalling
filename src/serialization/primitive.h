#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "core.h"

namespace ObjectModel
{
	class Primitive : public Root
	{
	private:
		uint8_t type = 0;
		std::vector<uint8_t>* data = nullptr;
	private:
		Primitive();

	public:
		template<typename T>
		static Primitive* Create(std::string name, Type type, T value);

		virtual void pack(std::vector<uint8_t>& buffer, uint8_t& iterator) override;
	};


	//definition
	template<typename T>
	static Primitive* Primitive::Create(std::string name, Type type, T value)
	{
		Primitive* p = new Primitive();
		p->setName(name);
		p->wrapper = static_cast<uint8_t>(Wrapper::PRIMITIVE);
		p->type = static_cast<uint8_t>(type);
		p->data = new std::vector<uint8_t>(sizeof value);

		p->size += p->data->size();

		uint8_t iterator = 0;
		Core::template encode<T>(*p->data, iterator, value);

		return p;
	}
}


#endif