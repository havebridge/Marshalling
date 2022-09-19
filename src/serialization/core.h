#pragma once


#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <bitset>


#include "root.h"
#include "data.h"

namespace Core
{
	namespace Utility
	{
		bool isLittleEndian();
		void SaveInFile(const std::vector<uint8_t>&, const char*);
		void saveAll(ObjectModel::Root*);
	}

	template<typename T>
	void encode(std::vector<uint8_t>& buffer, uint16_t& iterator, T value)
	{
		for (int i = (sizeof T * 8) - 8; i >= 0; i -= 8)
		{
			buffer[iterator++] = value >> i;
		}
	}


	template<>
	inline void encode<float>(std::vector<uint8_t>& buffer, uint16_t& iterator, float value)
	{
		uint32_t toEncode = *reinterpret_cast<uint32_t*>(&value);
		encode<>(buffer, iterator, toEncode);
	}


	template<>
	inline void encode<double>(std::vector<uint8_t>& buffer, uint16_t& iterator, double value)
	{
		uint64_t toEncode = *reinterpret_cast<uint64_t*>(&value);
		encode<>(buffer, iterator, toEncode);
	}

	template<>
	inline void encode<std::string>(std::vector<uint8_t>& buffer, uint16_t& iterator, std::string value)
	{
		for (int i = 0; i != value.size(); ++i)
		{
			encode<uint8_t>(buffer, iterator, value[i]);
		}
	}


	template<typename T>
	void encode(std::vector<uint8_t>& buffer, uint16_t& iterator, std::vector<T> value)
	{
		for (int i = 0; i != value.size(); ++i)
		{
			encode<T>(buffer, iterator, value[i]);
		}
	}
}