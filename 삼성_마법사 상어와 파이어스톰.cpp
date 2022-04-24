/* // �Ｚ ���� : ������ ���� ���̾�� (���� + DFS)
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int N, Q;
int mapSize;
int map[100][100];
vector<int> sq;

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

vector<int> answer(2);
bool visit[100][100]; // DFS Ž�� �� ���
int cnt;

void getInputValue() {
	cin >> N >> Q;
	mapSize = pow(2, N);
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		int L;
		cin >> L;
		sq.push_back(pow(2, L));
	}
}

void rotatePartOfMap(int startY, int startX, int PS) {
	// �־��� ���ڸ� �ð�������� 90�� ȸ���Ѵ�.
	vector<vector<int>> tmp(PS, vector<int>(PS));

	// ȸ���� �Ϸ�� ���ڸ� �ӽ� ����
	for (int i = 0; i < PS; i++) {
		for (int j = 0; j < PS; j++) {
			tmp[i][j] = map[startY + (PS - 1) - j][startX + i];
		}
	}

	// ȸ���� �Ϸ�� ���ڸ� map�� ����
	for (int i = 0; i < PS; i++) {
		for (int j = 0; j < PS; j++) {
			map[startY + i][startX + j] = tmp[i][j];
		}
	}
}

void meltIce() {
	// ���� ����� �Ǵ� ������ ��ǥ�� ã�´�.
	vector<pair<int, int>> target;
	for (int y = 0; y < mapSize; y++) {
		for (int x = 0; x < mapSize; x++) {

			if (!map[y][x]) continue;

			int ice = 0;
			for (int i = 0; i < 4; i++) {
				int nxtY = y + dy[i];
				int nxtX = x + dx[i];

				if (0 > nxtY || nxtY >= mapSize || 0 > nxtX || nxtX >= mapSize) continue;

				if (map[nxtY][nxtX] <= 0) continue;

				ice++;
			}

			if (ice < 3) target.push_back({ y, x });
		}
	}

	// ������ ���δ�.
	for (int i = 0; i < target.size(); i++) {
		map[target[i].first][target[i].second]--;
	}
}

void getAnswer1() {
	int sum = 0;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			sum += map[i][j];
		}
	}
	answer[0] = sum;
}

void DFS(int y, int x) {
	visit[y][x] = true;
	cnt++;

	for (int i = 0; i < 4; i++) {
		int nxtY = y + dy[i];
		int nxtX = x + dx[i];

		if (0 > nxtY || nxtY >= mapSize || 0 > nxtX || nxtX >= mapSize) continue;
		if (!map[nxtY][nxtX] || visit[nxtY][nxtX]) continue;

		DFS(nxtY, nxtX);
	}
}

void getAnswer2() {
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			if (!map[i][j] || visit[i][j]) continue;

			cnt = 0;
			DFS(i, j);
			
			if (cnt > answer[1]) answer[1] = cnt;
		}
	}
}

void solution() {
	for (int partSize : sq) {
		// ���̾���� �����Ѵ�.
		for (int y = 0; y < mapSize; y += partSize) {
			for (int x = 0; x < mapSize; x += partSize) {
				rotatePartOfMap(y, x, partSize);
			}
		}

		// ������ �ִ� ĭ 3�� �Ǵ� �� �̻�� ���������� ���� ĭ�� ������ ���� 1 �پ���.
		meltIce();
	}

	// �����ִ� ������ ��
	getAnswer1();

	// �����ִ� ���� �� ���� ū ����� �����ϴ� ĭ�� ����
	getAnswer2();
}

int main() {
	getInputValue();

	solution();

	// ��� ���
	for (int ans : answer) {
		cout << ans << endl;
	}
} */