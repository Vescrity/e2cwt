#include "evaluate.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
std::vector<wordList> getUniqueRandomWords(json wordBank, int numWords)
{

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

void evaluateWords(const std::string& wordBankFile, const int numWords)
{
    std::priority_queue<wordList> q;
    std::ifstream wordBankStream(wordBankFile);
    json wordBank = json::parse(wordBankStream);
    wordBankStream.close();
    const auto list = getUniqueRandomWords(wordBank, numWords);
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
    printf("FINISHED!!\n");

    while (!q.empty()) {
        int adds = 1;
        printf("%s: %d times\n", q.top().word.c_str(), q.top().times);
        if (q.top().score > 200)
            adds = 100;
        wordBank[q.top().word]["time"] = int(wordBank[q.top().word]["time"]) + adds;
        q.pop();
    }
    std::ofstream wordBankStream2(wordBankFile);
    wordBankStream2 << wordBank.dump(4);
    wordBankStream2.close();
    string w;
    std::getline(std::cin, w);
}
