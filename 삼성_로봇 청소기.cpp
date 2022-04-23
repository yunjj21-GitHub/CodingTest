// �Ｚ ���� : �κ� û�ұ�
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
int map[50][50];
bool finish[50][50]; // û�Ұ� �Ϸ�Ǿ����� ����
int robotY, robotX, dir;

// ���ʷ� ��, ��, ��, ������ �������� ����
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int answer = 0;

// �Է°��� �޾ƿ�
void getInputValue() {
	cin >> N >> M;
	cin >> robotY >> robotX >> dir;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void solution() {
	while (1) {
		// 1. ������ǥ û��
		int flag = true;

		if (!finish[robotY][robotX]) {
			finish[robotY][robotX] = true;
			answer++;
		}

		// 2-a. ��������� �ٷ� ���� ��ǥ Ȯ��
		for (int i = 0; i < 4; i++) {
			if (dir > 0) dir--;
			else dir = 3;
			int nxtY = robotY + dy[dir];
			int nxtX = robotX + dx[dir];

			// û�ҵ��� ���� �� �����̶��
			if (!finish[nxtY][nxtX] && !map[nxtY][nxtX]) {
				// ��ĭ ����
				robotY = nxtY;
				robotX = nxtX;
				
				flag = false; // 1������ ���ư� ������ ǥ��
				break;
			}
		}

		if (flag) { // 2-b. �������� Ȯ��
			// ��������� �ٷ� ���� ��ǥ
			int backY, backX;
			if (dir <= 1) {
				backY = robotY + dy[dir + 2];
				backX = robotX + dx[dir + 2];
			}
			else {
				backY = robotY + dy[dir - 2];
				backX = robotX + dx[dir - 2];
			}

			// ��������� �ٷ� ���� ��ǥ�� ���̶�� �۵��� �����.
			if (map[backY][backX] == 1) break;
			else { // ��������� �ٷ� ���� ��ǥ�� ���� �ƴ϶�� ��ĭ �����Ѵ�.
				robotY = backY;
				robotX = backX;
			}
		}
	}
}

int main() {
	// �Է°��� �޾ƿ�
	getInputValue();

	solution();

	cout << answer << endl;
}