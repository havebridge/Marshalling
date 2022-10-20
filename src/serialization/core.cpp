#include "core.h"

namespace Core
{
	namespace Utility
	{
		bool isLittleEndian()
		{
			uint32_t foo = 5;
			std::string result = std::bitset<8>(foo).to_string();
			return (result.back() == '1') ? true : false;
		}

		std::vector<uint8_t> load(const char* path)
		{
			std::ifstream in(path, std::ios::binary);
			std::vector<uint8_t> result((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));
			return result;
		}

		void SaveInFile(const std::vector<uint8_t>& buffer, const char* path)
		{
			std::ofstream file;

			file.open(path);

			if (file.is_open())
			{
				for (int i = 0; i != buffer.size(); ++i)
				{
					file << buffer[i];
				}

				file.close();

				return;
			}

			std::cerr << "Unable to open the file" << std::endl;
		}

		void saveAll(ObjectModel::Root* entity)
		{
			uint16_t iterator = 0;
			std::vector<uint8_t> buffer(entity->getSize());
			std::string result = "Data/" + entity->getName().substr(0, entity->getName().size()).append(".hsbrdg");
			entity->pack(buffer, iterator);
			SaveInFile(buffer, result.c_str());
		}
	}
}