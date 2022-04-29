// 삼성 기출 : 어항 정리 (구현)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };
int N, K;
vector<vector<int>> board;
int answer = 0;

bool isItEnd() {
	int maxFish = *max_element(board[0].begin(), board[0].end());
	int minFish = *min_element(board[0].begin(), board[0].end());

	return (maxFish - minFish <= K);
}

void moveFish() {
	vector<vector<int>> newBoard = board;

	// 물고기를 이동시킨다.
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (board[y][x] == -1) continue;

			for (int d = 0; d < 4; d++) {
				int nxtY = y + dy[d];
				int nxtX = x + dx[d];

				if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= N) continue;
				if (board[nxtY][nxtX] == -1) continue;

				newBoard[y][x] += ((board[nxtY][nxtX] - board[y][x]) / 5);
			}
		}
	}

	// 어항을 일자로 핀다.
	vector<int> flatBoard;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			if (newBoard[y][x] == -1) continue;
			else flatBoard.push_back(newBoard[y][x]);
		}
	}

	board = vector<vector<int>>(N, vector<int>(N, -1));
	board[0] = flatBoard;
}

void move() {
	int lenY = 1, lenX = 1;
	int startX = 0;

	// 1. 물고기를 추가한다.
	int minFish = *min_element(board[0].begin(), board[0].end());
	for (int i = 0; i < N; i++) {
		if (board[0][i] == minFish) board[0][i]++;
	}

	// 2. 어항을 말며 움직인다.
	while (startX + lenY + lenX <= N) {
		for (int y = 0; y < lenY; y++) {
			for (int x = 0; x < lenX; x++) {
				int nxtY = lenX - x;
				int nxtX = startX + lenX + y;

				board[nxtY][nxtX] = board[y][x + startX];
				board[y][x + startX] = -1;
			}
		}

		startX += lenX;
		if (lenY == lenX) lenY++;
		else lenX++;
	}

	// 3. 물고기를 이동시킨다.
	moveFish();

	// 4. 중심을 기준으로 어항 2번 움직인다.
	startX = 0;
	lenY = 1;
	lenX = N / 2;

	for (int i = 0; i < 2; i++) {

		for (int y = 0; y < lenY; y++) {
			for (int x = 0; x < lenX; x++) {
				int nxtY = 2 * lenY - y - 1;
				int nxtX = 2 * lenX + startX - x - 1;
				board[nxtY][nxtX] = board[y][x + startX];
				board[y][x + startX] = -1;
			}
		}
		startX += lenX;
		lenX /= 2;
		lenY *= 2;
	}

	// 5. 물고기를 이동시킨다.
	moveFish();
}

void solution() {
	while (!isItEnd()) {
		answer++;
		move();
	}
}

int main() {
	cin >> N >> K;
	board = vector<vector<int>>(N, vector<int>(N, -1));
	for (int i = 0; i < N; i++) {
		cin >> board[0][i];
	}
	solution();

	cout << answer << endl;
}