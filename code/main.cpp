#include "bankBuild.h"
#include "evaluate.h"
#include "wordList.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdio.h>

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
