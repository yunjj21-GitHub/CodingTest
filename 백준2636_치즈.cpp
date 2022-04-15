#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define MAX 100

int N, M;
int map[MAX][MAX];
int cheeseNum = 0;
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

vector<int> solution();

int main() {
	vector<int> answer;

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];

			if (map[i][j] == 1) cheeseNum++;
		}
	}

	answer = solution();

	for (int ans : answer) {
		cout << ans << endl;
	}
}

vector<int> solution() {
	vector<int> result(2); // ��ȯ�� ���

	int time = 0; // ���� �ð��� ����

	while (1) {
		queue<pair<int, int>> q; // {y, x}
		vector<vector<bool>> chk(N, vector<bool>(M, 0)); // �� ��ǥ�� �湮 ���θ� ����
		q.push({ 0, 0 });
		chk[0][0] = 1;

		vector<pair<int, int>> disappearing; // ����� ġ���� ��ǥ�� ����

		while (!q.empty()) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int nxtY = y + dy[i];
				int nxtX = x + dx[i];

				if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= M) continue;

				if (chk[nxtY][nxtX]) continue;

				if (map[nxtY][nxtX] == 1) {
					disappearing.push_back({ nxtY, nxtX });
				}
				else { // map[nxtY][nxtX] == 0
					q.push({ nxtY, nxtX }); // Ȯ������ ��ǥ�� 0�� ���� Ž���� ����
				}
				chk[nxtY][nxtX] = 1;
			}
		}

		time++;

		// ��ȯ ��(���) ����
		if (cheeseNum == disappearing.size()) {
			result[0] = time;
			result[1] = disappearing.size();

			break;
		}

		// ���� ����
		cheeseNum -= disappearing.size();
		for (auto spot : disappearing) {
			map[spot.first][spot.second] = 0;
		}
	}

	return result;
}