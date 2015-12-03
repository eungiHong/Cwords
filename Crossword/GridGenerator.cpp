#include "GridGenerator.h"

#define horizontal 100
#define vertical -100
#define crossing -50
#define closed -30

// 생성부: 그리드를 그리는 하위부문
GridGenerator::GridGenerator(int length) {  // 생성자
	gridLength = length;
	grid = new char*[gridLength];
	for (int i = 0; i < gridLength; i++) {
		grid[i] = new char[gridLength];  // 이중포인터로 2차원 배열을 동적할당
	}

	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			grid[i][j] = 'O';
		}
	}
}

GridGenerator::~GridGenerator() {   // 소멸자
	for (int i = 0; i < gridLength; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

inline void GridGenerator::closeSquare(int x, int y) {  // 칸 닫기
	grid[x][y] = 'X';
}

void GridGenerator::symmetricalCloser(int x, int y) {  // 대칭하여 닫기, (그리드의 길이가 홀수일 경우만)
	int median = gridLength / 2;
	closeSquare(x, y);
	int rowDifference = median - x;
	int columnDifference = median - y;
	closeSquare(median + rowDifference, median + columnDifference);
}

inline bool GridGenerator::randomlyAndSymmetricallyClose() {  // 무작위로 닫되, 닫힌 칸과 대칭되는 칸도 함께 닫기
	random_device rd;
	mt19937_64 rng(rd());
	uniform_int_distribution<__int64> dist(0, gridLength - 1); // 0에서 (그리드의 길이 - 1)까지의 난수 생성

	int x = dist(rng);
	int y = dist(rng);

	if (grid[x][y] == 'O') {
		symmetricalCloser(x, y);
		return true; // 성공시 true 반환
	}
	return false; // 실패시 (이미 닫혀 있는 경우) false 반환
}

void GridGenerator::recursiveRowCloser(int x, int y) {  // 하나의 행을 한 칸씩 건너뛰어 닫으면서 그와 대칭되는 칸도 함께 닫기
	if (y + 2 <= gridLength + 1) {
		symmetricalCloser(x, y);
		y = y + 2;
		recursiveRowCloser(x, y);
	}
}

void GridGenerator::makeAtOnce() {  // 다양한 메소드를 섞어서 한 번에 그리드 만들기
	// 위에서 아랫방향으로 그리드의 중간선까지 한 칸씩 띄워서 recursiveRowCloser 적용 
	for (int i = 0; i < gridLength / 2 + 1; i += 2) { // (1, 0), 즉 i = 1에서부터 닫아도 좋음
		recursiveRowCloser(i, 0);
	}

	// 한 번 패턴화된 그리드에 대해서 랜덤하게 칸 닫기
	int counter = 0;
	switch (gridLength) { // 그리드의 길이가 11일 경우 i < 9, 13일 경우 i < 14가 적당..
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
	if (wellFormednessValidator() == false) { // 정형의 그리드가 아닐 경우, 초기화 후, 그리드 재생성
		openAtOnce();
		makeAtOnce();
	}
}

void GridGenerator::openAtOnce() { // 그리드 초기화
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			grid[i][j] = 'O';
		}
	}
}
// 생성부 끝

// 블록 추출부 - 생성된 그리드가 가지고 있는 블록에 대한 정보를 벡터vector의 집합set의 형태로 추출하는 하위부문
int GridGenerator::rightwardSquareCounter(int x, int y) { // 입력된 좌표를 포함한 좌표의 오른쪽 행의 빈칸 개수 구하기
	int count = 0;
	if (y < gridLength) {
		if (grid[x][y] == 'O') {
			count++;
			count += rightwardSquareCounter(x, y + 1);
		}
	}
	return count;
}

int GridGenerator::leftwardSquareCounter(int x, int y) { // 입력된 좌표를 포함한 좌표의 왼쪽 행의 빈칸 개수 구하기
	int count = 0;
	if (y > -1) {
		if (grid[x][y] == 'O') {
			count++;
			count += leftwardSquareCounter(x, y - 1);
		}
	}
	return count;
}

int GridGenerator::downwardSquareCounter(int x, int y) { // 입력된 좌표를 포함한 좌표의 아래쪽 열의 빈칸 개수 구하기
	int count = 0;
	if (x < gridLength) {
		if (grid[x][y] == 'O') {
			count++;
			count += downwardSquareCounter(x + 1, y);
		}
	}
	return count;
}

int GridGenerator::upwardSquareCounter(int x, int y) { // 입력된 좌표를 포함한 좌표의 위쪽 열의 빈칸 개수 구하기
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
	// 입력된 좌표와 연결된 행의 빈칸 개수 구하기
	if (grid[x][y] == 'X') {
		return -30;
	}
	else {
		return rightwardSquareCounter(x, y) + leftwardSquareCounter(x, y) - 1;
	}
}

int GridGenerator::verticalSquareCounter(int x, int y) {
	// 입력된 좌표와 연결된 열의 빈칸 개수 구하기
	if (grid[x][y] == 'X') {
		return closed;
	}
	else {
		return downwardSquareCounter(x, y) + upwardSquareCounter(x, y) - 1;
	}
}

int GridGenerator::getBlockType(int x, int y) {
	// 입력된 좌표가 수평방향의 블록과 연결되어 있는지 수직방향의 블록과 연결되어 있는지, 아니면 둘 다 인지 알아내기
	if (horizontalSquareCounter(x, y) > 1 && verticalSquareCounter(x, y) > 1) {
		return crossing; // 수평방향의 블록, 수직방향의 블록 둘 다와 연결되어 있는 경우
	}
	else if (horizontalSquareCounter(x, y) > 1 && verticalSquareCounter(x, y) == 1) {
		return horizontal; // 수평방향의 블록과 연결되어 있는 경우
	}
	else if (horizontalSquareCounter(x, y) == 1 && verticalSquareCounter(x, y) > 1) {
		return vertical; // 수직방향의 블록과 연결되어 있는 경우
	}
	else if (horizontalSquareCounter(x, y) == -30 && verticalSquareCounter(x, y) == -30) {
		return closed; // 좌표가 닫혀있는 경우, 즉 "X" 인경우
	}
}

int GridGenerator::horizontalCoordinateFinder(int x, int y) {
	// 입력된 좌표와 수평선상으로 연결되어 있는 블록의 왼쪽끝 좌표 구하기
	if (grid[x][y] == 'X') { // 입력된 좌표가 닫혀있을 경우
		return -1;
	}
	else {
		for (int i = y; i > -1; i--) {
			if (grid[x][i] == 'X') { // ex) (1,3)에서 "X"를 만났을 경우, 블록의 왼쪽끝 좌표는 (1,4)임
				return i + 1;
			}
		}
		return 0; // "X"를 만나지 않았을 경우, 즉 y축 좌표 0까지 갔을 경우.
	}
}

int GridGenerator::verticalCoordinateFinder(int x, int y) {
	// 입력된 좌표와 수직선상으로 연결되어 있느 블록의 맨 위 좌표 구하기
	if (grid[x][y] == 'X') {
		return -1;
	}
	else {
		for (int i = x; i > -1; i--) {
			if (grid[i][y] == 'X') { // ex) (2,2)에서 "X"를 만났을 경우, 블록의 맨 위 좌표는 (2,3)임
				return i + 1;
			}
		}
		return 0; // "X"를 만나지 않았을 경우, 즉 x축 좌표 0까지 갔을 경우.
	}
}

vector<int> GridGenerator::getInfoOfBlock(int x, int y) { // 입력된 좌표와 연결되어 있는 블록의 정보 획득
												   // 빈칸의 정보: x좌표, y좌표, 길이, 방향(수평, 수직), 교차점의 개수
	int xCoordinate = -1;
	int yCoordinate = -1;
	int length = -1;
	int type = getBlockType(x, y);
	int intersection = -1;

	if (type == horizontal) { // 연결된 블록이 수평인 경우
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
	else if (type == vertical) { // 연결된 블록이 수직인 경우
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
	else if (type == crossing) {  // 좌표가 교차점인 경우는, 정보가 중복되므로 닫힌 칸인 경우와 동일하게 처리
		xCoordinate = 0;
		yCoordinate = 0;
		length = 0;
		type = 0;
		intersection = 0;
	}
	else if (type == closed) { // 닫힌 칸, 즉 "X"인 경우
		xCoordinate = 0;
		yCoordinate = 0;
		length = 0;
		type = 0;
		intersection = 0;
	}

	vector<int> blockInfo; // 교차점, 길이, x 좌표, y 좌표, 유형 순으로 vector에 삽입
	// 이 vector들을 set 자료구조에 저장하기 때문에, 먼저 교차점의 개수에 따라 오름차순으로 정렬, 
	// 그 다음에는 길이의 크기에 따라 오름차순으로 정렬됨.
	// 따라서, 나중에 블록에 낱말을 삽입할 때, 교차점이 많고 길이가 긴 블록부터 낱말을 채우는 것이 유리하기 때문에,
	// 꼬리에서부터 머리 방향으로 set을 순회
	blockInfo.push_back(intersection);
	blockInfo.push_back(length);
	blockInfo.push_back(xCoordinate);
	blockInfo.push_back(yCoordinate);
	blockInfo.push_back(type);
	
	return blockInfo;  // vector 반환
}

set<vector<int>> GridGenerator::getEveryInfoOfBlocks() {
	// 그리드의 모든 좌표(gridLength x gridLength개)를 순회하면서 그리드의 모든 블록 정보 추출
	// set에 정보를 담음으로써 중복되는 블록 정보는 자동적으로 추가되지 않음
	set<vector<int>> everyBlock;
	
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			everyBlock.insert(getInfoOfBlock(i, j));
		}
	}
	return everyBlock;
}
// 블록 추출부 끝

// 그리드 검사부: 생성된 그리드가 제약조건을 만족하는 정형(well-formed)의 그리드인지, 또는 "쓸만한" 그리드인지 검사하는 하위부문
int GridGenerator::closedSquareCounter() { // 닫혀 있는 칸의 개수 새기
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

int GridGenerator::openedSquareCounter() { // 열린 칸의 개수 새기
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

bool GridGenerator::wellFormednessValidator() {  // 그리드가 제약조건을 만족하는 정형의 그리드인지 검사하기
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			vector<int> temp = getInfoOfBlock(i, j);
			int xCoordinate = temp[0];
			int yCoordinate = temp[1];
			int length = temp[2];
			int type = temp[3];
			if (xCoordinate == -1 && yCoordinate == -1 && length == -1 && type == -1) {
				// 고립된 블록(가로 세로의 길이가 1인 블록)이 존재하는 케이스
				return false;
			}
		}
	}
	return true;
}
void GridGenerator::showGrid() { // 그리드를 전시
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}