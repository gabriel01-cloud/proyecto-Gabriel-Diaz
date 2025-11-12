#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct RankingEntry {
    string name;
    int score;
};

class RankingManager {
private:
    string filename;
    static const int MAX_ENTRIES = 50;
    RankingEntry entries[MAX_ENTRIES];
    int count;

public:
    RankingManager(const string& file = "ranking.txt");
    void load();
    void save();
    void addEntry(const std::string& name, int score);
    void printTop(int n = 5);
};

