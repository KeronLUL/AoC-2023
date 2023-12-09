#include <iostream>
#include <sstream>
#include <vector>
#include <set>

typedef std::vector<std::vector<int64_t>> vDiffs;

std::vector<int64_t> extract_numbers(std::string input){
    std::istringstream stream(input);
    std::vector<int64_t> numbers;
    int64_t number;
    while (stream >> number){
        numbers.push_back(number);
    }
    return numbers;
}

std::vector<int64_t> calculate_diff(std::vector<int64_t>& numbers){
    std::vector<int64_t> diffs;
    for (size_t i = 0; i < numbers.size() - 1; i++){
        diffs.push_back(numbers[i + 1] - numbers[i]);
    }

    return diffs;
}

void solution(std::istream& input, int64_t& part1, int64_t& part2){
    std::string line;
    
    while(std::getline(input, line)){
        vDiffs diffs;
        std::vector<int64_t> numbers = extract_numbers(line);
        diffs.push_back(numbers);

        while(1){
            std::vector<int64_t> diff = calculate_diff(numbers);
            diffs.push_back(diff);
            numbers = diff;
            if (std::set(diff.begin(), diff.end()).size() == 1){
                break;
            }
        }
        
        int64_t sum{0};
        int64_t value{0};
        for(auto it = diffs.rbegin(); it != diffs.rend(); ++it){
            value = it->front() - value;
            sum += it->back();
        }
        part1 += sum;
        part2 += value;
    }
}

int main(){
    std::istream& input = std::cin;
    int64_t part1{0};
    int64_t part2{0};

    solution(input, part1, part2);

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
    return 0;
}