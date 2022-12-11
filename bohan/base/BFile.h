/*
 * @Author: bohan.lj
 * @Date: 2022-12-11 11:19:36
 * @FilePath: /Bohan/bohan/base/BFile.h
 * @LastEditors: bohan.lj
 * @LastEditTime: 2022-12-11 11:50:46
 * @Description: srouce_code
 */

#ifndef BOHAN_BASE_BFILE_H
#define BOHAN_BASE_BFILE_H
#include "os_type.h"

#define MAX_PATH 1024

namespace bohan
{
class BFile
{
public:
    BFile():m_fp(nullptr){}
    ~BFile()
    {
         close();
    }
    int open(const char* filepath, const char* mode) 
    {
        close();
        strncpy(this->filepath, filepath, MAX_PATH);
        m_fp = fopen(filepath, mode);
        return m_fp ? 0 : errno;
    }
    void close() 
    {
        if(m_fp) 
        {
            fclose(m_fp);
            m_fp = nullptr;
        }
    }
    bool isOpen(){return m_fp};
    size_t read(void* ptr, size_t len) 
    {
        return fread(ptr, 1, len, m_fp);
    }
    size_t write(const void* ptr, size_t len) 
    {
        return fwrite(ptr, 1, len, m_fp);
    }
    size_t write(const std::string& str) 
    {
        return write(str.c_str(), str.length());
    }
    int seek(size_t offset, int whence = SEEK_SET) 
    {
        return fseek(m_fp, offset, whence);
    }
    int tell() 
    {
        return ftell(m_fp);
    }
    int flush() 
    {
        return fflush(m_fp);
    }
    static size_t size(const char* filepath) 
    {
        struct stat st;
        memset(&st, 0, sizeof(st));
        stat(filepath, &st);
        return st.st_size;
    }
    size_t size() 
    {
        return BFile::size(m_filepath);
    }
    size_t readall(std::string& str) 
    {
        size_t filesize = size();
        if (filesize == 0) 
            return 0;
        str.resize(filesize);
        return fread((void*)str.data(), 1, filesize, m_fp);
    }
    bool readline(std::string& str) 
    {
        str.clear();
        char ch;
        while (fread(&ch, 1, 1, m_fp)) {
            if (ch == '\n') { // unix LF
                return true;
            }
            if (ch == '\r')  //dos: CRLF
            { 
                if (fread(&ch, 1, 1, m_fp) && ch != '\n') 
                {
                    fseek(m_fp, -1, SEEK_CUR);
                }
                return true;
            }
            str += ch;
        }
        return str.length() != 0;
    }

    int readrange(std::string& str, size_t from = 0, size_t to = 0) 
    {
        size_t filesize = size();
        if (filesize == 0) 
              return 0;
        if (to == 0 || to >= filesize) 
            to = filesize - 1;
        size_t readbytes = to - from + 1;
        str.resize(readbytes);
        fseek(m_fp, from, SEEK_SET);
        return fread((void*)str.data(), 1, readbytes, m_fp);
    }
private:
   char m_filepath[MAX_PATH];
   FILE *m_fp;
};
}

#endif