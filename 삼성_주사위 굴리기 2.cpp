// �Ｚ ���� : �ֻ��� ������ 2 (���� + DFS)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M; // ������ ���� ���� N, ���� ���� M
int map[20][20]; // ���� ������ ����
int K; // �ֻ����� �̵� Ƚ��
int answer = 0; // ���
vector<int> dice(6); // �ֻ����� ���� ������ ���� {��, ��, ��, ��, ��, ��}
int dir = 0; // �ֻ����� �̵� ������ ���� (0 : ��, 1 : ��, 2 : ��, 3 : ��)
int score;
bool visit[20][20];

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

void getInputValue() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

// �ֻ����� ������ �޼���
void rollDice() {
	vector<int> tmp;
	// {��, ��, ��, ��, ��, ��}
	if (dir == 0) { // ��
		tmp = { dice[3], dice[1], dice[0], dice[5], dice[4], dice[2] };
	}
	else if (dir == 1) { // ��
		tmp = { dice[1], dice[5], dice[2], dice[3], dice[0], dice[4] };
	}
	else if (dir == 2) { // ��
		tmp = { dice[2], dice[1], dice[5], dice[0], dice[4], dice[3] };
	}
	else { // ��
		tmp = { dice[4], dice[0], dice[2], dice[3], dice[5], dice[1] };
	}

	dice = tmp;
}

void DFS(int y, int x, int num) {
	if (visit[y][x] || map[y][x] != num) return;

	visit[y][x] = true;
	score += num;

	for (int i = 0; i < 4; i++) {
		int nxtY = y + dy[i];
		int nxtX = x + dx[i];

		if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= M) continue;

		DFS(nxtY, nxtX, num);
	}
}

void getScore(int startY, int startX, int num) {
	score = 0;
	DFS(startY, startX, num);
	answer += score;

	// visit �迭 �ʱ�ȭ
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visit[i][j] = false;
		}
	}
}

void setDir(int y, int x, int num) {
	if (dice[5] > map[y][x]) { // �ð�������� 90�� ȸ��
		dir = (++dir) % 4;
	}
	else if(dice[5] < map[y][x]) { // �ݽð�������� 90�� ȸ��
		dir = (dir += 3) % 4;
	}
}

void solution() {
	// �ֻ��� ���� �ʱ� ����
	int y = 0;
	int x = 0;
	dice = { 1, 2, 3, 4, 5, 6 };

	while (K--) {
		// �ֻ����� ��ġ�� ���� ��ǥ
		y += dy[dir];
		x += dx[dir];

		// �̵� ���⿡ ĭ�� ���ٸ�
		if (0 > y || y >= N || 0 > x || x >= M) {
			dir = (dir += 2) % 4; // �̵� ������ �ݴ�� �Ѵ�.
			y += (dy[dir] * 2); // �̵� ��� + �ݴ� �������� �� ĭ
			x += (dx[dir] * 2); 
		}

		rollDice(); // �� ĭ ��������.
		
		getScore(y, x, map[y][x]); // ������ ȹ���Ѵ�.

		setDir(y, x, map[y][x]); // ���� ���� ���� ����
	}
}

int main() {
	getInputValue();

	solution();

	cout << answer << endl;
}