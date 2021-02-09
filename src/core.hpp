#ifndef _CORE_H
#define _CORE_H

#include <iostream>

/**
 *  Generate a random string with a random period, based on length and a number of characters.
 *  @param length length of the string
 *  @param char_num number of characters, starting from 'a', to be included
 *  @return A standard randomly generated string. 
 */
std::string generate_random_str(const int length, const int char_num);

#endif // _CORE_H