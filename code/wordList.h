#ifndef WORDLIST
#define WORDLIST

#include <nlohmann/json.hpp>
#include <string>
using string = std::string;
using json = nlohmann::json;
class wordList {
public:
    string word;
    int score;
    unsigned times;
    wordList() { score = times = 0; }
    bool operator<(const wordList& b) const { return score > b.score; }
    void show() const
    {
        printf("第%d次出现，得分%d\n%s\n", times, score, word.c_str());
    }
};
#endif
