// ���� 16234 : �α� �̵� (BFS)
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

int N; // ���� ũ��
int L, R; // ������ �̷�� �ִ� �α� ���� �ּ�, �ִ�
int map[50][50]; // �α� ������ ����
bool finish[50][50] = {0}; // ���ձ� Ž���� ���� ���� ����
// ���ձ� Ž�� ��θ� ����
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };
int answer = 0; // �α��̵��� �ҿ�Ǵ� ��

bool flag = 0;

void solution();
void exploreIfAllyCanBeCreated(int y, int x);

int main(){
	// �Է°��� �޾ƿ�
	cin >> N;
	cin >> L >> R;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}

	solution();

	// ��� ���
	cout << answer << endl;
}

void solution() {
	while (1) {
		// ���ձ� Ž���� �Ϸ���� ���� ���� ������� ���ձ� Ž��
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (!finish[y][x]) exploreIfAllyCanBeCreated(y, x);
			}
		}

		// ��� ���� �������� ������ �Ͼ�� �ʾҴٸ� �α��̵� ����
		if (!flag) break;

		// ���� Ž���� ���� ���� �ʱ�ȭ
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				finish[i][j] = 0;
			}
		}
		flag = 0;

		// �ҿ�Ǵ� �� ����
		answer++;
	}
}

void exploreIfAllyCanBeCreated(int y, int x) {
	vector<pair<int, int>> ally; // Ž������ ����� ������ ���� ������ ����
	ally.push_back({ y, x });
	int tot = map[y][x]; // ���տ� ���� ������� �� �α���

	// ���ձ� Ž�� (BFS)
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
			finish[nxtY][nxtX] = 1; // Ž�� �Ϸ� ó��
		}
	}

	// ������ �߻��ߴ��� Ȯ��
	if (ally.size() > 1) flag = 1;

	// �α� �̵�
	for (auto country : ally) {
		map[country.first][country.second] = tot / ally.size();
	}
}