/*
 * @Author: bohan.lj
 * @Date: 2022-10-20 08:23:20
 * @FilePath: /Bohan/bohan/base/InIConfigParser.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-11 20:04:17
 * @Description: ini config parser
 */


#ifndef BOHAN_BASE_INICONFIG_PARSER_H
#define BOHAN_BASE_INICONFIG_PARSER_H
#include "os_type.h"
#include <map>
#include <string.h>
using namespace std;

namespace bohan
{
class DLL_EXPORTS InIConfigParser
{

public:
    InIConfigParser(const char* filename);
    ~InIConfigParser();

    const char* GetConfigKey(const char* key);
    int SetConfigValue(const char* key, const char* value);
private:
    void LoadFile(const char* filename);
    int  WriteFile(const char*filename = NULL);
    void ParseLine(char* line);
    char* TrimSpace(char* name);
private:
    bool is_load;
    std::map<string, string> m_config_map;
    std::string m_config_file;
};
}

#endif
