// 백준 14502 : 연구소 (완전탐색 + BFS)
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int N, M;
vector<vector<int>> map;
queue<pair<int, int>> q; // {y, x}
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };
int answer = 0;

void getSafetyZone(vector<vector<int>> map, queue<pair<int, int>> q) {
	// 바이러스가 퍼진다. (BFS)
	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nxtY = y + dy[i];
			int nxtX = x + dx[i];

			if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= M) continue;

			if (map[nxtY][nxtX] != 0) continue;

			map[nxtY][nxtX] = 2;
			q.push({ nxtY, nxtX });
		}
	}

	// 안전영역의 수를 구한다.
	int safetyZone = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) safetyZone++;
		}
	}

	// 답안 갱신
	if (safetyZone > answer) answer = safetyZone;
}

void solution(int wallNum) {
	if (wallNum == 3) { // 벽 3개가 모두 세워졌다면
		getSafetyZone(map, q);
		return;
	}

	// 벽 3개를 세우는 모든 경우의 수를 구한다. (완전탐색)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1; // 벽을 세운다.	
				solution(wallNum + 1);
				map[i][j] = 0; // 벽을 다시 허문다.
			}
		}
	}
}

int main() {
	cin >> N >> M;
	map.resize(N, vector<int>(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) q.push({ i, j }); // {y, x}
		}
	}

	solution(0);

	cout << answer << endl;
}