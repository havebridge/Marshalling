#ifndef ROOT_H
#define ROOT_H

#include <string>


namespace ObjectModel
{
	class Root
	{
	protected:
		uint8_t wrapper;
		std::string name;
		uint8_t nameLength;
		uint8_t size;
	public:
		Root()
			:
			name("unknown"),
			wrapper(0),
			nameLength(0),
			size(sizeof wrapper + sizeof nameLength + sizeof size) {}

	public:
		inline uint8_t getSize() const { return size; }
		inline std::string getName() const { return name; }

		void setName(std::string name)
		{
			this->name = name;
			nameLength += name.size();
			this->size += nameLength;
		}

		virtual void pack(std::vector<uint8_t>& buffer, uint8_t& iterator) = 0;		//pure virtual
	};
}

#endif