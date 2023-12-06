#include <iostream>
#include <typeinfo>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>
/**
    \file 02_2.cxx

    \author Erik Sieburgh
*/
void check_value(const int value, int &max_value)
{
    if (value > max_value)
    {
        max_value = value;
    }
}

int find_power(const std::string line)
{
    std::string no_game_line = line.substr(line.find(":") + 1);
    std::istringstream iss(no_game_line);

    std::string game;
    int power = 1;

    std::unordered_map<std::string, int> min_amount_colours =
        {
            {"blue", 0},
            {"red", 0},
            {"green", 0}};

    std::vector<std::string> colours{"blue", "red", "green"};
    while (std::getline(iss, game, ';'))
    {
        std::istringstream iss_2(game);
        std::string pull;
        while (std::getline(iss_2, pull, ','))
        {
            std::vector<std::string>::iterator it;

            for (it = colours.begin(); it != colours.end(); ++it)
            {
                std::string colour = *it;
                if (pull.ends_with(colour))
                {
                    // The value of the mapping is given by reference.
                    check_value(std::stoi(pull), min_amount_colours[colour]);
                }
            }
        }
    }

    // Create power by multiplying the values of the minimum amount of balls
    // of each colour require for the game to be possible.
    for (const auto &[key, value] : min_amount_colours)
    {
        power = power * value;
    }

    return power;
}

int main(int argc, char *argv[])
{
    std::string line;
    std::ifstream inputFile("input2.txt");

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
    while (std::getline(inputFile, line))
    {
        int power = find_power(line);
        sum += power;
    }

    std::cout << sum << std::endl;
    std::cout << "End of Script" << std::endl;
    return 0;
}