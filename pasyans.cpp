#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>

void Init() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

bool RemoveStack(const std::vector<std::string>& stack) {
    return stack == std::vector<std::string>{"A", "K", "Q", "J", "10", "9", "8", "7", "6"};
}


int CardRank(const std::string& card) {
    if (card == "6") return 0;
    if (card == "7") return 1;
    if (card == "8") return 2;
    if (card == "9") return 3;
    if (card == "10") return 4;
    if (card == "J") return 5;
    if (card == "Q") return 6;
    if (card == "K") return 7;
    if (card == "A") return 8;
    return -1;
}


std::pair<bool, int> SolvePasyans(std::vector<std::vector<std::string>>& stacks) {
    std::queue<std::pair<std::vector<std::vector<std::string>>, int>> queue;
    std::set<std::string> visited;

    queue.push({stacks, 0});

    while (!queue.empty()) {
        auto [curr_stacks, total_moves] = queue.front();
        queue.pop();

        
        bool if_all_empty = true;
        for (const auto& stack : curr_stacks) {
            if (!stack.empty()) {
                if_all_empty = false;
                break;
            }
        }
        if (if_all_empty) {
            return {true, total_moves};
        }

        
        for (int i = 0; i < curr_stacks.size(); ++i) {
            if (RemoveStack(curr_stacks[i])) {
                auto new_stacks = curr_stacks;
                new_stacks[i].clear();
                std::string state_tuple;
                for (const auto& stack : new_stacks) {
                    for (const auto& card : stack) {
                        state_tuple += card + ",";
                    }
                    state_tuple += "|";
                }
                if (visited.find(state_tuple) == visited.end()) {
                    visited.insert(state_tuple);
                    queue.push({new_stacks, total_moves + 1});
                }
            }
        }

        
        for (int from_index = 0; from_index < curr_stacks.size(); ++from_index) {
            if (!curr_stacks[from_index].empty()) {
                std::string moved_card = curr_stacks[from_index].back();
                for (int to_index = 0; to_index < curr_stacks.size(); ++to_index) {
                    if (from_index != to_index && !curr_stacks[to_index].empty()) {
                        std::string target_card = curr_stacks[to_index].back();
                        if (CardRank(moved_card) < CardRank(target_card)) {
                            auto new_stacks = curr_stacks;
                            new_stacks[from_index].pop_back();
                            new_stacks[to_index].push_back(moved_card);
                            std::string state_tuple;
                            for (const auto& stack : new_stacks) {
                                for (const auto& card : stack) {
                                    state_tuple += card + ",";
                                }
                                state_tuple += "|";
                            }
                            if (visited.find(state_tuple) == visited.end()) {
                                visited.insert(state_tuple);
                                queue.push({new_stacks, total_moves + 1});
                            }
                        }
                    }

                }
            }
        }
    }

    return {false, -1};
}

int main() {
    std::vector<std::vector<std::string>> input_stacks = {
        {"A", "K", "Q", "J", "10", "9", "8", "7", "6"},
        {"A", "K", "Q", "J", "10", "9", "8", "7", "6"},
        {"A", "K", "Q", "J", "10", "9", "8", "7", "6"},
        {"A", "K", "Q", "J", "10", "9", "8", "7", "6"},
        {"A", "K", "Q", "J", "10", "9", "8", "7", "6"},
        {"A", "K", "Q", "J", "10", "9", "8", "7", "6"},
        {"A", "K", "Q", "J", "10", "9", "8", "7", "6"},
        {"A", "K", "Q", "J", "10", "9", "8", "7", "6"}
    };
    auto [win_flag, min_moves] = SolvePasyans(input_stacks);
    if (win_flag) {
        std::cout << "Можно убрать все карты. \n";
        std::cout << "Минимальное количество действий: " << min_moves - 8 << '\n';
    } else {
        std::cout << "Невозможно убрать все карты.\n";
    }

    return 0;
}