#pragma once

#include "core.h"

namespace ObjectModel
{
	class Root
	{
	protected:
		std::string name;
		uint8_t wrapper;
		uint8_t nameLenght;
		uint32_t size;
	protected:
		Root()
			:
			name("unknown"),
			wrapper(0),
			nameLenght(0),
			size(sizeof wrapper + sizeof nameLenght + sizeof size) {}
	public:
		void setName(std::string name)
		{
			this->name = name;
			nameLenght += static_cast<uint8_t>(name.size());
			size += nameLenght;
		}

		uint32_t getSize() const { return size; }
		std::string getName() const { return name; }

		virtual void pack(std::vector<uint8_t>&, uint16_t&) = 0;

	};
}