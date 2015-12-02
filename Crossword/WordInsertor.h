#pragma once

#ifndef WordInsertor_H
#define WordInsertor_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

class WordInsertor {
private:
	char **grid;
	int gridLength;
	int (*blockSet)[5];
	inline void draw(int x, int y);

public:
	WordInsertor(int length, int (*blocks)[5]);
	~WordInsertor();
	void blockDrawer();
	void reload(vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9);
	void fillInTheBlock(vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9);
	int puzzleValidator();
	void showPuzzle();
	void drawPuzzle();
};

#endif