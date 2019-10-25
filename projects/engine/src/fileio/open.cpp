#include "open.h"
#include <string>
#include <fstream>
#include <vector>

namespace perennial{
	namespace fileio{
		std::string s_openFile(std::string FileName) //Copied from stackoverflow, apparently 200% faster when loading moby dick... or something.
		{
			std::ifstream ifs(FileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

			std::ifstream::pos_type fileSize = ifs.tellg();
			ifs.seekg(0, std::ios::beg);

			std::vector<char> bytes(fileSize);
			ifs.read(bytes.data(), fileSize);

			return std::string(bytes.data(), fileSize);
		}
	}
}