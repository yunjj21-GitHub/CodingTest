// 삼성 기출 : 마법사 상어와 비바라기 (구현 + deque)
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

int N, M; // 격자의 크기 N, 물의 이동 횟수 M;
int map[50][50]; // 물의 정보를 담는 배열
deque<pair<int, int>> cmd; // 구름의 이동 정보를 저장

// 좌, 대각선상좌, 상, 대각선상우, 우, 대각선하우, 하, 대각선하좌
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

bool removed[50][50]; // 구름이 사라진 좌표를 기억
int answer = 0; // 답안

void getInputValue() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int dir, s;
		cin >> dir >> s;
		cmd.push_back({ dir, s });
	}
}

void solution() {
	// 구름의 초기 위치 설정
	deque<pair<int, int>> cloud = { 
		{N - 2, 0}, {N - 2, 1}, {N - 1, 0}, {N - 1, 1} 
	};

	while (!cmd.empty()) {
		// 1. 모든 구름이 dir 방향으로 s칸 이동한다.
		int dir = cmd.front().first - 1;
		int s = cmd.front().second % N;
		cmd.pop_front();

		for (int i = 0; i < cloud.size(); i++) {
			cloud[i].first += (dy[dir] * s);
			cloud[i].second += (dx[dir] * s);

			// 구름의 경계 넘음을 처리
			if (cloud[i].first < 0) cloud[i].first += N;
			else if (cloud[i].first >= N) cloud[i].first -= N;

			if (cloud[i].second < 0) cloud[i].second += N;
			else if (cloud[i].second >= N) cloud[i].second -= N;
		}

		// 2. 각 구름에서 비가 내려 구름이 있는 칸의 바구니에 저장된 물의 양이 1 증가한다.
		for (int i = 0; i < cloud.size(); i++) {
			map[cloud[i].first][cloud[i].second]++;
			// 3. 구름이 모두 사라진다.
			removed[cloud[i].first][cloud[i].second] = true; // 구름이 사라진 좌표 기억
		}

		// 4. 2에서 물이 증가한 칸에 물복사버그 마법을 시전한다.
		for (int i = 0; i < cloud.size(); i++) {
			int cnt = 0;
			for (int j = 1; j <= 7; j += 2) { // 1, 3, 5, 7
				int chkY = cloud[i].first + dy[j];
				int chkX = cloud[i].second + dx[j];

				if (0 > chkY || chkY >= N || 0 > chkX || chkX >= N) continue;

				if (map[chkY][chkX] > 0) cnt++;
			}
			map[cloud[i].first][cloud[i].second] += cnt;
		}

		int preCloudSize = cloud.size();

		// 5. 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름이 생기고, 물의 양이 2 줄어든다.
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] >= 2 && !removed[i][j]) {
					map[i][j] -= 2;
					cloud.push_back({ i, j });
				}
			}
		}

		// 3의 구름 사라짐과 visit 배열 초기화
		for (int i = 0; i < preCloudSize; i++) {
			removed[cloud.front().first][cloud.front().second] = false;
			cloud.pop_front();
		}
	}
}

void getAnswer() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			answer += map[i][j];
		}
	}
}

int main() {
	getInputValue(); // 입력값을 받아옴

	solution();

	getAnswer();

	cout << answer << endl;
}