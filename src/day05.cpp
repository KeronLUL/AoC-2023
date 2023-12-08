#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

typedef std::vector<std::tuple<int64_t, int64_t, int64_t>> vTuple;
typedef std::vector<std::tuple<int64_t, int64_t>> vtRange;

void extract_numbers(const std::string& input, std::vector<int64_t> *numbers){
    std::istringstream stream(input);
    int64_t number;
    while (stream >> number){
        numbers->push_back(number);
    }
}

void extract_range(const std::string& input, vtRange *numbers){
    std::istringstream stream(input);
    int64_t begin, end;
    while (stream >> begin >> end){
        numbers->push_back(std::make_tuple(begin, end));
    }
}

void solution(std::istream& input, size_t* sum_part1, size_t* sum_part2)
{
    std::string line;
    std::getline(input, line);
    std::vector<int64_t> seeds;
    std::vector<std::tuple<int64_t, int64_t>> seeds_range;
    extract_numbers(line.substr(line.find(':') + 1), &seeds);
    extract_range(line.substr(line.find(':') + 1), &seeds_range);

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
    for (const auto& seed : seeds){
        int64_t source = seed;
        for (const auto& map : maps){
            for (const auto& range : map){
                if (((source - std::get<1>(range)) | (std::get<1>(range) + std::get<2>(range) - source)) >= 0){
                    source = std::get<0>(range) + (source - std::get<1>(range));
                    break;
                }
            }
        }
        locations.push_back(source);
    }

    std::vector<int64_t> locations_part2;
    for (const auto& seed_range : seeds_range) {
        for ( int64_t seed = std::get<0>(seed_range); seed < std::get<1>(seed_range); ++seed){
            int64_t source = seed;
            for (const auto& map : maps){
                for (const auto& range : map){
                    if (((source - std::get<1>(range)) | (std::get<1>(range) + std::get<2>(range) - source)) >= 0){
                        source = std::get<0>(range) + (source - std::get<1>(range));
                        break;
                    }
                }
            }
            locations_part2.push_back(source);
        }
    }

    auto result = std::min_element(locations.begin(), locations.end());
    auto result_2 = std::min_element(locations_part2.begin(), locations_part2.end());
    *sum_part1 = *result;
    *sum_part2 = *result_2;
}


int main()
{
    std::istream& input = std::cin;
    size_t sum_part1 = 0;
    size_t sum_part2 = 0;

    solution(input, &sum_part1, &sum_part2);

    std::cout << "Part 1: " << sum_part1 << std::endl;
    std::cout << "Part 2: " << sum_part2 << std::endl;
    return 0;
}