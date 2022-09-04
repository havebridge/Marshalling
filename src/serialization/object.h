#ifndef OBJECT_H
#define OBJECT_H

#include "core.h"

namespace ObjectModel
{
	class Object : public Root
	{
	private:
		std::vector<Root*> entities;
		uint8_t count;
	public:
		Object(std::string name);
		void addEntitie(Root* r);

		virtual void pack(std::vector<uint8_t>& buffer, uint8_t& iterator) override;
	};
}

#endif