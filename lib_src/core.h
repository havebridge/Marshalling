#pragma once


#include <iostream>
#include <fstream>

#include <memory>

#include <string>
#include <vector>

#include <bitset>


#include "root.h"
#include "data.h"

namespace Core
{
	namespace Utility
	{
		bool LIB isLittleEndian();
		void SaveInFile(const std::vector<uint8_t>&, const char*);
		std::vector<uint8_t> LIB load(const char* path);
		void LIB saveAll(ObjectModel::Root*);
	}


	//serialization
	template<typename T>
	void encode(std::vector<uint8_t>& buffer, uint16_t& iterator, T value)
	{
		for (int i = (sizeof(T) * 8) - 8; i >= 0; i -= 8)
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

	
	//deserialization
	template<typename T>
	T decode(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		T temp = 0, result = 0;
		
		for (int i = 0; i != sizeof(T); ++i)
		{
			temp = buffer[iterator++] << (((sizeof(T) * 8) - 8) - (i * 8));
			result |= temp;
		}

		return result;
	}


	template<>
	inline std::string decode<std::string>(const std::vector<uint8_t>& buffer, uint16_t& iterator)
	{
		iterator -= 1;

		uint8_t size = decode<uint8_t>(buffer, iterator);

		std::string result((buffer.begin() + iterator), (buffer.begin() + (iterator + size)));
		iterator += size;

		return result;
	}


	template<typename T>
	void decode(const std::vector<uint8_t>& buffer, uint16_t& iterator, std::vector<T>& value)
	{
		for (int i = 0; i != value.size(); ++i)
		{
			value[i] = buffer[iterator++];
		}
	}
}
