// �Ｚ ���� : ��Ʈ�ι̳� (����Ž�� + DFS)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M; // ������ ���� ũ�� N, ���� ũ�� M
vector<vector<int>> map; // ���̿� ���� ������ ����
int answer = -1; // ���

int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };
vector<vector<int>> visit; // DFS�� �湮���� üũ

void getInputValue() {
	cin >> N >> M;
	map.resize(N, vector<int>(M)); // ������ ������ ����
	visit.resize(N, vector<int>(M)); // �湮���� üũ �迭 ������ ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void DFS(int y, int x, int depth, int sum) {
	if (visit[y][x]) return; // ���� �湮���� ��ǥ���

	visit[y][x] = true; // �湮ó��
	sum += map[y][x];

	if (++depth == 4) { // ��Ʈ�ι̳� ����� ����� ���ٸ�
		if (sum > answer) answer = sum; // ��� ����
		
		visit[y][x] = false;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nxtY = y + dy[i];
		int nxtX = x + dx[i];

		if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= M) continue;

		DFS(nxtY, nxtX, depth, sum);
	}

	visit[y][x] = false;
}

void checkT(int y, int x) {
	if (y + 1 < N && x + 2 < M) { // �� ��� Ȯ��
		int sum = map[y][x] + map[y][x + 1] + map[y + 1][x + 1] + map[y][x + 2];
		answer = sum > answer ? sum : answer;
	}

	if (y - 1 >= 0 && y + 1 < N && x + 1 < M) { // �� ��� Ȯ��
		int sum = map[y][x] + map[y - 1][x + 1] + map[y][x + 1] + map[y + 1][x + 1];
		answer = sum > answer ? sum : answer;
	}

	if (y + 1 < N && x - 1 >= 0 && x + 1 < M) { // �� ��� Ȯ��
		int sum = map[y][x] + map[y + 1][x - 1] + map[y + 1][x] + map[y + 1][x + 1];
		answer = sum > answer ? sum : answer;
	}

	if (y + 2 < N && x + 1 < M) { // �� ��� Ȯ��
		int sum = map[y][x] + map[y + 1][x] + map[y + 2][x] + map[y + 1][x + 1];
		answer = sum > answer ? sum : answer;
	}
	return;
}

void solution() {
	// ��� ��ǥ�� �������� Ž�� (����Ž��)
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			DFS(y, x, 0, 0); // ��Ʈ�ι̳� 4�� Ȯ�� (��Ī, ȸ�� ����)
			checkT(y, x); // ��Ʈ�ι̳� 1�� Ȯ�� (��Ī, ȸ�� ����, (��, ��, ��, ��))
		}
	}
}

int main() {
	getInputValue(); // �Է°��� �޾ƿ�

	solution();
	
	cout << answer << '\n';
}