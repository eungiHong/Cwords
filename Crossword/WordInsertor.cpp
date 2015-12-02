#include "WordInsertor.h"

// �׸��� �����: �׸����� �� ��Ͽ� ���� ������ ��� �ִ� ����Ʈ�� ����Ʈ�� �Է� �޾�, �׸��带 �׸��� �ι�
WordInsertor::WordInsertor(int length, int (*blocks)[5]) { // ������
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
inline void WordInsertor::draw(int x, int y) { // ���� ĭ�� ����, i.e., �׸���
	grid[x][y] = 'O';
}
void WordInsertor::blockDrawer() { // ����� ������ ������, ��� �׸���
	for (int i = 20; i > 0; i--) {
		if (blockSet[i][4] == 100) { // ����� ��������� ���,
			for (int j = 0; j < blockSet[i][1]; j++) { // ����� ���̸�ŭ,
				draw(blockSet[i][2], blockSet[i][3] + j); // ���ʿ��� ���������� �׸���
			}
		}
		else if (blockSet[i][4] == -100) { // ����� ���������� ���,
			for (int j = 0; j < blockSet[i][1]; j++) { // ����� ���̸�ŭ,
				draw(blockSet[i][2] + j, blockSet[i][3]); // ������ �Ʒ��� �׸���
			}
		}
	}
}
// �׸��� ����� ��

// ���� ���Ժ�: �׸��� �׸���ο��� �׷��� �׸��忡 ���ؼ� ���� �������κ��� �ܾ ������ �����ϴ� �ι�.
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


void WordInsertor::fillInTheBlock(vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9) { // ��Ͽ� ����ä���
	
	vector<string> wordSetRef3 = wordSet3;
	vector<string> wordSetRef4 = wordSet4;
	vector<string> wordSetRef5 = wordSet5;
	vector<string> wordSetRef6 = wordSet6;
	vector<string> wordSetRef7 = wordSet7;
	vector<string> wordSetRef8 = wordSet8;
	vector<string> wordSetRef9 = wordSet9;

	vector<string>::iterator it;

	for (int i = 20; i > 0; i--) { // ��� ����� ���� �ݺ���
		int row = blockSet[i][2]; // ����� x�� ��ǥ
		int col = blockSet[i][3]; // ����� y�� ��ǥ
		int length = blockSet[i][1]; // ����� ���̿� �´� �������� ����
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
// ���� ���Ժ� ��

// ũ�ν����� �˻��: ���� ���Ժο� ���ؼ� ������ ũ�ν����尡 ������ ũ�ν���������, �� ������ ����� ���ԵǾ����� Ȯ���ϴ� �ι�.
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