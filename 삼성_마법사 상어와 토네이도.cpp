// �Ｚ ���� : ������ ���� ����̵� (����)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N; // ������ ũ��
vector<vector<int>> map; // �� ĭ�� ���� ���� ����
// ����̵��� ������ ���� (��, ��, ��, ��)
int t_dy[4] = { 0, 1, 0, -1 };
int t_dx[4] = { -1, 0, 1, 0 };
// ���� ������ ���� (��, ��, ��, ��)
int s_dy[4][10] = {
	{ -1, -1, -1, -2, 1, 1, 1, 2, 0, 0},
	{-1, 0, 1, 0, -1, 0, 1, 0, 2, 1},
	{1, 1, 1, 2, -1, -1, -1, -2, 0, 0},
	{1, 0, -1, 0, 1, 0, -1, 0, -2, -1}
};
int s_dx[4][10] = {
	{1, 0, -1, 0, 1, 0, -1, 0, -2, -1},
	{-1, -1, -1, -2, 1, 1, 1, 2, 0, 0},
	{-1, 0, 1, 0, -1, 0, 1, 0, 2, 1},
	{1, 1, 1, 2, -1, -1, -1, -2, 0, 0}
};
vector<int> s_md = { 1, 7, 10, 2, 1, 7, 10, 2, 5}; // ������ 9

int answer = 0; // ���� ������ ���� �� (���)

void getInputValue() {
	cin >> N;
	map.resize(N, vector<int>(N));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

bool isItRightRange(int y, int x) {
	if (y >= 0 && y < N && x >= 0 && x < N) return true;
	else return false;
}

void solution() {
	// ����̵��� �ʱ���ġ ���� (map�� �ε��� : 0~N-1)
	int y = N / 2;
	int x = N / 2;
	int dir = 0; // ����̵��� ���� ���� (0~3)
	int len = 1; // ����̵��� ���� ����

	while (isItRightRange(y, x)) {
		// ����̵��� ������
		for (int i = 0; i < len; i++) {
			y += t_dy[dir];
			x += t_dx[dir];

			if (!isItRightRange(y, x)) break;

			// ���� ������
			if (!map[y][x]) continue; // �ش� ��ǥ�� �𷡰� ���ٸ�

			int totDis = 0;
			for (int j = 0; j < 10; j++) {
				int nxtY = y + s_dy[dir][j];
				int nxtX = x + s_dx[dir][j];

				int dis;
				if (j != 9) {
					dis = (map[y][x] * s_md[j]) / 100;
					totDis += dis;
				}
				else { // j == 9
					dis = map[y][x] - totDis;
				}

				if (!isItRightRange(nxtY, nxtX)) {
					answer += dis;
				}
				else { // ������ ����� �ʾҴٸ�
					map[nxtY][nxtX] += dis;
				}
			}
		}

		// ������� ����
		dir = (++dir) % 4;
		if (dir % 2 == 0) len++; // 0 �Ǵ� 2 �����϶�, �������� ����
	}
}

int main() {
	getInputValue();

	solution();

	cout << answer << endl;
}