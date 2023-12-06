#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

typedef std::vector<std::tuple<int64_t, int64_t, int64_t>> vTuple;

void extract_numbers(std::string input, std::vector<int64_t> *numbers){
    std::istringstream stream(input);
    int64_t number;
    while (stream >> number){
        numbers->push_back(number);
    }
}

void solution(std::istream& input, size_t* sum_part1)
{
    std::string line;
    std::getline(input, line);
    std::vector<int64_t> seeds;
    extract_numbers(line.substr(line.find(':') + 1), &seeds);

    std::vector<vTuple> maps;
    vTuple map;
    while (std::getline(input, line)){
        if (line.empty()){
            continue;
        }
        if (line.find(':') != std::string::npos){
            if (map.size() != 0){
                maps.push_back(map);
            }
            map.clear();
            continue;
        }
        std::istringstream stream(line);
        int64_t a, b, c;
        stream >> a >> b >> c;
        map.push_back(std::make_tuple(a, b, c));
    }
    maps.push_back(map);

    std::vector<int64_t> locations;
    for (auto seed : seeds){
        int64_t source = seed;
        for (auto map : maps){
            for (auto range : map){
                if (((source - std::get<1>(range)) | (std::get<1>(range) + std::get<2>(range) - source)) >= 0){
                    source = std::get<0>(range) + (source - std::get<1>(range));
                    break;
                }
            }
        }
        locations.push_back(source);
    }

    auto result = std::min_element(locations.begin(), locations.end());
    *sum_part1 = *result;
}


int main()
{
    std::istream& input = std::cin;
    size_t sum_part1 = 0;

    solution(input, &sum_part1);

    std::cout << "Part 1: " << sum_part1 << std::endl;
    return 0;
}