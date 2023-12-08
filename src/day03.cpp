#include <iostream>
#include <vector>
#include <tuple>
#include <regex>

typedef std::vector<std::tuple<int, char, int>> vtChar;
typedef std::vector<std::tuple<int, int, int>> vtInt;
typedef std::map<std::pair<size_t, size_t>, std::tuple<size_t, size_t>> ptMap;

void check_symbol(const vtChar& symbols, const std::tuple<int, int, int>& tuple, ptMap& map, size_t& sum_part1){
    for (size_t i = 0; i < symbols.size(); i++){
        if (std::get<0>(symbols[i]) >= std::get<1>(tuple) && std::get<0>(symbols[i]) <= std::get<2>(tuple) ) {
            sum_part1 += std::get<0>(tuple);
            if (std::get<1>(symbols[i]) == '*') {
                std::pair<size_t, size_t> map_key = std::make_pair(std::get<0>(symbols[i]), std::get<2>(symbols[i]));
                if (map.find(map_key) == map.end()) {
                    map.insert(std::make_pair(map_key, std::make_tuple(1, std::get<0>(tuple))));
                } else {
                    std::get<0>(map[map_key])++;
                    std::get<1>(map[map_key]) *= std::get<0>(tuple);
                }
            }
        }
    }
}

void solution(std::istream &input, size_t& sum_part1, size_t& sum_part2){
    std::string line;
    std::vector<vtChar> symbols;
    std::vector<vtInt> numbers;
    size_t line_count = 0;

    while (std::getline(input, line)){
        std::string symbols_line = line;
        std::string numbers_line = line;
        vtChar line_symbols;
        vtInt line_numbers;
        std::smatch match;
        size_t pos_sym = 0;
        size_t pos_num = 0;
        line_count++;

        while(std::regex_search(symbols_line, match, std::regex("[^0-9.]"))){
            pos_sym += pos_sym == 0 ? match.position() : match.position() + 1;
            line_symbols.push_back(std::make_tuple(pos_sym, symbols_line[match.position()], line_count));
            symbols_line = match.suffix().str();
        }
        symbols.push_back(line_symbols);

        while(std::regex_search(numbers_line, match, std::regex("\\b\\d+\\b"))){
            pos_num += match.position();
            line_numbers.push_back(std::make_tuple(std::stoi(match.str()), pos_num - 1, pos_num + match.length()));
            numbers_line = match.suffix().str();
            pos_num += match.length();
        }
        numbers.push_back(line_numbers);
    }

    ptMap map;
    for (size_t i = 0; i < numbers.size(); i++){
        for ( auto tuple : numbers[i]) {
            check_symbol(symbols[i], tuple, map, sum_part1);
            i != 0 ? check_symbol(symbols[i-1], tuple, map, sum_part1) : void();
            i != numbers.size() - 1 ? check_symbol(symbols[i+1], tuple, map, sum_part1) : void();
        } 
    }

    for (auto gear : map) {
        if (std::get<0>(gear.second) == 2) {
            sum_part2 += std::get<1>(gear.second);
        }
    }
}

int main(){
    std::istream &input = std::cin;
    std::string line;
    size_t sum_part1 = 0;
    size_t sum_part2 = 0;
    
    solution(input, sum_part1, sum_part2);
    
    std::cout << "Sum for part1: " << sum_part1 << std::endl;
    std::cout << "Sum for part2: " << sum_part2 << std::endl;
    return 0;
}