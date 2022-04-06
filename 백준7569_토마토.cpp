// 백준 7569 : 토마토 (BFS + 3차원 배얄)
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// 상자의 가로 칸의 수 M, 세로 칸의 수 N, 쌓아올린 상자의 수 H
int M, N, H;

// 가능한 탐색 경로
int dz[6] = { 1, -1, 0, 0, 0, 0 };
int dy[6] = { 0, 0, 0, 0, 1, -1 };
int dx[6] = { 0, 0, 1, -1, 0, 0 };

// BFS 탐색 시 사용
queue<vector<int>> q; // {h, y, x, day}

int main() {
	// 입력값을 받아옴 (초기화)
	cin >> M >> N >> H;
	// 상자의 각 칸에 대한 정보를 저장
	vector<vector<vector<int>>> box(H, vector<vector<int>>(N, vector<int>(M)));
	for (int z = 0; z < H; z++) { // 쌓아올린 상자 수 만큼
		for (int y = 0; y < N; y++) { // 상자의 세로 길이 만큼
			for (int x = 0; x < M; x++) { // 상자의 가로 길이 만큼
				cin >> box[z][y][x];
				if (box[z][y][x] == 1) q.push({ z, y, x, 0});
			}
		}
	}

	// BFS 탐색
	int result = 0;
	while (!q.empty()) {
		int z = q.front()[0];
		int y = q.front()[1];
		int x = q.front()[2];
		int day = q.front()[3];
		q.pop();

		if (day > result) result = day;

		for (int i = 0; i < 6; i++) {
			int nxtZ = z + dz[i];
			int nxtY = y + dy[i];
			int nxtX = x + dx[i];

			// 탐색 가능한 범위가 아니라면
			if (nxtZ < 0 || nxtZ >= H ||
				nxtY < 0 || nxtY >= N ||
				nxtX < 0 || nxtX >= M) continue;
			
			// 안익은 토마토가 아니라면
			if (box[nxtZ][nxtY][nxtX] != 0) continue;

			q.push({ nxtZ, nxtY, nxtX, day + 1 });
			box[nxtZ][nxtY][nxtX] = 1; // 익은 토마토로 처리
		}
	}

	// 익지 않은 토마토가 있는지 확인
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int z = 0; z < M; z++) {
				if (box[i][j][z] == 0) result = -1;
			}
		}
	}

	// 결과 출력
	cout << result << endl;
}