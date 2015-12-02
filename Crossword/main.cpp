#include "GridGenerator.h"
#include "WordInsertor.h"
#include <set>



int main() {
	int gridLength = 11; // 사용자에게 입력받기
	
	GridGenerator puzzle(gridLength);
	puzzle.makeAtOnce();
	puzzle.showGrid();
	puzzle.drawGrid();

	set<vector<int>> everyBlock;
	set<vector<int>>::iterator it;
	everyBlock = puzzle.getEveryInfoOfBlocks();

	ofstream fout("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\blockInfo.txt");
	for (it = everyBlock.begin(); it != everyBlock.end(); it++) {

		vector<int> aBlock = *it;
		for (int j = 0; j < 4; j++) {
			fout << aBlock[j] << ", ";
		}
		fout << aBlock[4];
		fout << endl;
	}
	/*for (it = everyBlock.begin(); it != everyBlock.end(); it++) {
		vector<int> aBlock = *it;
		for (int j = 0; j < 4; j++) {
			std::cout << aBlock[j] << ", ";
		}
		std::cout << aBlock[4];
		std::cout << endl;
	}*/

	/*cout << "Do you want to continue to make a puzzle?\nIf yes, then enter 1.\n";
	int answer;
	cin >> answer;
	if (answer == 1) {*/

		int blockSet[][5] = {
		{0, 0, 0, 0, 0 },
		{1, 2, 3, 9, 100},
		{1, 2, 7, 0, 100},
		{1, 3, 5, 0, 100},
		{1, 3, 5, 8, 100},
		{2, 3, 1, 3, -100},
		{2, 3, 7, 7, -100},
		{2, 4, 0, 1, -100},
		{2, 4, 1, 7, -100},
		{2, 4, 1, 7, 100},
		{2, 4, 6, 3, -100},
		{2, 4, 7, 9, -100},
		{2, 4, 9, 0, 100},
		{3, 6, 0, 9, -100},
		{3, 6, 1, 0, 100},
		{3, 6, 5, 1, -100},
		{3, 6, 9, 5, 100},
		{4, 8, 3, 0, 100},
		{4, 8, 7, 3, 100},
		{4, 9, 1, 5, -100},
		};

		vector<string> wordSet3;
		vector<string> wordSet4;
		vector<string> wordSet5;
		vector<string> wordSet6;
		vector<string> wordSet7;
		vector<string> wordSet8;
		vector<string> wordSet9;

		string word;

		ifstream fin("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet3.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet3.push_back(word);
		}
		fin.close();
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet4.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet4.push_back(word);
		}
		fin.close();
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet5.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet5.push_back(word);
		}
		fin.close();
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet6.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet6.push_back(word);
		}
		fin.close();
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet7.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet7.push_back(word);
		}
		fin.close();
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet8.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet8.push_back(word);
		}
		fin.close();
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet9.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet9.push_back(word);
		}
		fin.close();

		WordInsertor crossword(gridLength, blockSet);
		int i = 0;
		while (true) {
			crossword.blockDrawer();
			crossword.reload(wordSet3, wordSet4, wordSet5, wordSet6, wordSet7, wordSet8, wordSet9);
			crossword.fillInTheBlock(wordSet3, wordSet4, wordSet5, wordSet6, wordSet7, wordSet8, wordSet9);
			if (crossword.puzzleValidator() == 0) {
				crossword.showPuzzle();
				crossword.drawPuzzle();
				break;
			}
			i++;
			std::cout << i << endl; // 누적실패횟수 출력
		}
	/*}
	else return 0;*/
}