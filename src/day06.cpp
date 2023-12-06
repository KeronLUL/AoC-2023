#include <iostream>
#include <vector>
#include <sstream>

void extract_numbers(std::string input, std::vector<size_t> *numbers){
    std::istringstream stream(input);
    size_t number;
    while (stream >> number){
        numbers->push_back(number);
    }
}

size_t concatenate(std::vector<size_t> vector){
    std::stringstream ss;
    for (size_t number : vector){
        ss << number;
    }

    size_t final_num;
    ss >> final_num;
    return final_num;
}

void solution(std::istream& input, size_t *solution_part1, size_t *solution_part2){
    std::vector<size_t> time;
    std::vector<size_t> distance;
    
    std::string line;
    std::getline(input, line);
    extract_numbers(line.substr(line.find(':') + 1), &time);
    std::getline(input, line);
    extract_numbers(line.substr(line.find(':') + 1), &distance);

    time.push_back(concatenate(time));
    distance.push_back(concatenate(distance));

    for (size_t i = 0; i < time.size(); i++){
        size_t counter = 0;
        for (size_t charge = 0; charge < time[i]; charge++){
            counter = charge * (time[i] - charge) > distance[i] ? counter + 1 : counter;
        }
        if (i != time.size() - 1){
            *solution_part1 *= counter;
        } else {
            *solution_part2 *= counter;
        }
    }
}

int main(){
    std::istream& input = std::cin;
    size_t solution_part1 = 1;
    size_t solution_part2 = 1;

    solution(input, &solution_part1, &solution_part2);

    std::cout << "Part 1: " << solution_part1 << std::endl;
    std::cout << "Part 2: " << solution_part2 << std::endl;
    return 0;
}