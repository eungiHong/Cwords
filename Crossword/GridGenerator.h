#pragma once

#ifndef GridGenerator_H
#define GridGenerator_H

#include <vector>
#include <set>
#include <iostream>
#include <random>
#include <fstream>

using namespace std;


class GridGenerator {
private:
	char **grid;
	int gridLength;

	inline void closeSquare(int x, int y);
	void symmetricalCloser(int x, int y);
	inline bool randomlyAndSymmetricallyClose();
	void recursiveRowCloser(int x, int y);
	void openAtOnce();
	int rightwardSquareCounter(int x, int y);
	int leftwardSquareCounter(int x, int y);
	int downwardSquareCounter(int x, int y);
	int upwardSquareCounter(int x, int y);
	int horizontalSquareCounter(int x, int y);
	int verticalSquareCounter(int x, int y);
	int getBlockType(int x, int y);
	vector<int> getInfoOfBlock(int x, int y);
	int horizontalCoordinateFinder(int x, int y);
	int verticalCoordinateFinder(int x, int y);
	bool wellFormednessValidator();

public:
	GridGenerator(int length = 11);
	~GridGenerator();
	void makeAtOnce();
	set<vector<int>> getEveryInfoOfBlocks();
	int closedSquareCounter();
	int openedSquareCounter();
	void drawGrid();
	void showGrid();
	
	
};

#endif