#ifndef OPEN_H
#define OPEN_H
#include <string>
extern "C"{
namespace perennial{
    namespace fileio{
        std::string s_openFile(std::string FileName);
    }
}}
#endif
