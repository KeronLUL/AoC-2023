#include <iostream>
#include <fstream>
#include <cstring>
#include <map>

void part1(std::string line, size_t *sum){
    size_t first = line.find_first_of("0123456789");
    size_t last = line.find_last_of("0123456789");
    std::string number = std::string(1, line[first]) + std::string(1, line[last]);
    *sum += std::stoi(number);
}

void part2(std::string line, size_t *sum){
    std::map<std::string, std::string> map{{"one", "o1e"}, {"two", "t2o"}, {"three", "t3e"}, {"four", "f4r"}, {"five", "f5e"},
                                           {"six", "s6x"}, {"seven", "s7n"}, {"eight", "e8t"}, {"nine", "n9e"}};
    for (auto entry : map){
        size_t pos;
        while((pos = line.find(entry.first)) != std::string::npos){
            line.replace(pos, entry.first.length(), entry.second);
        }
    }
    part1(line, sum);
}

int main(){
    std::istream &input = std::cin;
    std::string line;
    size_t sum_part1 = 0;
    size_t sum_part2 = 0;
    
    while (std::getline(input, line)){
        part1(line, &sum_part1);
        part2(line, &sum_part2);
    }
    std::cout << "Sum for part1: " << sum_part1 << std::endl;
    std::cout << "Sum for part2: " << sum_part2 << std::endl;
    return 0;
}