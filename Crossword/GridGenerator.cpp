#include "GridGenerator.h"

#define horizontal 100
#define vertical -100
#define crossing -50
#define closed -30

// ������: �׸��带 �׸��� �����ι�
GridGenerator::GridGenerator(int length) {  // ������
	gridLength = length;
	grid = new char*[gridLength];
	for (int i = 0; i < gridLength; i++) {
		grid[i] = new char[gridLength];  // ���������ͷ� 2���� �迭�� �����Ҵ�
	}

	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			grid[i][j] = 'O';
		}
	}
}

GridGenerator::~GridGenerator() {   // �Ҹ���
	for (int i = 0; i < gridLength; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

inline void GridGenerator::closeSquare(int x, int y) {  // ĭ �ݱ�
	grid[x][y] = 'X';
}

void GridGenerator::symmetricalCloser(int x, int y) {  // ��Ī�Ͽ� �ݱ�, (�׸����� ���̰� Ȧ���� ��츸)
	int median = gridLength / 2;
	closeSquare(x, y);
	int rowDifference = median - x;
	int columnDifference = median - y;
	closeSquare(median + rowDifference, median + columnDifference);
}

inline bool GridGenerator::randomlyAndSymmetricallyClose() {  // �������� �ݵ�, ���� ĭ�� ��Ī�Ǵ� ĭ�� �Բ� �ݱ�
	random_device rd;
	mt19937_64 rng(rd());
	uniform_int_distribution<__int64> dist(0, gridLength - 1); // 0���� (�׸����� ���� - 1)������ ���� ����

	int x = dist(rng);
	int y = dist(rng);

	if (grid[x][y] == 'O') {
		symmetricalCloser(x, y);
		return true; // ������ true ��ȯ
	}
	return false; // ���н� (�̹� ���� �ִ� ���) false ��ȯ
}

void GridGenerator::recursiveRowCloser(int x, int y) {  // �ϳ��� ���� �� ĭ�� �ǳʶپ� �����鼭 �׿� ��Ī�Ǵ� ĭ�� �Բ� �ݱ�
	if (y + 2 <= gridLength + 1) {
		symmetricalCloser(x, y);
		y = y + 2;
		recursiveRowCloser(x, y);
	}
}

void GridGenerator::makeAtOnce() {  // �پ��� �޼ҵ带 ��� �� ���� �׸��� �����
	// ������ �Ʒ��������� �׸����� �߰������� �� ĭ�� ����� recursiveRowCloser ���� 
	for (int i = 0; i < gridLength / 2 + 1; i += 2) { // (1, 0), �� i = 1�������� �ݾƵ� ����
		recursiveRowCloser(i, 0);
	}

	// �� �� ����ȭ�� �׸��忡 ���ؼ� �����ϰ� ĭ �ݱ�
	int counter = 0;
	switch (gridLength) { // �׸����� ���̰� 11�� ��� i < 9, 13�� ��� i < 14�� ����..
	case 11:
		while (true) {
			if(randomlyAndSymmetricallyClose() == true) counter++;
			if (counter == 9) break;
		}
		break;
	case 13:
		while (true) {
			if (randomlyAndSymmetricallyClose() == true) counter++;
			if (counter == 14) break;
		}
		break;
	case 15:
		while (true) {
			if (randomlyAndSymmetricallyClose() == true) counter++;
			if (counter == 21) break;
		}
		break;
	case 17:
		while (true) {
			if (randomlyAndSymmetricallyClose() == true) counter++;
			if (counter == 29) break;
		}
		break;
	case 19:
		while (true) {
			if (randomlyAndSymmetricallyClose() == true) counter++;
			if (counter == 34) break;
		}
		break;
	}
	if (wellFormednessValidator() == false) { // ������ �׸��尡 �ƴ� ���, �ʱ�ȭ ��, �׸��� �����
		openAtOnce();
		makeAtOnce();
	}
}

void GridGenerator::openAtOnce() { // �׸��� �ʱ�ȭ
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			grid[i][j] = 'O';
		}
	}
}
// ������ ��

// ��� ����� - ������ �׸��尡 ������ �ִ� ��Ͽ� ���� ������ ����vector�� ����set�� ���·� �����ϴ� �����ι�
int GridGenerator::rightwardSquareCounter(int x, int y) { // �Էµ� ��ǥ�� ������ ��ǥ�� ������ ���� ��ĭ ���� ���ϱ�
	int count = 0;
	if (y < gridLength) {
		if (grid[x][y] == 'O') {
			count++;
			count += rightwardSquareCounter(x, y + 1);
		}
	}
	return count;
}

