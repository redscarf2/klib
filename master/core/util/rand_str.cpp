
#include "rand_str.h"


#ifndef _WIN32
#include <string.h>
#endif


const char g_rand_str_tbl[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

using namespace klib::util;


rand_str::rand_str() 
    : str_tbl_(nullptr)
    , tbl_len_(0)
    , gen_len_(10)
{
    str_tbl_ = g_rand_str_tbl;
    tbl_len_ = strlen(g_rand_str_tbl);
}

rand_str::rand_str(size_t len) 
    : str_tbl_(nullptr)
    , tbl_len_(0)
{
    str_tbl_ = g_rand_str_tbl;
    tbl_len_ = strlen(g_rand_str_tbl);

    gen_len_ = len;
}

bool rand_str::set_str_tbl(const char* buf, size_t len)
{
    str_tbl_ = buf;
    tbl_len_ = len;
    return len > 0;
}

std::string rand_str::get_rand_str(size_t len)
{
    std::string str_tmp;
    str_tmp.reserve(len);

    for (size_t index = 0; index < len; index++)
    {
        size_t offset = rd_() % tbl_len_;
        str_tmp.append(str_tbl_ + offset, 1);
    }
    return std::move(str_tmp);
}

rand_str::operator std::string()
{
    return get_rand_str(gen_len_);
}