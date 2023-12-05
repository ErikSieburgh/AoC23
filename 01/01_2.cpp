#include <iostream>
#include <typeinfo>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
/**
    \file 01_2.cxx

    \author Erik Sieburgh
*/
std::string convert_to_number(const std::string &number_alpha)
{
    /**
    convert the written numbers to string digits.

    return: string digit
    */
    std::vector<std::string> spelled_numbers{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::string written_number;
    if (number_alpha == "one")
    {
        written_number = "1";
    }
    else if (number_alpha == "two")
    {
        written_number = "2";
    }
    else if (number_alpha == "three")
    {
        written_number = "3";
    }
    else if (number_alpha == "four")
    {
        written_number = "4";
    }
    else if (number_alpha == "five")
    {
        written_number = "5";
    }
    else if (number_alpha == "six")
    {
        written_number = "6";
    }
    else if (number_alpha == "seven")
    {
        written_number = "7";
    }
    else if (number_alpha == "eight")
    {
        written_number = "8";
    }
    else if (number_alpha == "nine")
    {
        written_number = "9";
    }
    std::vector<std::string>::iterator it;
    it = find(spelled_numbers.begin(), spelled_numbers.end(), number_alpha);
    if (it == spelled_numbers.end())
    {
        std::cout << "not a number I know\n";
    }

    return written_number;
};

std::string fix_line(const std::string line)
{
    /**
    changes all the written out numbers to string digits, where the first letter of
    the written number is replaced by the string digit.

    return: string line
    */

    std::string new_line = line;
    std::vector<std::string>::iterator it;
    std::vector<std::string> spelled_numbers{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (it = spelled_numbers.begin(); it != spelled_numbers.end(); ++it)
    {
        std::string substring = *it;
        size_t pos = 0;
        while (line.std::string::find(substring, pos) != std::string::npos)
        {
            size_t foundPosition = line.find(substring, pos);
            std::string sting_number = convert_to_number(substring);
            new_line.replace(foundPosition, 1, sting_number);
            pos = foundPosition + 1;
        }
    }
    return new_line;
};

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

        line = fix_line(line);
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