// ���� 16928 : ��� ��ٸ� ����
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#define MAX 10000000

using namespace std;

int answer = MAX;
int N, M; // ��ٸ��� �� N, ���� �� M
int map[101]; // �������� ������ ����, ��� �ε��� : 1~100
bool visit[101]; // �������� �� ĭ�� �湮 ���θ� ����, ��� �ε��� : 1~100


void getUserInput() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) { // ��ٸ��� ������ �޾ƿ�
		int x, y;
		cin >> x >> y;
		map[x] = y;

	}
	for (int i = 0; i < M; i++) { // ���� ������ �޾ƿ�
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

		// 100�� ĭ�� �����ߴٸ�
		if (x == 100 && cnt < answer) {
			answer = cnt; // ��� ����
			continue;
		}

		for (int d = 1; d <= 6; d++) { // �ֻ����� ������.
			int nxtX;

			// ����ĭ�� ���Ѵ�.
			if (map[x + d]) { // ��ٸ� �Ǵ� ���� �ִ� ĭ�̶��
				nxtX = map[x + d];
			}
			else { // �ƹ��͵� ���� ĭ�̶��
				nxtX = x + d;
			}

			// �������� ����� �����̶��
			if (nxtX < 1 || nxtX > 100) continue;

			// �̹� �湮�� ��ǥ���
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