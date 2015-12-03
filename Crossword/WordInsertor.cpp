#include "WordInsertor.h"

#define horizontal 100
#define vertical -100
#define crossing -50
#define closed -30

// 그리드 전사부: 그리드의 각 블록에 대한 정보를 담고 있는 벡터의 집합을 입력 받아, 그리드를 그리는 부문
WordInsertor::WordInsertor(int length, set<vector<int>>* blocks) { // 생성자
	gridLength = length;
	grid = new char*[gridLength];
	blockSet = blocks;
	for (int i = 0; i < gridLength; i++) {
		grid[i] = new char[gridLength];
	}

	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			grid[i][j] = '*';
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
	for (setIterator = (*blockSet).rbegin(); setIterator != (*blockSet).rend(); setIterator++) {
		if ((*setIterator)[4] == horizontal) { // 블록이 수평방향일 경우,
			for (int j = 0; j < (*setIterator)[1]; j++) { // 블록의 길이만큼,
				draw((*setIterator)[2], (*setIterator)[3] + j); // 왼쪽에서 오른쪽으로 그리기
			}
		}
		else if ((*setIterator)[4] == vertical) { // 블록이 수직방향일 경우,
			for (int j = 0; j < (*setIterator)[1]; j++) { // 블록의 길이만큼,
				draw((*setIterator)[2] + j, (*setIterator)[3]); // 위에서 아래로 그리기
			}
		}
	}
}
// 그리드 전사부 끝

// 낱말 삽입부: 그리드 그리기부에서 그려진 그리드에 대해서 낱말 사전으로부터 단어를 가져와 삽입하는 부문.

// main 함수에 선언된 (정렬되어 있는) 낱말 사전들을 참조하여 셔플
void WordInsertor::reload(vector<string>& wordSet2, vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9, vector<string>& wordSet10, vector<string>& wordSet11) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(wordSet2.begin(), wordSet2.end(), default_random_engine(seed));
	shuffle(wordSet3.begin(), wordSet3.end(), default_random_engine(seed));
	shuffle(wordSet4.begin(), wordSet4.end(), default_random_engine(seed));
	shuffle(wordSet5.begin(), wordSet5.end(), default_random_engine(seed));
	shuffle(wordSet6.begin(), wordSet6.end(), default_random_engine(seed));
	shuffle(wordSet7.begin(), wordSet7.end(), default_random_engine(seed));
	shuffle(wordSet8.begin(), wordSet8.end(), default_random_engine(seed));
	shuffle(wordSet9.begin(), wordSet9.end(), default_random_engine(seed));
	shuffle(wordSet10.begin(), wordSet10.end(), default_random_engine(seed));
	shuffle(wordSet11.begin(), wordSet11.end(), default_random_engine(seed));
}

