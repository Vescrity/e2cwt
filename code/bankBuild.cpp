#include "bankBuild.h"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
void buildWordBank(const std::string& inputFile, const std::string& outputFile)
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
