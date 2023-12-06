#include <iostream>
#include <typeinfo>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>
/**
    \file 03_1.cxx

    \author Erik Sieburgh
*/
std::vector<int> find_symbols(std::string line)
{
    std::vector<std::string> symbol{"+", "#", "$", "*", "/", "=", "-", "&", "^", "@", "!", "%"};
    std::vector<std::string>::iterator it;
    std::vector<int> symbol_location;
    for (it = symbol.begin(); it != symbol.end(); ++it)
    {
        std::string symbol = *it;
        size_t pos = 0;
        while (line.find(symbol, pos) != std::string::npos)
        {
            size_t foundPosition = line.find(symbol, pos);
            symbol_location.push_back(foundPosition);
            pos = foundPosition + 1;
        }
    }
    return symbol_location;
}

std::vector<int> find_numbers(std::string line)
{
    std::regex pattern("/(\d+)/g");
    auto words_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto words_end = std::sregex_iterator();

    std::vector<std::string>::iterator it;
    std::vector<int> symbol_location;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        std::string match_str = match.str();
        size_t pos = 0;
        while (line.find(match_str, pos) != std::string::npos)
        {
            // add the length of the number to the position.
            size_t foundPosition = line.find(match_str, pos);
            symbol_location.push_back(foundPosition);
            pos = foundPosition + 1;
        }
    }
    return symbol_location;
}

void add_horizontal_parts(std::string line)
{
}

int main(int argc, char *argv[])
{
    std::string line;
    std::ifstream inputFile("input3.txt");

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
    std::string previous_line;
    while (std::getline(inputFile, line))
    {
        std::vector<int> symbol_locations = find_symbols(line);
        for (int n : symbol_locations)
            std::cout << n << ' ';
        std::cout << '\n';
    }
    std::cout << "End of Script" << std::endl;
    return 0;
}