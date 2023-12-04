#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>

void extract_numbers(std::string input, std::vector<int> *numbers){
    std::istringstream stream(input);
    int number;
    while (stream >> number){
        numbers->push_back(number);
    }
}

void solution(std::istream& input, size_t *sum, size_t *sum_part2){
    std::vector<std::tuple<int, std::vector<int>>> cards;
    std::string line;

    while (std::getline(input, line)){
        std::string card = line.substr(line.find(':') + 1);
        std::string win_numbers = card.substr(0, card.find('|'));
        std::string elf_numbers = card.substr(card.find('|') + 1);
        std::vector<int> numbers;
        std::vector<int> win;
        std::vector<int> elf;
        size_t counter = 0;

        std::istringstream stream(line.substr(line.find(' '), line.find(':')));
        int card_num = stream >> card_num ? card_num : 0;

        extract_numbers(win_numbers, &win);
        extract_numbers(elf_numbers, &elf);

        for (auto win_num : win){
            for (auto elf_num : elf){
                if (win_num == elf_num){
                    counter++;
                    numbers.push_back(win_num);
                }
            }
        }
        cards.push_back(std::make_pair(1, numbers));
        
        *sum += counter != 0 ? std::pow(2, counter - 1) : 0;
    }

    for (size_t i = 0; i < cards.size(); i++){
        for (size_t j = 0; j < std::get<1>(cards[i]).size(); j++){
            std::get<0>(cards[i+1+j]) += std::get<0>(cards[i]);
        }
        *sum_part2 += std::get<0>(cards[i]);
    }
}

int main(){
    std::istream &input = std::cin;
    size_t sum_part1 = 0;
    size_t sum_part2 = 0;

    solution(input, &sum_part1, &sum_part2);

    std::cout << "Part 1: " << sum_part1 << std::endl;
    std::cout << "Part 2: " << sum_part2 << std::endl;
    return 0;
}