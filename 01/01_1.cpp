#include <iostream>
#include <typeinfo>
#include <string>
#include <fstream>
#include <regex>
/**
    \file 01_1.cxx

    \author Erik Sieburgh
*/

int main(int argc, char *argv[])
{
    std::string line;
    std::ifstream inputFile("input1.txt");

    // Check if file can be opened
    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;
    }
    if (inputFile.is_open())
    {
        std::cout << "File is Opened!" << std::endl;
    }

    int sum = 0;
    std::regex pattern("\\d");

    // Read every line and do the following line separately.
    while (std::getline(inputFile, line))
    {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto words_end = std::sregex_iterator();
        std::string string_num;
        std::string first_digit;
        std::string last_digit;

        std::cout << "Found " << std::distance(words_begin, words_end) << " number(s) in string line:\n";
        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            std::smatch match = *i;
            std::string match_str = match.str();

            if (i == words_begin)
            {
                first_digit = match.str();
            }
            if (i != words_end)
            {
                last_digit = match.str();
            }
        }

        int int_num = 0;
        // If the string only includes one digit combine those.
        if (std::distance(words_begin, words_end) == 1)
        {
            string_num = first_digit + first_digit;
            int_num = std::stoi(string_num);
            std::cout << "int_num: " << int_num << std::endl;
        }
        // Else, combine the last two digits of the line.
        else
        {
            string_num = first_digit + last_digit;
            int_num = std::stoi(string_num);
            std::cout << "int_num: " << int_num << std::endl;
        }
        sum += int_num;
    }
    std::cout << "Total Sum: " << sum << std::endl;

    std::cout << "End of Script" << std::endl;
    return 0;
}