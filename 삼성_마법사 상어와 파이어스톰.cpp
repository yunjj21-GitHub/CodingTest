/* // 삼성 기출 : 마법사 상어와 파이어스톰 (구현 + DFS)
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int N, Q;
int mapSize;
int map[100][100];
vector<int> sq;

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

vector<int> answer(2);
bool visit[100][100]; // DFS 탐색 시 사용
int cnt;

void getInputValue() {
	cin >> N >> Q;
	mapSize = pow(2, N);
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		int L;
		cin >> L;
		sq.push_back(pow(2, L));
	}
}

void rotatePartOfMap(int startY, int startX, int PS) {
	// 주어진 격자를 시계방향으로 90도 회전한다.
	vector<vector<int>> tmp(PS, vector<int>(PS));

	// 회전이 완료된 격자를 임시 저장
	for (int i = 0; i < PS; i++) {
		for (int j = 0; j < PS; j++) {
			tmp[i][j] = map[startY + (PS - 1) - j][startX + i];
		}
	}

	// 회전이 완료된 격자를 map에 복사
	for (int i = 0; i < PS; i++) {
		for (int j = 0; j < PS; j++) {
			map[startY + i][startX + j] = tmp[i][j];
		}
	}
}

void meltIce() {
	// 녹일 대상이 되는 얼음의 좌표를 찾는다.
	vector<pair<int, int>> target;
	for (int y = 0; y < mapSize; y++) {
		for (int x = 0; x < mapSize; x++) {

			if (!map[y][x]) continue;

			int ice = 0;
			for (int i = 0; i < 4; i++) {
				int nxtY = y + dy[i];
				int nxtX = x + dx[i];

				if (0 > nxtY || nxtY >= mapSize || 0 > nxtX || nxtX >= mapSize) continue;

				if (map[nxtY][nxtX] <= 0) continue;

				ice++;
			}

			if (ice < 3) target.push_back({ y, x });
		}
	}

	// 얼음을 녹인다.
	for (int i = 0; i < target.size(); i++) {
		map[target[i].first][target[i].second]--;
	}
}

void getAnswer1() {
	int sum = 0;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			sum += map[i][j];
		}
	}
	answer[0] = sum;
}

void DFS(int y, int x) {
	visit[y][x] = true;
	cnt++;

	for (int i = 0; i < 4; i++) {
		int nxtY = y + dy[i];
		int nxtX = x + dx[i];

		if (0 > nxtY || nxtY >= mapSize || 0 > nxtX || nxtX >= mapSize) continue;
		if (!map[nxtY][nxtX] || visit[nxtY][nxtX]) continue;

		DFS(nxtY, nxtX);
	}
}

void getAnswer2() {
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			if (!map[i][j] || visit[i][j]) continue;

			cnt = 0;
			DFS(i, j);
			
			if (cnt > answer[1]) answer[1] = cnt;
		}
	}
}

void solution() {
	for (int partSize : sq) {
		// 파이어스톰을 시전한다.
		for (int y = 0; y < mapSize; y += partSize) {
			for (int x = 0; x < mapSize; x += partSize) {
				rotatePartOfMap(y, x, partSize);
			}
		}

		// 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양이 1 줄어든다.
		meltIce();
	}

	// 남아있는 얼음의 합
	getAnswer1();

	// 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수
	getAnswer2();
}

int main() {
	getInputValue();

	solution();

	// 답안 출력
	for (int ans : answer) {
		cout << ans << endl;
	}
} */