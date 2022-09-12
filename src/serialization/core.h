#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <fstream>

#include <bitset>

#include <vector>

#include <cassert>

#include "data.h"	
#include "root.h"

namespace Core
{
	namespace Util
	{
		bool isLittleEndian();
		void saveInFile(ObjectModel::Root* data, const std::vector<uint8_t>& buffer, const char* filePath);
		void saveAll(ObjectModel::Root* data);
	}

	template<typename T>
	void encode(std::vector<uint8_t>& buffer, uint8_t& iterator, T value)
	{
		for (int i = (sizeof T * 8) - 8; i >= 0; i -= 8)
			buffer[iterator++] = value >> i;
	}

	template<>
	inline void encode<float>(std::vector<uint8_t>& buffer, uint8_t& iterator, float value)
	{
		uint32_t toEncode = *reinterpret_cast<uint32_t*>(&value);
		encode<>(buffer, iterator, toEncode);
	}

	template<>
	inline void encode<double>(std::vector<uint8_t>& buffer, uint8_t& iterator, double value)
	{
		uint64_t toEncode = *reinterpret_cast<uint64_t*>(&value);
		encode<>(buffer, iterator, toEncode);
	}

	template<>
	inline void encode<std::string>(std::vector<uint8_t>& buffer, uint8_t& iterator, std::string value)
	{
		for (uint8_t i = 0; i != value.size(); ++i)
		{
			encode<uint8_t>(buffer, iterator, value[i]);
		}
	}

	template<typename T>
	void encode(std::vector<uint8_t>& buffer, uint8_t& iterator, std::vector<T> value)
	{
		for (uint8_t i = 0; i != value.size(); ++i)
		{
			encode<T>(buffer, iterator, value[i]);
		}
	}

}

#endif