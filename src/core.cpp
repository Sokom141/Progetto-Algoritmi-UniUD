#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "core.hpp"

/**
 * randomize the string up to lim
 */
void random_up_to(std::string &s, const int lim, const int char_n)
{
    for (int i = 0; i < lim; ++i)
    {
        s[i] = (std::rand() % char_n) + 'a';
    }
}

void period_from(std::string &s, const int start, const int lim)
{
    for (int i = start; i < lim; ++i)
    {
        s[i] = s[((i - 1) % start) + 1];
    }
}

std::string generate_random_str(const int length, const int char_num, random_str_method method)
{
    unsigned int seed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    std::srand(seed);

    std::string str(length, 'a');

    /**
     * le lettere s(i) della stringa, per ogni i=1,…,n
     * vengono generate in modo pseudo-casuale e indipendentemente una dall'altra
     */
    if (method == random_str_method::ONE)
    {
        random_up_to(str, length, char_num);
    }
    /**
     * un parametro q compreso fra 1 ed n viene generato in modo pseudo-causale
     * in seguito vengono generate le lettere s(i) per ogni i=1,…,q, seguendo il medoto 1.
     * infine la parte rimanente di s viene generata seguendo la formula s(i)=s((i−1) mod q+1) per ogni i=q+1,…,n
     */
    else if (method == random_str_method::TWO)
    {
        const int q = (std::rand() % length) + 1;

        random_up_to(str, q, char_num);

        period_from(str, q, length);
    }
    /**
     * una variante del metodo 2.
     * viene applicata, con l'eccezione che ad s(q) viene assegnata una lettera speciale 
     * differente da tutte quelle generate in modo pseudo-casuale
     */
    else if (method == random_str_method::THREE)
    {
        const int q = (std::rand() % length) + 1;

        random_up_to(str, q, char_num);

        period_from(str, q, length);

        str[q] = 'a' + char_num;
    }
    /**
     * costruzione deterministica di s che possa fungere da caso pessimo.
     */
    else
    {
        const int q = length - 1;

        random_up_to(str, q, char_num);

        period_from(str, q, length);

        str[q] = 'a' + char_num;
    }

    return str;
}

int period_naive(const std::string &str)
{
    const int n = str.length();

    for (int i = 1; i <= n; ++i)
    {
        std::string str1 = str.substr(0, n - i);
        std::string str2 = str.substr(i, n - i);

        if (str1.compare(str2) == 0)
        {
            return i;
        }
    }

    return n;
}

int period_smart(const std::string &str)
{
    const int n = str.length();

    std::vector<int> vec;
    vec.reserve(n);
    vec.push_back(0);

    for (int i = 1; i < n; ++i)
    {
        int z = vec[i - 1];

        while (z > 0 && str[z] != str[i])
        {
            z = vec[z - 1];
        }

        if (str[z] == str[i])
        {
            vec.push_back(z + 1);
        }
        else
        {
            vec.push_back(0);
        }
    }

    return n - vec[n - 1];
}

double get_system_resolution()
{
    auto start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end;

    do
    {
        end = std::chrono::steady_clock::now();
    } while (start == end);

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

std::string name(random_str_method m)
{
    switch (m)
    {
    case random_str_method::ONE:
        return "one";
    case random_str_method::TWO:
        return "two";
    case random_str_method::THREE:
        return "three";
    default:
        return "four";
    }
}