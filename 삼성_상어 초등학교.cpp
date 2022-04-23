// �Ｚ ���� : ��� �ʵ��б� (���� + ����)
#include <iostream>
#include <vector>
#include <string>

#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

int N;
queue<vector<int>> q; // �л� ������ ���
unordered_map<int, vector<int>> um; // �л� �������� ���� �� ���
vector<vector<int>> finish; // ��ġ�� �Ϸ�� ���� ���� ����
int answer = 0; // ���

// �����¿츦 ����
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

vector<vector<int>> result;

bool cmp(vector<int> a, vector<int> b) {
	if (a[0] == b[0]) {
		if (a[1] == b[1]) {
			if (a[2] == b[2]) {
				return a[3] < b[3];
			}
			return a[2] < b[2];
		}
		return a[1] > b[1];
	}
	return a[0] > b[0];
}

void getInputValue() {
	cin >> N;
	for (int i = 0; i < N * N; i++) {
		int student, f1, f2, f3, f4;
		cin >> student >> f1 >> f2 >> f3 >> f4;

		q.push({ student, f1, f2, f3, f4 });
		um[student] = { f1, f2, f3, f4 };
	}

	finish.resize(N, vector<int>(N));
}

void checkConditions(int f1, int f2, int f3, int f4) {
	result.clear();
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {

			// �̹� ���� ���� �ڸ����
			if (finish[y][x] != 0) continue;

			int con1 = 0, con2 = 0;

			for (int i = 0; i < 4; i++) {
				int nxtY = y + dy[i];
				int nxtX = x + dx[i];

				// ���� ���� �����̶��
				if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= N) continue;

				// ����1 Ȯ��, ������ ���� ģ���� �ɾҴٸ�
				int adj = finish[nxtY][nxtX];
				if (adj == f1 || adj == f2 ||
					adj == f3 || adj == f4) {
					con1++;
				}

				// ����2 Ȯ��, ������ ���� �� ĭ�̶��
				if (adj == 0) con2++;
			}

			result.push_back({ con1, con2, y, x });
		}
	}
}

void arrangeSeat(int student) {
	sort(result.begin(), result.end(), cmp);

	int bestY = result[0][2];
	int bestX = result[0][3];

	finish[bestY][bestX] = student;
}

void calculatSatisfaction() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int student = finish[y][x];

			vector<int> f_list = um[student];
			int f1 = f_list[0];
			int f2 = f_list[1];
			int f3 = f_list[2];
			int f4 = f_list[3];

			int cnt = 0;
			for (int i = 0; i < 4; i++) {
				int nxtY = y + dy[i];
				int nxtX = x + dx[i];

				// ���� ���� �����̶��
				if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= N) continue;

				int adj = finish[nxtY][nxtX];
				if (adj == f1 || adj == f2 ||
					adj == f3 || adj == f4) {
					cnt++;
				}
			}

			if (cnt == 1) answer += 1;
			else if (cnt == 2) answer += 10;
			else if (cnt == 3) answer += 100;
			else if (cnt == 4) answer += 1000;
		}
	}
}

void solution() {
	while (!q.empty()) {
		int student = q.front()[0];
		int f1 = q.front()[1];
		int f2 = q.front()[2];
		int f3 = q.front()[3];
		int f4 = q.front()[4];
		q.pop();

		// �л��� ���� ���� ��� �ڸ��� �������� ���� �˻�
		checkConditions(f1, f2, f3, f4);

		// �л��� �ڸ��� ���Ѵ�.
		arrangeSeat(student);
	}

	// ��� �л��� �������� ���Ѵ�.
	calculatSatisfaction();
}

int main() {
	// �Է°��� �޾ƿ�
	getInputValue();

	solution();

	cout << answer << endl;
}