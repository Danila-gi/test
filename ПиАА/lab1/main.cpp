#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

struct State {
    std::string name_of_block;
    std::map<char, int> transitions;
    int fail = -1;
    std::vector<int> output;
};

class AhoCorasick {
private:
    std::vector<State> automaton;
    int root = 0;
    std::vector<std::string> patterns;

    void buildTrie() {
        automaton.resize(1);
        automaton[0].name_of_block = "";
        for (int i = 0; i < patterns.size(); ++i) {
            int current = root;
            for (char ch : patterns[i]) {
                if (automaton[current].transitions.find(ch) == automaton[current].transitions.end()) {
                    automaton[current].transitions[ch] = automaton.size();
                    automaton.emplace_back();
                    automaton[automaton.size() - 1].name_of_block = automaton[current].name_of_block + ch;
                }
                current = automaton[current].transitions[ch];
            }
            automaton[current].output.push_back(i + 1);
        }
        /*int index = 0;
        for (auto x: automaton){
            std::cout << index++ << std::endl;
            std::cout << "Block: " << x.name_of_block << std::endl;
            for (auto y: x.transitions){
                std::cout << y.first << " - " << y.second << std::endl;
            }
            for (auto y: x.output){
                std::cout << y << " ";
            }
            std::cout << "\n=============\n";
        }*/
    }

    void buildFailureLinks() {
        std::queue<int> q;
        for (auto& pair : automaton[root].transitions) {
            q.push(pair.second);
            automaton[pair.second].fail = root;
        }

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (auto& pair : automaton[current].transitions) {
                //std::cout << "Current: " << current << " -- ";
                //std::cout << pair.first << " | " << pair.second << std::endl;
                char ch = pair.first;
                int nextState = pair.second;
                q.push(nextState);

                int failState = automaton[current].fail;
                //std::cout << failState << std::endl;
                while (failState != -1 && automaton[failState].transitions.find(ch) == automaton[failState].transitions.end()) {
                    failState = automaton[failState].fail;
                    //std::cout << failState << std::endl;
                }

                if (failState == -1) {
                    automaton[nextState].fail = root;
                } else {
                    automaton[nextState].fail = automaton[failState].transitions[ch];
                }

                automaton[nextState].output.insert(automaton[nextState].output.end(),
                                                   automaton[automaton[nextState].fail].output.begin(),
                                                   automaton[automaton[nextState].fail].output.end());
            }
        }
        /*int index = 0;
        for (auto x: automaton){
            std::cout << index++ << std::endl;
            std::cout << "Block: " << x.name_of_block << std::endl;
            for (auto y: x.transitions){
                std::cout << y.first << " - " << y.second << std::endl;
            }
            for (auto y: x.output){
                std::cout << y << " ";
            }
            std::cout << "\nFail: " << x.fail << std::endl;
            std::cout << "=============\n";
        }*/
    }

public:
    AhoCorasick(const std::vector<std::string>& patterns) : patterns(patterns) {
        buildTrie();
        //std::cout << "###############\n";
        buildFailureLinks();
    }

    std::vector<std::pair<int, int>> search(const std::string& text) {
        std::vector<std::pair<int, int>> matches;
        int current = root;

        for (int i = 0; i < text.size(); ++i) {
            char ch = text[i];
            while (current != -1 && automaton[current].transitions.find(ch) == automaton[current].transitions.end()) {
                current = automaton[current].fail;
            }

            if (current == -1) {
                current = root;
            } else {
                current = automaton[current].transitions[ch];
            }

            for (int patternIndex : automaton[current].output) {
                matches.push_back({i + 2 - patterns[patternIndex - 1].size(), patternIndex});
            }
        }

        return matches;
    }
};

int main() {
    AhoCorasick ac({"a", "ab", "bab", "bc", "bca", "caa", "c"});
    std::vector<std::pair<int, int>> matches = ac.search("abccab");

    sort(matches.begin(), matches.end());

    for (auto& match : matches) {
        std::cout << match.first << " " << match.second << std::endl;
    }
    /*std::string text;
    int n;
    std::cin >> text;
    std::cin >> n;
    std::vector<std::string> patterns(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> patterns[i];
    }

    AhoCorasick ac(patterns);
    std::vector<std::pair<int, int>> matches = ac.search(text);

    sort(matches.begin(), matches.end());

    for (auto& match : matches) {
        std::cout << match.first << " " << match.second << std::endl;
    }*/

    return 0;
}
