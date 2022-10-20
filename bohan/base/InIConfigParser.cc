/*
 * @Author: bohan.lj
 * @Date: 2022-10-20 08:23:32
 * @FilePath: /Bohan/bohan/base/InIConfigParser.cc
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-10-20 08:45:45
 * @Description: srouce_code
 */
#include "InIConfigParser.h"

namespace bohan{
InIConfigParser::InIConfigParser(const char* filename)
        :m_config_file(filename),is_load(false)
{
    LoadFile(filename);
}

InIConfigParser::~InIConfigParser()
{
}

const char* InIConfigParser::GetConfigKey(const char* key)
{
    if (!is_load)
		return NULL;

	const char* value = NULL;
	for(auto it : m_config_map)
    {
        if(strcmp(it.first.c_str(),key) == 0)
        {
            value = it.second.c_str();
            break;
        }
    }
	return value;
}

int InIConfigParser::SetConfigValue(const char* key, const char* value)
{
    if(!is_load)
        return -1;

    map<string, string>::iterator it = m_config_map.find(key);
    if(it != m_config_map.end())
    {
        it->second = value;
    }
    else
    {
        m_config_map.insert(make_pair(key, value));
    }
    return WriteFile();
}

void InIConfigParser::LoadFile(const char* filename)
{
    m_config_file.clear();
    m_config_file.append(filename);
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		printf("can not open %s,errno = %d", filename,errno);
		return;
	}

	char buf[256];
	for (;;)
	{
		char* p = fgets(buf, 256, fp);
		if (!p)
			break;

		size_t len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = 0;			

		char* ch = strchr(buf, '#');
		if (ch)
			*ch = 0;

		if (strlen(buf) == 0)
			continue;

		ParseLine(buf);
	}

	fclose(fp);
	is_load = true;
}
int InIConfigParser::WriteFile(const char*filename)
{
   FILE* fp = NULL;
   if(filename == NULL)
   {
       fp = fopen(m_config_file.c_str(), "w");
   }
   else
   {
       fp = fopen(filename, "w");
   }
   if(fp == NULL)
   {
       return -1;
   }

   char szPaire[128];
   map<string, string>::iterator it = m_config_map.begin();
   for (; it != m_config_map.end(); it++)
   {
       memset(szPaire, 0, sizeof(szPaire));
       snprintf(szPaire, sizeof(szPaire), "%s=%s\n", it->first.c_str(), it->second.c_str());
       uint32_t ret =  fwrite(szPaire, strlen(szPaire),1,fp);
       if(ret != 1)
       {
          fclose(fp);
          return -1;
       }
   }
   fclose(fp);
   return 0;
}
void InIConfigParser::ParseLine(char* line)
{
    char* p = strchr(line, '=');
	if (p == NULL)
		return;

	*p = 0;
	char* key =  TrimSpace(line);
	char* value = TrimSpace(p + 1);
	if (key && value)
	{
		m_config_map.insert(make_pair(key, value));
	}
}
char* InIConfigParser::TrimSpace(char* name)
{
    char* start_pos = name;
	while( (*start_pos == ' ') || (*start_pos == '\t'))
	{
		start_pos++;
	}

	if (strlen(start_pos) == 0)
		return NULL;

	// remove ending space or tab
	char* end_pos = name + strlen(name) - 1;
	while ( (*end_pos == ' ') || (*end_pos == '\t') )
	{
		*end_pos = 0;
		end_pos--;
	}

	int len = (int)(end_pos - start_pos) + 1;
	if (len <= 0)
		return NULL;

	return start_pos;
}
}