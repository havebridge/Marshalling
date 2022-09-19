#pragma once


#include "core.h"

namespace ObjectModel
{
	class Object : public Root
	{
	private:
		std::vector<Root*> entities;
		uint32_t count = 0;
	public:
		Object(std::string);
	public:
		void addEntitie(Root*);

		virtual void pack(std::vector<uint8_t>&, uint16_t&) override;
	};
}