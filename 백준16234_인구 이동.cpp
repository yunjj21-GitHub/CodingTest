// 백준 16234 : 인구 이동 (BFS)
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

int N; // 땅의 크기
int L, R; // 연합을 이룰수 있는 인구 차의 최소, 최대
int map[50][50]; // 인구 정보를 저장
bool finish[50][50] = {0}; // 연합국 탐색이 끝난 나라를 저장
// 연합국 탐색 경로를 저장
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };
int answer = 0; // 인구이동에 소요되는 날

bool flag = 0;

void solution();
void exploreIfAllyCanBeCreated(int y, int x);

int main(){
	// 입력값을 받아옴
	cin >> N;
	cin >> L >> R;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}

	solution();

	// 답안 출력
	cout << answer << endl;
}

void solution() {
	while (1) {
		// 연합국 탐색이 완료되지 않은 나라를 대상으로 연합국 탐색
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (!finish[y][x]) exploreIfAllyCanBeCreated(y, x);
			}
		}

		// 모든 나라를 기준으로 연합이 일어나지 않았다면 인구이동 종료
		if (!flag) break;

		// 다음 탐색에 사용될 변수 초기화
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				finish[i][j] = 0;
			}
		}
		flag = 0;

		// 소요되는 날 갱신
		answer++;
	}
}

void exploreIfAllyCanBeCreated(int y, int x) {
	vector<pair<int, int>> ally; // 탐색중인 나라와 연합을 맺은 국가를 저장
	ally.push_back({ y, x });
	int tot = map[y][x]; // 연합에 속한 나라들의 총 인구수

	// 연합국 탐색 (BFS)
	queue<pair<int, int>> q; // {y, x}
	q.push({ y, x });
	finish[y][x] = 1;

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nxtY = y + dy[i];
			int nxtX = x + dx[i];

			if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= N) continue;

			if (finish[nxtY][nxtX]) continue;

			int dif = abs(map[nxtY][nxtX] - map[y][x]);
			if (L > dif || dif > R) continue;

			ally.push_back({ nxtY, nxtX });
			tot += map[nxtY][nxtX];

			q.push({ nxtY, nxtX });
			finish[nxtY][nxtX] = 1; // 탐색 완료 처리
		}
	}

	// 연합이 발생했는지 확인
	if (ally.size() > 1) flag = 1;

	// 인구 이동
	for (auto country : ally) {
		map[country.first][country.second] = tot / ally.size();
	}
}