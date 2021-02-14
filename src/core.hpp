#ifndef _CORE_H
#define _CORE_H

#include <iostream>
#include <fstream>
#include <vector>

/**
 * enum class for string generation method
 */
enum class random_str_method
{
    ONE,
    TWO,
    THREE,
    FOUR
};

/**
 * Get the string name of the enum class 
 * @param m the enum class member
 */
std::string name(random_str_method m);

/**
 *  Generate a random string with a random period, based on length and a number of characters.
 *  @param length length of the string
 *  @param char_num number of characters, starting from 'a', to be included
 *  @param method the method to generate the strings
 *  @return A standard randomly generated string. 
 */
std::string generate_random_str(const int length, const int char_num, random_str_method method);

/**
 *  Return the length of the period. Naive implementation - Theta(n^2).
 *  @param str a reference to the string to check
 *  @return The length of the period 
 */
int period_naive(const std::string &str);

/**
 *  Return the length of the period. Smart implementation - Theta(n).
 *  @param str a reference to the string to check
 *  @return The length of the period 
 */
int period_smart(const std::string &str);

/**
 *  @return the system clock resolution in nanoseconds
 */
double get_system_resolution();

/**
 *  Write a CSV file with two columns of templated types.
 *  @param filename the path to the file where the result will be written, ereasing any possible previous data
 *  @param dataset vector with a templated pair of data
 *  @param f_col_name first column name
 *  @param s_col_name second column name
 */
template <class T, class U>
void write_csv(const std::string &filename, const std::vector<std::pair<T, U>> &dataset,
               const std::string &f_col_name, const std::string &s_col_name)
{
    std::ofstream f(filename);
    if (!f.is_open())
    {
        std::cout << "Error while opening the file " << filename << '\n';
        return;
    }

    f << f_col_name << ',' << s_col_name << '\n';

    for (const auto &data_pair : dataset)
    {
        f << data_pair.first << ',' << data_pair.second << '\n';
    }

    f.close();
}

#endif // _CORE_H