#pragma once

#include "core.h"
#include "lib.h"

namespace ObjectModel
{
	class LIB Root
	{
	protected:
		std::string name;
		uint8_t nameLength;
		uint32_t size;
	public:
		uint8_t wrapper;
	protected:
		Root()
			:
			name("unknown"),
			wrapper(0),
			nameLength(0),
			size(sizeof wrapper + sizeof nameLength + sizeof size) {}
	public:
		void setName(std::string name)
		{
			this->name = name;
			nameLength += static_cast<uint8_t>(name.size());
			size += nameLength;
		}

		uint32_t getSize() const { return size; }
		std::string getName() const { return name; }

		virtual void pack(std::vector<uint8_t>&, uint16_t&) = 0;
	};
}
