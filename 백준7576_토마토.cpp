// ���� 7576 : �丶�� (BFS)
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int m, n; // ������ ���� ũ�� m, ���� ũ�� n
vector<vector<int>> box; // ���ڿ� ��� �丶���� ������ ����

// BFS Ž�� ����
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

			// �ش� ĭ�� �丶�䰡 �;��ִٸ�
			if (box[i][j] == 1) q.push({ i, j, 0}); // {y, x, day}
		}
	}
}

int solution() { // BFS Ž�� �̿�
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

			// ���� ���� �����̶��
			if (0 > nxtY || nxtY >= n || 0 > nxtX || nxtX >= m) continue;

			// ���� ���� �丶�䰡 �ƴ϶��
			if (box[nxtY][nxtX] != 0) continue;

			box[nxtY][nxtX] = 1;
			q.push({ nxtY, nxtX, day + 1 });
		}
	}

	// �丶�䰡 ��� ���� ���ϴ� ��Ȳ�̸�
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (box[i][j] == 0) return -1;
		}
	}

	return maxDay;
}