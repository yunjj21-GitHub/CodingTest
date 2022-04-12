// ���� 14502 : ������ (����Ž�� + BFS)
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
	// ���̷����� ������. (BFS)
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

	// ���������� ���� ���Ѵ�.
	int safetyZone = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) safetyZone++;
		}
	}

	// ��� ����
	if (safetyZone > answer) answer = safetyZone;
}

void solution(int wallNum) {
	if (wallNum == 3) { // �� 3���� ��� �������ٸ�
		getSafetyZone(map, q);
		return;
	}

	// �� 3���� ����� ��� ����� ���� ���Ѵ�. (����Ž��)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1; // ���� �����.	
				solution(wallNum + 1);
				map[i][j] = 0; // ���� �ٽ� �㹮��.
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