#include "WordInsertor.h"

// 그리드 전사부: 그리드의 각 블록에 대한 정보를 담고 있는 리스트의 리스트를 입력 받아, 그리드를 그리는 부문
WordInsertor::WordInsertor(int length, int (*blocks)[5]) { // 생성자
	gridLength = length;
	grid = new char*[gridLength];
	blockSet = blocks;
	for (int i = 0; i < gridLength; i++) {
		grid[i] = new char[gridLength];
	}

	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			grid[i][j] = 'X';
		}
	}
}
WordInsertor::~WordInsertor() {
	for (int i = 0; i < gridLength; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}
inline void WordInsertor::draw(int x, int y) { // 닫힌 칸을 열기, i.e., 그리기
	grid[x][y] = 'O';
}
void WordInsertor::blockDrawer() { // 블록의 정보를 가지고, 블록 그리기
	for (int i = 20; i > 0; i--) {
		if (blockSet[i][4] == 100) { // 블록이 수평방향일 경우,
			for (int j = 0; j < blockSet[i][1]; j++) { // 블록의 길이만큼,
				draw(blockSet[i][2], blockSet[i][3] + j); // 왼쪽에서 오른쪽으로 그리기
			}
		}
		else if (blockSet[i][4] == -100) { // 블록이 수직방향일 경우,
			for (int j = 0; j < blockSet[i][1]; j++) { // 블록의 길이만큼,
				draw(blockSet[i][2] + j, blockSet[i][3]); // 위에서 아래로 그리기
			}
		}
	}
}
// 그리드 전사부 끝

// 낱말 삽입부: 그리드 그리기부에서 그려진 그리드에 대해서 낱말 사전으로부터 단어를 가져와 삽입하는 부문.
void WordInsertor::reload(vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(wordSet3.begin(), wordSet3.end(), default_random_engine(seed));
	shuffle(wordSet4.begin(), wordSet4.end(), default_random_engine(seed));
	shuffle(wordSet5.begin(), wordSet5.end(), default_random_engine(seed));
	shuffle(wordSet6.begin(), wordSet6.end(), default_random_engine(seed));
	shuffle(wordSet7.begin(), wordSet7.end(), default_random_engine(seed));
	shuffle(wordSet8.begin(), wordSet8.end(), default_random_engine(seed));
	shuffle(wordSet9.begin(), wordSet9.end(), default_random_engine(seed));
}


void WordInsertor::fillInTheBlock(vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9) { // 블록에 낱말채우기
	
	vector<string> wordSetRef3 = wordSet3;
	vector<string> wordSetRef4 = wordSet4;
	vector<string> wordSetRef5 = wordSet5;
	vector<string> wordSetRef6 = wordSet6;
	vector<string> wordSetRef7 = wordSet7;
	vector<string> wordSetRef8 = wordSet8;
	vector<string> wordSetRef9 = wordSet9;

	vector<string>::iterator it;

	for (int i = 20; i > 0; i--) { // 모든 블록을 도는 반복문
		int row = blockSet[i][2]; // 블록의 x축 좌표
		int col = blockSet[i][3]; // 블록의 y축 좌표
		int length = blockSet[i][1]; // 블록의 길이에 맞는 낱말사전 선택
		switch (length) {
		case 3:
			for (it = wordSetRef3.begin(); it != wordSetRef3.end(); it++) {
				string word = *it;
				if (blockSet[i][4] == 100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z);
						}
						it = wordSetRef3.erase(it);
						break;
					}
				}
				else if (blockSet[i][4] == -100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row + k][col] != 'O' && grid[row + k][col] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row + z][col] = word.at(z);
						}
						it = wordSetRef3.erase(it);
						break;
					}
				}
			}
			break;
		case 4:
			for (it = wordSetRef4.begin(); it != wordSetRef4.end(); it++) {
				string word = *it;
				if (blockSet[i][4] == 100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z);
						}
						it = wordSetRef4.erase(it);
						break;
					}
				}
				else if (blockSet[i][4] == -100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row + k][col] != 'O' && grid[row + k][col] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row + z][col] = word.at(z);
						}
						it = wordSetRef4.erase(it);
						break;
					}
				}
			}
			break;
		case 5:
			for (it = wordSetRef5.begin(); it != wordSetRef5.end(); it++) {
				string word = *it;
				if (blockSet[i][4] == 100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z);
						}
						it = wordSetRef5.erase(it);
						break;
					}
				}
				else if (blockSet[i][4] == -100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row + k][col] != 'O' && grid[row + k][col] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row + z][col] = word.at(z);
						}
						it = wordSetRef5.erase(it);
						break;
					}
				}
			}
			break;
		case 6:
			for (it = wordSetRef6.begin(); it != wordSetRef6.end(); it++) {
				string word = *it;
				if (blockSet[i][4] == 100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z);
						}
						it = wordSetRef6.erase(it);
						break;
					}
				}
				else if (blockSet[i][4] == -100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row + k][col] != 'O' && grid[row + k][col] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row + z][col] = word.at(z);
						}
						it = wordSetRef6.erase(it);
						break;
					}
				}
			}
			break;
		case 7:
			for (it = wordSetRef7.begin(); it != wordSetRef7.end(); it++) {
				string word = *it;
				if (blockSet[i][4] == 100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z);
						}
						it = wordSetRef7.erase(it);
						break;
					}
				}
				else if (blockSet[i][4] == -100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row + k][col] != 'O' && grid[row + k][col] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row + z][col] = word.at(z);
						}
						it = wordSetRef7.erase(it);
 						break;
					}
				}
			}
			break;
		case 8:
			for (it = wordSetRef8.begin(); it != wordSetRef8.end(); it++) {
				string word = *it;
				if (blockSet[i][4] == 100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z);
						}
						it = wordSetRef8.erase(it);
						break;
					}
				}
				else if (blockSet[i][4] == -100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row + k][col] != 'O' && grid[row + k][col] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row + z][col] = word.at(z);
						}
						it = wordSetRef8.erase(it);
						break;
					}
				}
			}
			break;
		case 9:
			for (it = wordSetRef9.begin(); it != wordSetRef9.end(); it++) {
				string word = *it;
				if (blockSet[i][4] == 100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z);
						}
						it = wordSetRef9.erase(it);
						break;
					}
				}
				else if (blockSet[i][4] == -100) {
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						if (grid[row + k][col] != 'O' && grid[row + k][col] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) {
						for (int z = 0; z < word.length(); z++) {
							grid[row + z][col] = word.at(z);
						}
						it = wordSetRef9.erase(it);
						break;
					}
				}
			}
			break;
		}
	}
}
// 낱말 삽입부 끝

// 크로스워드 검사부: 낱말 삽입부에 의해서 생성된 크로스워드가 정형의 크로스워드인지, 즉 낱말이 제대로 삽입되었는지 확인하는 부문.
int WordInsertor::puzzleValidator() {
	int errorCount = 0;
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			if (grid[i][j] == 'O') errorCount++;
		}
	}
	return errorCount;
}
void WordInsertor::showPuzzle() {
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}
void WordInsertor::drawPuzzle() {
	ofstream fout("c:\\c_coding\\puzzle.txt");
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			fout << grid[i][j] << " ";
		}
		fout << endl;
	}
}