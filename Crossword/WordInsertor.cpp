#include "WordInsertor.h"

#define horizontal 100
#define vertical -100
#define crossing -50
#define closed -30

// �׸��� �����: �׸����� �� ��Ͽ� ���� ������ ��� �ִ� ������ ������ �Է� �޾�, �׸��带 �׸��� �ι�
WordInsertor::WordInsertor(int length, set<vector<int>>* blocks) { // ������
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
inline void WordInsertor::draw(int x, int y) { // ���� ĭ�� ����, i.e., �׸���
	grid[x][y] = 'O';
}
void WordInsertor::blockDrawer() { // ����� ������ ������, ��� �׸���
	for (setIterator = (*blockSet).rbegin(); setIterator != (*blockSet).rend(); setIterator++) {
		if ((*setIterator)[4] == horizontal) { // ����� ��������� ���,
			for (int j = 0; j < (*setIterator)[1]; j++) { // ����� ���̸�ŭ,
				draw((*setIterator)[2], (*setIterator)[3] + j); // ���ʿ��� ���������� �׸���
			}
		}
		else if ((*setIterator)[4] == vertical) { // ����� ���������� ���,
			for (int j = 0; j < (*setIterator)[1]; j++) { // ����� ���̸�ŭ,
				draw((*setIterator)[2] + j, (*setIterator)[3]); // ������ �Ʒ��� �׸���
			}
		}
	}
}
// �׸��� ����� ��

// ���� ���Ժ�: �׸��� �׸���ο��� �׷��� �׸��忡 ���ؼ� ���� �������κ��� �ܾ ������ �����ϴ� �ι�.

// main �Լ��� ����� (���ĵǾ� �ִ�) ���� �������� �����Ͽ� ����
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

// ��Ͽ� ���� ä���
void WordInsertor::fillInTheBlock(vector<string>& wordSet2, vector<string>& wordSet3, vector<string>& wordSet4, vector<string>& wordSet5, vector<string>& wordSet6, vector<string>& wordSet7, vector<string>& wordSet8, vector<string>& wordSet9, vector<string>& wordSet10, vector<string>& wordSet11) {
	
	// main �Լ��� ����� ���� �������� �����Ͽ� �Լ� ���� ���� ������� vector�� ����
	// ������ ���� ������ �״�� ����, ���� ���� ���н�, fillInTheBlock �Լ� �۵� �߿� ������ �������� �ٽ� ������ �� ����.
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

	// ��� ����� ���� �ݺ���
	vector<string>::iterator vectorIterator;
	for (setIterator = (*blockSet).rbegin(); setIterator != (*blockSet).rend(); setIterator++) {
		int row = (*setIterator)[2]; // ����� x�� ��ǥ
		int col = (*setIterator)[3]; // ����� y�� ��ǥ
		int length = (*setIterator)[1]; // ����� ���̿� �´� �������� ����
		switch (length) {
		case 2: // ����� ���̰� 2�� ��� ���� 2�� ������ ��� �ִ� ��������(vector) ��ȸ
			for (vectorIterator = wordSetRef2.begin(); vectorIterator != wordSetRef2.end(); vectorIterator++) {
				string word = *vectorIterator;
				if ((*setIterator)[4] == horizontal) { // ����� ������ ���, ����������� ������ �Է�
					int count = 0;
					for (int k = 0; k < word.length(); k++) {
						// k�� ° ĭ�� �̹� �� �ִ� ĭ�̰�, �� ���ڰ� ������ k�� ° ���ڿ� �ٸ� ���, �ٸ� ������ �Ѿ
						if (grid[row][col + k] != 'O' && grid[row][col + k] != word.at(k)) {
							count++;
						}
					}
					if (count == 0) { // �ش� ����� ��� �ְų�, �Է��Ϸ��� ������ ��ġ�� ���
						for (int z = 0; z < word.length(); z++) {
							grid[row][col + z] = word.at(z); // ������ ����
						}
						// ��Ͽ� ������ ������ ���� �������� ����
						vectorIterator = wordSetRef2.erase(vectorIterator);
						break;
					}
				}
				else if ((*setIterator)[4] == vertical) { // ����� ������ ���, ������������ ������ �Է�
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
		case 3: // ����� ���̰� 3�� ���, ���� ����
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
// ���� ���Ժ� ��

// ũ�ν����� �˻��: ���� ���Ժο� ���ؼ� ������ ũ�ν����尡 ������ ũ�ν���������, �� ������ ����� ���ԵǾ����� Ȯ���ϴ� �ι�.

// ������ ä������ ���� �� ĭ�� ������ Ȯ�� (return ���� 0�̾�� ������ ũ�ν�����)
int WordInsertor::puzzleValidator() {
	int errorCount = 0;
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			if (grid[i][j] == 'O') errorCount++;
		}
	}
	return errorCount;
}

// ũ�ν����� �����ֱ�
void WordInsertor::showPuzzle() {
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

// ũ�ν����带 �ؽ�Ʈ ������ ���
void WordInsertor::drawPuzzle() {
	ofstream fout("c:\\Users\\ekhong\\Documents\\Visual Studio 2015\\Projects\\Crossword\\generated_puzzle.txt");
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			fout << grid[i][j] << " ";
		}
		fout << endl;
	}
}
// ũ�ν����� �˻�� ��