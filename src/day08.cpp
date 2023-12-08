#include <iostream>
#include <vector>
#include <numeric>
#include <map>

typedef std::map<std::string, std::tuple<std::string, std::string>> Map;

void solution(std::istream& input, size_t *part1, size_t *part2){
    Map maps;
    std::string line;
    std::string inst;

    std::getline(input, inst);

    while (std::getline(input, line)){
        if (line.empty()) continue;
        std::string key = line.substr(0, line.find('=') - 1);
        std::string first_val = line.substr(line.find('(') + 1, 3);
        std::string second_val = line.substr(line.find(')') - 3, 3);

        maps.insert(std::make_pair(key, std::make_tuple(first_val, second_val)));
    }

    Map starting_nodes;
    for (const auto& map : maps){
        const std::string& key = map.first;
        if (key.back() == 'A'){
            starting_nodes.insert(map);
        }
    }

    std::string key = maps.begin()->first;
    for (size_t i = 0; i < inst.size() && key != "ZZZ";){   
        key = inst[i] == 'R' ? std::get<1>(maps[key]) : key = std::get<0>(maps[key]);
        i = key != "ZZZ" && i == inst.size() - 1 ? 0 : i + 1;
        (*part1)++;
    }

    std::vector<size_t> results;
    for( const auto& node : starting_nodes){
        key = node.first;
        size_t counter = 0;
        for (size_t i = 0; i < inst.size() && key.back() != 'Z';){   
            key = inst[i] == 'R' ? std::get<1>(maps[key]) : key = std::get<0>(maps[key]);
            i = key.back() != 'Z' && i == inst.size() - 1 ? 0 : i + 1;
            counter++;
        }
        results.push_back(counter);
    }

    *part2 = results[0];
    for (size_t i = 1; i < results.size(); ++i) {
        *part2 = std::lcm(*part2, results[i]);
    }
}

int main(){
    std::istream& input = std::cin;
    size_t part1 = 0;
    size_t part2 = 0;

    solution(input, &part1, &part2);

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
    return 0;
}