int GridGenerator::leftwardSquareCounter(int x, int y) { // �Էµ� ��ǥ�� ������ ��ǥ�� ���� ���� ��ĭ ���� ���ϱ�
	int count = 0;
	if (y > -1) {
		if (grid[x][y] == 'O') {
			count++;
			count += leftwardSquareCounter(x, y - 1);
		}
	}
	return count;
}

int GridGenerator::downwardSquareCounter(int x, int y) { // �Էµ� ��ǥ�� ������ ��ǥ�� �Ʒ��� ���� ��ĭ ���� ���ϱ�
	int count = 0;
	if (x < gridLength) {
		if (grid[x][y] == 'O') {
			count++;
			count += downwardSquareCounter(x + 1, y);
		}
	}
	return count;
}

int GridGenerator::upwardSquareCounter(int x, int y) { // �Էµ� ��ǥ�� ������ ��ǥ�� ���� ���� ��ĭ ���� ���ϱ�
	int count = 0;
	if (x > -1) {
		if (grid[x][y] == 'O') {
			count++;
			count += upwardSquareCounter(x - 1, y);
		}
	}
	return count;
}

int GridGenerator::horizontalSquareCounter(int x, int y) {
	// �Էµ� ��ǥ�� ����� ���� ��ĭ ���� ���ϱ�
	if (grid[x][y] == 'X') {
		return -30;
	}
	else {
		return rightwardSquareCounter(x, y) + leftwardSquareCounter(x, y) - 1;
	}
}

int GridGenerator::verticalSquareCounter(int x, int y) {
	// �Էµ� ��ǥ�� ����� ���� ��ĭ ���� ���ϱ�
	if (grid[x][y] == 'X') {
		return closed;
	}
	else {
		return downwardSquareCounter(x, y) + upwardSquareCounter(x, y) - 1;
	}
}

int GridGenerator::getBlockType(int x, int y) {
	// �Էµ� ��ǥ�� ��������� ��ϰ� ����Ǿ� �ִ��� ���������� ��ϰ� ����Ǿ� �ִ���, �ƴϸ� �� �� ���� �˾Ƴ���
	if (horizontalSquareCounter(x, y) > 1 && verticalSquareCounter(x, y) > 1) {
		return crossing; // ��������� ���, ���������� ��� �� �ٿ� ����Ǿ� �ִ� ���
	}
	else if (horizontalSquareCounter(x, y) > 1 && verticalSquareCounter(x, y) == 1) {
		return horizontal; // ��������� ��ϰ� ����Ǿ� �ִ� ���
	}
	else if (horizontalSquareCounter(x, y) == 1 && verticalSquareCounter(x, y) > 1) {
		return vertical; // ���������� ��ϰ� ����Ǿ� �ִ� ���
	}
	else if (horizontalSquareCounter(x, y) == -30 && verticalSquareCounter(x, y) == -30) {
		return closed; // ��ǥ�� �����ִ� ���, �� "X" �ΰ��
	}
}

int GridGenerator::horizontalCoordinateFinder(int x, int y) {
	// �Էµ� ��ǥ�� ���򼱻����� ����Ǿ� �ִ� ����� ���ʳ� ��ǥ ���ϱ�
	if (grid[x][y] == 'X') { // �Էµ� ��ǥ�� �������� ���
		return -1;
	}
	else {
		for (int i = y; i > -1; i--) {
			if (grid[x][i] == 'X') { // ex) (1,3)���� "X"�� ������ ���, ����� ���ʳ� ��ǥ�� (1,4)��
				return i + 1;
			}
		}
		return 0; // "X"�� ������ �ʾ��� ���, �� y�� ��ǥ 0���� ���� ���.
	}
}

int GridGenerator::verticalCoordinateFinder(int x, int y) {
	// �Էµ� ��ǥ�� ������������ ����Ǿ� �ִ� ����� �� �� ��ǥ ���ϱ�
	if (grid[x][y] == 'X') {
		return -1;
	}
	else {
		for (int i = x; i > -1; i--) {
			if (grid[i][y] == 'X') { // ex) (2,2)���� "X"�� ������ ���, ����� �� �� ��ǥ�� (2,3)��
				return i + 1;
			}
		}
		return 0; // "X"�� ������ �ʾ��� ���, �� x�� ��ǥ 0���� ���� ���.
	}
}

