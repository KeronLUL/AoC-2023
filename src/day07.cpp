#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>

#define CARD_COUNT(container, container_value, value) (std::count((container).begin(), (container).end(), (container_value)) == (value))

typedef std::tuple<std::string, size_t, size_t> Tuple;
typedef std::vector<Tuple> Vector;

enum Type { HighCard, Pair, TwoPair, ThreeKind, FullHouse, FourKind, FiveKind };

size_t hand_strength(const std::string& hand){
    std::unordered_set<char> set;
    for (size_t i = 0; i < hand.length(); i++){
        set.insert(hand[i]);
    }
    auto it = set.begin();

    if(set.size() == 1){
        return FiveKind;
    } else if (set.size() == 2){
        return CARD_COUNT(hand, *it, 4) || CARD_COUNT(hand, *(++it), 4) ? FourKind : FullHouse;
    } else if (set.size() == 3){
        return CARD_COUNT(hand, *it, 3) || CARD_COUNT(hand, *(++it), 3) || CARD_COUNT(hand, *(++it), 3) ? ThreeKind : TwoPair;
    } else if (set.size() == 4){
        return Pair;
    } else {
        return HighCard;
    }
}

size_t hand_strength_joker(const std::string& hand){
    std::unordered_set<char> set;
    for (size_t i = 0; i < hand.length(); i++){
        set.insert(hand[i]);
    }

    if (set.size() == 1 && hand[0] == 'J'){
        return FiveKind;
    }

    size_t max = 0;
    for (auto it = set.begin(); it != set.end(); it++){
        if(*it != 'J'){
            std::string joker_hand = hand;
            size_t pos;
            while((pos = joker_hand.find('J')) != std::string::npos){
                joker_hand.replace(pos, 1, std::string(1, *it));
            }
            max = max < hand_strength(joker_hand) ? hand_strength(joker_hand) : max;
        }
    }
    return max;
}

bool compare_hands(const Tuple& tHand1, const Tuple& tHand2){
    return std::get<2>(tHand1) < std::get<2>(tHand2);
}

bool compare_high_card(const Tuple& tHand1, const Tuple& tHand2, const std::string& order){
    const std::string cardOrder = order;
    std::string hand1 = std::get<0>(tHand1);
    std::string hand2 = std::get<0>(tHand2);
    if(std::get<2>(tHand1) == std::get<2>(tHand2)){
        size_t i = 0;
        for( ; i < hand1.length() && hand1[i] == hand2[i]; i++);
        if (i < hand1.length()){
            size_t pos1 = cardOrder.find(hand1[i]);
            size_t pos2 = cardOrder.find(hand2[i]);

            return pos1 < pos2;
        }
    }
    return std::get<2>(tHand1) < std::get<2>(tHand2);
}

void solution(std::istream& input, size_t *sum_part1, size_t *sum_part2){
    std::string line;
    Vector cards;
    Vector cards_joker;
    while(std::getline(input, line)){
        std::string hand = line.substr(0, line.find(' '));
        size_t value = std::stoi(line.substr(line.find(' ') + 1));
        cards.push_back(std::make_tuple(hand, value, hand_strength(hand)));
        cards_joker.push_back(std::make_tuple(hand, value, hand_strength_joker(hand)));
    }
    
    std::string order = "23456789TJQKA";
    std::sort(cards.begin(), cards.end(), compare_hands);
    std::sort(cards.begin(), cards.end(), [order](const Tuple& tHand1, const Tuple& tHand2) {
        return compare_high_card(tHand1, tHand2, order);
    });
    order = "J23456789TQKA";
    std::sort(cards_joker.begin(), cards_joker.end(), compare_hands);
    std::sort(cards_joker.begin(), cards_joker.end(), [order](const Tuple& tHand1, const Tuple& tHand2) {
        return compare_high_card(tHand1, tHand2, order);
    });

    for (size_t i = 0; i < cards.size(); i++){
        *sum_part1 += std::get<1>(cards[i]) * (i+1);
        *sum_part2 += std::get<1>(cards_joker[i]) * (i+1);
    }
}


int main(){
    std::istream& input = std::cin;
    size_t sum_part1 = 0;
    size_t sum_part2 = 0;

    solution(input, &sum_part1, &sum_part2);

    std::cout << "Part 1: " << sum_part1 << std::endl;
    std::cout << "Part 2: " << sum_part2 << std::endl;
    return 0;
}