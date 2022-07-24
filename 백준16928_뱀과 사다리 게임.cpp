// 백준 16928 : 뱀과 사다리 게임
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#define MAX 10000000

using namespace std;

int answer = MAX;
int N, M; // 사다리의 수 N, 뱀의 수 M
int map[101]; // 게임판의 정보를 저장, 사용 인덱스 : 1~100
bool visit[101]; // 게임판의 각 칸의 방문 여부를 저장, 사용 인덱스 : 1~100


void getUserInput() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) { // 사다리의 정보를 받아옴
		int x, y;
		cin >> x >> y;
		map[x] = y;

	}
	for (int i = 0; i < M; i++) { // 뱀의 정보를 받아옴
		int u, v;
		cin >> u >> v;
		map[u] = v;
	}
}

void solution() {
	queue<pair<int, int>> q; // {x, cnt};
	q.push({1, 0});
	visit[1] = true;

	while (!q.empty()) {
		int x = q.front().first;
		int cnt = q.front().second;
		q.pop();

		// 100번 칸에 도착했다면
		if (x == 100 && cnt < answer) {
			answer = cnt; // 답안 갱신
			continue;
		}

		for (int d = 1; d <= 6; d++) { // 주사위를 굴린다.
			int nxtX;

			// 다음칸을 구한다.
			if (map[x + d]) { // 사다리 또는 뱀이 있는 칸이라면
				nxtX = map[x + d];
			}
			else { // 아무것도 없는 칸이라면
				nxtX = x + d;
			}

			// 게임판을 벗어나는 영역이라면
			if (nxtX < 1 || nxtX > 100) continue;

			// 이미 방문한 좌표라면
			if (visit[nxtX]) continue;

			q.push({ nxtX, cnt + 1 });
			visit[nxtX] = true;
		}
	}
}

int main() {
	getUserInput();

	solution();

	cout << answer << endl;
} 