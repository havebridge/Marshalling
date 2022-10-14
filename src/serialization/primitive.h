#pragma once

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
		static std::unique_ptr<Primitive> createPrimitive(std::string name, Type type, T value)
		{
			std::unique_ptr<Primitive> p(new Primitive());
			p->setName(name);
			p->wrapper = static_cast<uint8_t>(Wrapper::PRIMITIVE);
			p->type = static_cast<uint8_t>(type);
			p->data = new std::vector<uint8_t>(sizeof value);

			p->size += static_cast<uint32_t>(p->data->size());

			uint16_t iterator = 0;
			Core::template encode<T>(*p->data, iterator, value);

			return p;
		}


		virtual void pack(std::vector<uint8_t>&, uint16_t&) override;
	};
}