vector<int> GridGenerator::getInfoOfBlock(int x, int y) { // �Էµ� ��ǥ�� ����Ǿ� �ִ� ����� ���� ȹ��
												   // ��ĭ�� ����: x��ǥ, y��ǥ, ����, ����(����, ����), �������� ����
	int xCoordinate = -1;
	int yCoordinate = -1;
	int length = -1;
	int type = getBlockType(x, y);
	int intersection = -1;

	if (type == horizontal) { // ����� ����� ������ ���
		xCoordinate = x;
		yCoordinate = horizontalCoordinateFinder(x, y);
		length = horizontalSquareCounter(x, y);
		int count = 0;
		for (int i = yCoordinate; i < length + yCoordinate; i++) {
			if (verticalSquareCounter(xCoordinate, i) > 1) {
				count++;
			}
		}
		intersection = count;
	}
	else if (type == vertical) { // ����� ����� ������ ���
		xCoordinate = verticalCoordinateFinder(x, y);
		yCoordinate = y;
		length = verticalSquareCounter(x, y);
		int count = 0;
		for (int i = xCoordinate; i < length + xCoordinate; i++) {
			if (horizontalSquareCounter(i, yCoordinate) > 1) {
				count++;
			}
		}
		intersection = count;
	}
	else if (type == crossing) {  // ��ǥ�� �������� ����, ������ �ߺ��ǹǷ� ���� ĭ�� ���� �����ϰ� ó��
		xCoordinate = 0;
		yCoordinate = 0;
		length = 0;
		type = 0;
		intersection = 0;
	}
	else if (type == closed) { // ���� ĭ, �� "X"�� ���
		xCoordinate = 0;
		yCoordinate = 0;
		length = 0;
		type = 0;
		intersection = 0;
	}

	vector<int> blockInfo; // ������, ����, x ��ǥ, y ��ǥ, ���� ������ vector�� ����
	// �� vector���� set �ڷᱸ���� �����ϱ� ������, ���� �������� ������ ���� ������������ ����, 
	// �� �������� ������ ũ�⿡ ���� ������������ ���ĵ�.
	// ����, ���߿� ��Ͽ� ������ ������ ��, �������� ���� ���̰� �� ��Ϻ��� ������ ä��� ���� �����ϱ� ������,
	// ������������ �Ӹ� �������� set�� ��ȸ
	blockInfo.push_back(intersection);
	blockInfo.push_back(length);
	blockInfo.push_back(xCoordinate);
	blockInfo.push_back(yCoordinate);
	blockInfo.push_back(type);
	
	return blockInfo;  // vector ��ȯ
}

set<vector<int>> GridGenerator::getEveryInfoOfBlocks() {
	// �׸����� ��� ��ǥ(gridLength x gridLength��)�� ��ȸ�ϸ鼭 �׸����� ��� ��� ���� ����
	// set�� ������ �������ν� �ߺ��Ǵ� ��� ������ �ڵ������� �߰����� ����
	set<vector<int>> everyBlock;
	
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			everyBlock.insert(getInfoOfBlock(i, j));
		}
	}
	return everyBlock;
}
// ��� ����� ��

// �׸��� �˻��: ������ �׸��尡 ���������� �����ϴ� ����(well-formed)�� �׸�������, �Ǵ� "������" �׸������� �˻��ϴ� �����ι�
int GridGenerator::closedSquareCounter() { // ���� �ִ� ĭ�� ���� ����
	int count = 0;
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			if (grid[i][j] == 'X') {
				count++;
			}
		}
	}
	return count;
}

int GridGenerator::openedSquareCounter() { // ���� ĭ�� ���� ����
	int count = 0;
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			if (grid[i][j] == 'O') {
				count++;
			}
		}
	}
	return count;
}

bool GridGenerator::wellFormednessValidator() {  // �׸��尡 ���������� �����ϴ� ������ �׸������� �˻��ϱ�
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			vector<int> temp = getInfoOfBlock(i, j);
			int xCoordinate = temp[0];
			int yCoordinate = temp[1];
			int length = temp[2];
			int type = temp[3];
			if (xCoordinate == -1 && yCoordinate == -1 && length == -1 && type == -1) {
				// ���� ���(���� ������ ���̰� 1�� ���)�� �����ϴ� ���̽�
				return false;
			}
		}
	}
	return true;
}
void GridGenerator::showGrid() { // �׸��带 ����
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}