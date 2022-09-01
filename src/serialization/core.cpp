#include "core.h"

namespace Core
{
	namespace Util
	{
		bool isLittleEndian()
		{
			uint32_t foo = 5;
			std::string result = std::bitset<8>(foo).to_string();
			return (result.back() == '1') ? true : false;
		}

		void saveInFile(const std::vector<uint8_t>& buffer, const char* filePath)
		{
			std::ofstream file;
			file.open(filePath);

			if (file.is_open())
			{
				for (uint8_t i = 0; i != buffer.size(); ++i)
				{
					file << buffer[i];
				}

				file.close();

				return;
			}

			std::cerr << "Unable to open file: " << filePath;
		}

		void saveAll(ObjectModel::Root* data)
		{
			uint8_t iterator = 0;
			std::vector<uint8_t> buffer(data->getSize());
			std::string filePath = data->getName().substr(0, data->getName().size()).append(".hsbrdg");
			data->pack(buffer, iterator);
			saveInFile(buffer, filePath.c_str());
		}
	}
}