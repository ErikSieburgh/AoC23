#include <iostream>
#include <typeinfo>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>
/**
    \file 02_1.cxx

    \author Erik Sieburgh
*/

int find_game_id(const std::string line)
{
    std::string game = line.substr(0, line.find(":"));
    int digit = std::stoi(game.substr(5));
    return digit;
}

bool check_game(const int value, const int max_value)
{
    if (value <= max_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int find_games(const std::string line)
{
    std::string no_game_line = line.substr(line.find(":") + 1);
    std::istringstream iss(no_game_line);

    std::string game;
    int game_id = 0;
    bool game_possible = true;
    while (std::getline(iss, game, ';'))
    {
        std::istringstream iss_2(game);

        std::string pull;
        while (std::getline(iss_2, pull, ','))
        {
            std::vector<std::string>::iterator it;
            std::vector<std::string> colours{"blue", "red", "green"};
            std::unordered_map<std::string, int> colour_max =
                {
                    {"blue", 14},
                    {"red", 12},
                    {"green", 13}};

            for (it = colours.begin(); it != colours.end(); ++it)
            {
                std::string colour = *it;
                if (pull.ends_with(colour))
                {
                    game_possible &= check_game(std::stoi(pull), colour_max[colour]);
                    if (!game_possible)
                    {
                        return 0;
                    }
                }
            }
        }
    }
    game_id = find_game_id(line);
    return game_id;
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
        int game_id = find_games(line);
        sum += game_id;
    }

    std::cout << sum << std::endl;
    std::cout << "End of Script" << std::endl;
    return 0;
}