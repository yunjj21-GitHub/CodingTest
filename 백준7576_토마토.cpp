// 백준 7576 : 토마토 (BFS)
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int m, n; // 상자의 가로 크기 m, 세로 크기 n
vector<vector<int>> box; // 상자에 담긴 토마토의 정보를 저장

// BFS 탐색 관련
queue<vector<int>> q; // {y, x, day}

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

void getInputValue();
int solution();

int main() {
	getInputValue();
	
	int result = solution();
	cout << result << endl;
}

void getInputValue() {
	cin >> m >> n;
	box.resize(n, vector<int>(m));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> box[i][j];

			// 해당 칸의 토마토가 익어있다면
			if (box[i][j] == 1) q.push({ i, j, 0}); // {y, x, day}
		}
	}
}

int solution() { // BFS 탐색 이용
	int maxDay = 0;

	while (!q.empty()) {
		int y = q.front()[0];
		int x = q.front()[1];
		int day = q.front()[2];
		q.pop();

		if (maxDay < day) maxDay = day;

		for (int i = 0; i < 4; i++) {
			int nxtY = y + dy[i];
			int nxtX = x + dx[i];

			// 상자 밖의 영역이라면
			if (0 > nxtY || nxtY >= n || 0 > nxtX || nxtX >= m) continue;

			// 익지 않은 토마토가 아니라면
			if (box[nxtY][nxtX] != 0) continue;

			box[nxtY][nxtX] = 1;
			q.push({ nxtY, nxtX, day + 1 });
		}
	}

	// 토마토가 모두 익지 못하는 상황이면
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (box[i][j] == 0) return -1;
		}
	}

	return maxDay;
}