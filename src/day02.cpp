#include <iostream>
#include <sstream>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

void part1(std::string line, size_t *sum){
    std::string input = line.substr(line.find(':') + 1);
    std::string game = line.substr(0, line.find(':'));
    size_t id = std::stoi(game.substr(game.find(' ')));
    bool is_valid = true;

    std::istringstream iss(input);
    std::string round;
    
    while (std::getline(iss, round, ';')) {
        size_t red = round.find("red");
        size_t green = round.find("green");
        size_t blue = round.find("blue");

        std::string red_count = round.find("red") != std::string::npos ? round.substr(red - 3, 2) : "0";
        std::string green_count = round.find("green") != std::string::npos ? round.substr(green - 3, 2) : "0";
        std::string blue_count = round.find("blue") != std::string::npos ? round.substr(blue - 3, 2) : "0";
        if (std::stoi(red_count) > MAX_RED || std::stoi(green_count) > MAX_GREEN || std::stoi(blue_count) > MAX_BLUE){
            is_valid = false;
            break;
        }
    }
    if (is_valid) *sum += id;
}

void part2(std::string line, size_t *sum){
    std::string input = line.substr(line.find(':') + 1);
    int min_r = 0;
    int min_g = 0;
    int min_b = 0;

    std::istringstream iss(input);
    std::string round;
    
    while (std::getline(iss, round, ';')) {
        size_t red = round.find("red");
        size_t green = round.find("green");
        size_t blue = round.find("blue");

        std::string red_count = red != std::string::npos ? round.substr(red - 3, 2) : "0";
        std::string green_count = green != std::string::npos ? round.substr(green - 3, 2) : "0";
        std::string blue_count = blue != std::string::npos ? round.substr(blue - 3, 2) : "0";
  
        min_r = std::stoi(red_count) > min_r ? std::stoi(red_count) : min_r;
        min_g = std::stoi(green_count) > min_g ? std::stoi(green_count) : min_g;
        min_b = std::stoi(blue_count) > min_b ? std::stoi(blue_count) : min_b;
    }
    *sum += (min_r * min_g * min_b);
}

int main(){
    std::istream &input = std::cin;
    std::string line;
    size_t sum_part1 = 0;
    size_t sum_part2 = 0;
    while(std::getline(input, line)){
        part1(line, &sum_part1);
        part2(line, &sum_part2);
    }
    std::cout << "Sum for part1: " << sum_part1 << std::endl;
    std::cout << "Sum for part2: " << sum_part2 << std::endl;
    return 0;
}