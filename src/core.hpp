#ifndef _CORE_H
#define _CORE_H

#include <iostream>

/**
 *  Generate a random string based on length and a period.
 *  @param length length of the string
 *  @param period period length
 *  @return A standard randomly generated string. 
 */
std::string generate_random_str(const int length, const int char_num);

#endif // _CORE_H