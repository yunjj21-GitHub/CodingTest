// �Ｚ ���� : ������ ���� ��ٶ�� (���� + deque)
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

int N, M; // ������ ũ�� N, ���� �̵� Ƚ�� M;
int map[50][50]; // ���� ������ ��� �迭
deque<pair<int, int>> cmd; // ������ �̵� ������ ����

// ��, �밢������, ��, �밢�����, ��, �밢���Ͽ�, ��, �밢������
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };

bool removed[50][50]; // ������ ����� ��ǥ�� ���
int answer = 0; // ���

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
	// ������ �ʱ� ��ġ ����
	deque<pair<int, int>> cloud = { 
		{N - 2, 0}, {N - 2, 1}, {N - 1, 0}, {N - 1, 1} 
	};

	while (!cmd.empty()) {
		// 1. ��� ������ dir �������� sĭ �̵��Ѵ�.
		int dir = cmd.front().first - 1;
		int s = cmd.front().second % N;
		cmd.pop_front();

		for (int i = 0; i < cloud.size(); i++) {
			cloud[i].first += (dy[dir] * s);
			cloud[i].second += (dx[dir] * s);

			// ������ ��� ������ ó��
			if (cloud[i].first < 0) cloud[i].first += N;
			else if (cloud[i].first >= N) cloud[i].first -= N;

			if (cloud[i].second < 0) cloud[i].second += N;
			else if (cloud[i].second >= N) cloud[i].second -= N;
		}

		// 2. �� �������� �� ���� ������ �ִ� ĭ�� �ٱ��Ͽ� ����� ���� ���� 1 �����Ѵ�.
		for (int i = 0; i < cloud.size(); i++) {
			map[cloud[i].first][cloud[i].second]++;
			// 3. ������ ��� �������.
			removed[cloud[i].first][cloud[i].second] = true; // ������ ����� ��ǥ ���
		}

		// 4. 2���� ���� ������ ĭ�� ��������� ������ �����Ѵ�.
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

		// 5. �ٱ��Ͽ� ����� ���� ���� 2 �̻��� ��� ĭ�� ������ �����, ���� ���� 2 �پ���.
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] >= 2 && !removed[i][j]) {
					map[i][j] -= 2;
					cloud.push_back({ i, j });
				}
			}
		}

		// 3�� ���� ������� visit �迭 �ʱ�ȭ
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
	getInputValue(); // �Է°��� �޾ƿ�

	solution();

	getAnswer();

	cout << answer << endl;
}