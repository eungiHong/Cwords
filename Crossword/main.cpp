#include "GridGenerator.h"
#include "WordInsertor.h"
#include <string>


int main() {
	int gridLength = 11; // 사용자에게 입력받기
	
	GridGenerator puzzle(gridLength);
	puzzle.makeAtOnce();
	puzzle.showGrid();

	// 생성된 그리드의 블록 정보를 텍스트 문서에 출력
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

	// 생성된 그리드에 대해서 낱말을 삽입할지 말지 결정
	cout << "Do you want to continue to make a puzzle?\nIf yes, then type 1.\n";
	int answer;
	cin >> answer;

	if (answer == 1) {
		vector<string> wordSet2;
		vector<string> wordSet3;
		vector<string> wordSet4;
		vector<string> wordSet5;
		vector<string> wordSet6;
		vector<string> wordSet7;
		vector<string> wordSet8;
		vector<string> wordSet9;
		vector<string> wordSet10;
		vector<string> wordSet11;

		// 길이 2에서 11까지의 낱말을 English Words 폴더 안에 있는 낱말 사전에서 읽어 들이기
		string word;
		ifstream fin("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet2.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet2.push_back(word);
		}
		fin.close();
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet3.txt");
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
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet10.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet10.push_back(word);
		}
		fin.close();
		fin.open("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\English Words\\wordSet11.txt");
		while (true) {
			fin >> word;
			if (word == "EOF") break;
			wordSet11.push_back(word);
		}
		fin.close();


		WordInsertor crossword(gridLength, &everyBlock); // WordInsertor 객체 생성
		int i = 0;
		while (true) {
			crossword.blockDrawer();  // 블록 그리기
			crossword.reload(wordSet2, wordSet3, wordSet4, wordSet5, wordSet6, wordSet7, wordSet8, wordSet9, wordSet10, wordSet11); // 낱말 사전 셔플
			crossword.fillInTheBlock(wordSet2, wordSet3, wordSet4, wordSet5, wordSet6, wordSet7, wordSet8, wordSet9, wordSet10, wordSet11); // 블록에 낱말 삽입
			if (crossword.puzzleValidator() == 0) {  // 검사 통과시 생성된 크로스워드를 출력, 실패 시 성공할 때까지 반복
				crossword.showPuzzle();
				crossword.drawPuzzle();
				break;
			}
			i++;
			std::cout << i << endl; // 누적된 크로스워드 생성 실패 횟수 출력
		}
	}
	else return 0;
}