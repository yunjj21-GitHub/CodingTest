// 삼성 기출 : 상어 중학교 (완전탐색 + DFS + 정렬 + 구현)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define EMPTY -5

int N, M; // 격자의 크기 N, 일반 블록 색의 수 M(1~M)
int board[50][50]; // 격자의 정보를 저장
bool visit[50][50]; // DFS탐색 시 사용, 각 좌표의 방문 여부를 저장
int blockSize; // 각 블록의 사이즈
int rainbowBlockNum = 0; // 무지개 블록의 수
vector<pair<int, int>> rainbowBlock;
map<pair<int, int>, vector<pair<int, int>>> m;
vector<pair<int, int>> group;
vector<vector<int>> possibleBlock;
int answer = 0;
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

bool cmp(vector<int> a, vector<int> b) {
	if (a[0] == b[0]) {
		if (a[1] == b[1]) {
			if (a[2] == b[2]) {
				return a[3] > b[3]; // 기준블록의 열을 기준으로 내림차순
			}
			return a[2]> b[2]; // 기준블록의 행을 기준으로 내림차순
		}
		return a[1] > b[1]; // 무지개블록의 개수를 기준으로 내림차순
	}
	return a[0] > b[0]; // 블록의 크기를 기준으로 내림차순
}

void getInputValue() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}

void DFS(int y, int x, int color) {
	// 방문했거나, 색이 일치하지 않는데 무지개블록도 아니라면
	if (visit[y][x] ||
		(board[y][x] != color && board[y][x] != 0)) {
		return;
	}

	visit[y][x] = true;

	// 무지개블록이라면
	if (board[y][x] == 0) {
		rainbowBlockNum++;
		rainbowBlock.push_back({ y, x });
	}

	blockSize++;
	group.push_back({ y, x });

	for (int i = 0; i < 4; i++) {
		int nxtY = y + dy[i];
		int nxtX = x + dx[i];

		if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= N) continue;

		DFS(nxtY, nxtX, color);
	}
}

void findBlockGroup() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// 아직 방문하지 않은 일반 블록이라면
			if (!visit[i][j] && 
				(M >= board[i][j] &&
				board[i][j] >= 1)) {
				blockSize = 0;
				rainbowBlockNum = 0;
				rainbowBlock.clear();
				group.clear();
				DFS(i, j, board[i][j]);

				// 무지개 블록 재방문 허용
				for (pair<int, int> rb : rainbowBlock) {
					visit[rb.first][rb.second] = false;
				}

				if (group.size() < 2) continue;

				possibleBlock.push_back({
					blockSize, rainbowBlockNum,
					i, j });
				m[{i, j}] = group;
			}
		}
	}
}

void removeBlock() {
	int startY = possibleBlock[0][2];
	int startX = possibleBlock[0][3];

	vector<pair<int, int>> g = m[{startY, startX}];
	for (int i = 0; i < g.size(); i++) {
		board[g[i].first][g[i].second] = EMPTY;
	}

	answer += (g.size() * g.size());
}

void gravityWorks() {
	// 내릴 블록을 찾는다.
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == -1 || board[i][j] == EMPTY) continue;

			// 해당 블록을 한칸씩 내릴 수 있는지 확인하고 내린다.
			int curI = i; // 내릴 블록이 위치한 행
			while (1) {
				if (curI == N) break;

				// 다음 칸이 비어있지 않다면
				if (board[curI + 1][j] != EMPTY) break;

				// 블록을 내린다.
				int tmp = board[curI + 1][j];
				board[curI + 1][j] = board[curI][j];
				board[curI][j] = tmp;

				curI++;
			}
		}
	}
}

void rotateBoard() {
	int tmp[50][50];
	// 격자를 회전해 본다.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmp[i][j] = board[j][(N - 1) - i];
		}
	}

	// 회전된 격자 정보를 복사한다.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = tmp[i][j];
		}
	}
}

void solution() {
	while (1) {
		// 블록 그룹을 모두 찾는다.
		findBlockGroup();

		if (possibleBlock.size() == 0) break;

		// 제거할 블록을 찾는다.
		sort(possibleBlock.begin(), possibleBlock.end(), cmp);

		// 블록을 제거하고 점수를 획득한다.
		removeBlock();

		// 격자에 중력이 작용한다.
		gravityWorks();

		// 격자가 반시계 방향으로 90도 회전한다.
		rotateBoard();

		// 다시 격자에 중력이 작용한다.
		gravityWorks();

		// 다음 플레이에 필요한 변수 및 배열 초기화
		possibleBlock.clear();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visit[i][j] = false;
			}
		}
		m.clear();
	}
}

int main() {
	getInputValue();

	solution();

	cout << answer << endl;
}