// 블록에 낱말 채우기
void WordInsertor::fillInTheBlock(vector<string>& wordSet2, vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9, vector<string>& wordSet10, vector<string>& wordSet11) {
	
	// main 함수에 선언된 낱말 사전들을 참조하여 함수 내에 새로 만들어진 vector에 복사
	// 참조한 낱말 사전을 그대로 쓰면, 퍼즐 생성 실패시, fillInTheBlock 함수 작동 중에 삭제한 낱말들을 다시 복원할 수 없음.
	vector<string> wordSetRef2 = wordSet2;
	vector<string> wordSetRef3 = wordSet3;
	vector<string> wordSetRef4 = wordSet4;
	vector<string> wordSetRef5 = wordSet5;
	vector<string> wordSetRef6 = wordSet6;
	vector<string> wordSetRef7 = wordSet7;
	vector<string> wordSetRef8 = wordSet8;
	vector<string> wordSetRef9 = wordSet9;
	vector<string> wordSetRef10 = wordSet10;
	vector<string> wordSetRef11 = wordSet11;

	// 모든 블록을 도는 반복문
	vector<string>::iterator vectorIterator;
	for (setIterator = (*blockSet).rbegin(); setIterator != (*blockSet).rend(); setIterator++) {
		int row = (*setIterator)[2]; // 블록의 x축 좌표
		int col = (*setIterator)[3]; // 블록의 y축 좌표
		int length = (*setIterator)[1]; // 블록의 길이에 맞는 낱말사전 선택
		switch (length) {
		case 2: // 블록의 길이가 2일 경우 길이 2인 낱말을 담고 있는 낱말사전(vector) 순회
			for (vectorIterator = wordSetRef2.begin(); vectorIterator != wordSetRef2.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == horizontal) { // 블록이 수평일 경우, 수평방향으로 낱말을 입력
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						// k번 째 칸이 이미 차 있는 칸이고, 그 문자가 낱말의 k번 째 문자와 다를 경우, 다른 낱말로 넘어감
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) { // 해당 블록이 비어 있거나, 입력하려는 낱말과 일치할 경우
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z); // 낱말을 삽입
						}
						// 블록에 삽입한 낱말을 낱말 사전에서 삭제
						vectorIterator = wordSetRef2.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == vertical) { // 블록이 수직일 경우, 수직방향으로 낱말을 입력
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
						vectorIterator = wordSetRef2.erase(vectorIterator);
						break;
					}
				}
			}
			break;
		case 3: // 블록의 길이가 3인 경우, 위와 동일
			for (vectorIterator = wordSetRef3.begin(); vectorIterator != wordSetRef3.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef3.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef3.erase(vectorIterator);
						break;
					}
				}
			}
			break;
		case 4:
			for (vectorIterator = wordSetRef4.begin(); vectorIterator != wordSetRef4.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef4.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef4.erase(vectorIterator);
						break;
					}
				}
			}
			break;
		case 5:
			for (vectorIterator = wordSetRef5.begin(); vectorIterator != wordSetRef5.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef5.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef5.erase(vectorIterator);
						break;
					}
				}
			}
			break;
		case 6:
			for (vectorIterator = wordSetRef6.begin(); vectorIterator != wordSetRef6.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef6.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef6.erase(vectorIterator);
						break;
					}
				}
			}
			break;
		case 7:
			for (vectorIterator = wordSetRef7.begin(); vectorIterator != wordSetRef7.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef7.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef7.erase(vectorIterator);
 						break;
					}
				}
			}
			break;
		case 8:
			for (vectorIterator = wordSetRef8.begin(); vectorIterator != wordSetRef8.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef8.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef8.erase(vectorIterator);
						break;
					}
				}
			}
			break;
		case 9:
			for (vectorIterator = wordSetRef9.begin(); vectorIterator != wordSetRef9.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef9.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef9.erase(vectorIterator);
						break;
					}
				}
			}
			break;
		case 10:
			for (vectorIterator = wordSetRef10.begin(); vectorIterator != wordSetRef10.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef10.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef10.erase(vectorIterator);
						break;
					}
				}
			}
			break;
		case 11:
			for (vectorIterator = wordSetRef11.begin(); vectorIterator != wordSetRef11.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == 100) {
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
						vectorIterator = wordSetRef11.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == -100) {
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
						vectorIterator = wordSetRef11.erase(vectorIterator);
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

// 낱말로 채워지지 않은 빈 칸의 개수를 확인 (return 값이 0이어야 정형의 크로스워드)
int WordInsertor::puzzleValidator() {
	int errorCount = 0;
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			if (grid[i][j] == 'O') errorCount++;
		}
	}
	return errorCount;
}

// 크로스워드 보여주기
void WordInsertor::showPuzzle() {
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

// 크로스워드를 텍스트 문서에 출력
void WordInsertor::drawPuzzle() {
	ofstream fout("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\generated_puzzle.txt");
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			fout << grid[i][j] << " ";
		}
		fout << endl;
	}
}
// 크로스워드 검사부 끝