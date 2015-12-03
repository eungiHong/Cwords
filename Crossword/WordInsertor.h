#pragma once

#ifndef WordInsertor_H
#define WordInsertor_H

#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

class WordInsertor {
private:
	char **grid;
	int gridLength;
	set<vector<int>>* blockSet;
	set<vector<int>>::reverse_iterator setIterator;
	inline void draw(int x, int y);

public:
	WordInsertor(int length, set<vector<int>>* blocks);
	~WordInsertor();
	void blockDrawer();
	void reload(vector<string>& wordSet2, vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9, vector<string>& wordSet10, vector<string>& wordSet11);
	void fillInTheBlock(vector<string>& wordSet2, vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9, vector<string>& wordSet10, vector<string>& wordSet11);
	int puzzleValidator();
	void showPuzzle();
	void drawPuzzle();
};

#endif