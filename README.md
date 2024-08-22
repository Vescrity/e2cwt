# e2cwt

> English 2 Chinese Words Test

Simple and silly program to help you learn words. For personal usage.

## Dependencies

- sdcv
- (optional) stardict-oxford-gb-formated

## Build

- nlohmann-json
- cmake

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

- A word list. One word for one line.
- Run this program, build the wordbank data(json).
- Start your test with your wordbank.
    - It will pick some words randomly.
    - When the word shows out, try to think its meaning. Then press enter.
    - It will show the output of `sdcv $word`
    - You can give a score to this word according to your familiarty to the word.
    - It will always show the word which has the lowest score.
    - When a word's score add up to 100 or more, it will be considered as passed in this time's test.
    - If a word's score add up to more than 200, it will be marked as learned in the database and it will never be picked out.

