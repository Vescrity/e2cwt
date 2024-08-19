#include <algorithm>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <queue>
#include <random>
#include <stdio.h>
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

std::vector<wordList> getUniqueRandomWords(const std::string& wordBankFile, int numWords)
{
    std::ifstream wordBankStream(wordBankFile);
    json wordBank = json::parse(wordBankStream);
    wordBankStream.close();

    std::vector<std::string> words;
    for (auto it = wordBank.begin(); it != wordBank.end(); ++it) {
        words.push_back(it.key());
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(words.begin(), words.end(), gen);

    std::vector<wordList> randomWords;
    wordList temp;
    for (int i = 0; i < numWords; i++) {
        if (wordBank[words[i]]["time"] >= 100) {
            numWords++;
            continue;
        }
        temp.word = words[i];
        randomWords.push_back(temp);
    }

    return randomWords;
}

void buildWordBank(const std::string& inputFile,
    const std::string& outputFile)
{
    std::ifstream inFile(inputFile);
    std::string word;
    json wordBank;

    while (std::getline(inFile, word)) {
        wordBank[word] = { { "time", 0 } };
    }

    std::ofstream outFile(outputFile);
    outFile << wordBank.dump(4);
    inFile.close();
    outFile.close();
}

void evaluateWords(const std::string& wordBankFile, const int numWords)
{
    std::priority_queue<wordList> q;
    const auto list = getUniqueRandomWords(wordBankFile, numWords);
    for (auto i : list)
        q.push(i);
    while (q.top().score < 100) {
        system("clear");
        auto crt = q.top();
        crt.times++;
        q.pop();
        crt.show();
        string w;
        std::getline(std::cin, w);
        string cmd = "sdcv " + crt.word;
        system(cmd.c_str());
        printf("Enter your score: ");
        int score;
        std::cin >> score;
        std::cin.ignore();
        crt.score += score;
        q.push(crt);
    }
    std::ifstream wordBankStream(wordBankFile);
    json wordBank = json::parse(wordBankStream);
    wordBankStream.close();
    printf("FINISHED");

    while (!q.empty()) {
        int score;
        int adds = 1;
        q.top().show();
        if (q.top().score > 999)
            adds = 100;
        wordBank[q.top().word]["time"] = int(wordBank[q.top().word]["time"]) + adds;
        q.pop();
    }
    std::ofstream wordBankStream2(wordBankFile);
    wordBankStream2 << wordBank.dump(4);
    wordBankStream2.close();
}

int main()
{
    for (;;) {
        system("clear");
        printf("1. Build wordbank\n2. Start Test\n3. Exit\n");
        int a;
        scanf("%d", &a);
        if (a == 1) {
            printf("Word list filename: ");
            string aa, bb;
            std::cin >> aa;
            printf("Word bank filename: ");
            std::cin >> bb;
            buildWordBank(aa, bb);
        } else if (a == 2) {
            printf("Word bank filename: ");
            string aa;
            int n;
            std::cin >> aa;
            printf("Number of words: ");
            std::cin >> n;
            std::cin.ignore();
            evaluateWords(aa, n);
        } else
            return 0;
    }
}
