// �Ｚ ���� : ������ ���� ���̾ (���� + map)
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int N; // ������ ũ��
int M; // ���̾�� ����
int K; // ��� Ƚ��
// ���̾�� ���� ������ ����
// {y, x} = {{m1, s1, d1}, {m2, s2, d2}, ... }
vector<vector<int>> board[50][50];
map<pair<int, int>, int> chk;

// ��, ���, ��, �Ͽ�, ��, ����, ��, ����
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int answer = 0;

void getInputValue() {
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int y, x, m, s, d; // m : ����, s : �ӵ�, d : ����
		cin >> y >> x >> m >> s >> d;
		board[y - 1][x - 1].push_back({ m, s, d });
		chk[{y - 1, x - 1}]++;
	}
}

void getAnswer() {
	for (auto spot : chk) {
		int y = spot.first.first;
		int x = spot.first.second;

		for (int i = 0; i < board[y][x].size(); i++) {
			answer += board[y][x][i][0];
		}
	}
}

void solution() {
	while (K--) {
		vector<vector<int>> tmp_board[50][50];
		map<pair<int, int>, int> tmp_chk;

		// 1. ��� ���̾�� �̵��Ѵ�.
		for (auto spot : chk) {
			int y = spot.first.first;
			int x = spot.first.second;

			for (int i = 0; i < board[y][x].size(); i++) {
				int m = board[y][x][i][0];
				int s = board[y][x][i][1];
				int d = board[y][x][i][2];

				int nxtY = y + (dy[d] * (s % N));
				int nxtX = x + (dx[d] * (s % N));

				if (nxtY < 0) nxtY += N;
				else if (nxtY >= N) nxtY -= N;
				if (nxtX < 0) nxtX += N;
				else if (nxtX >= N) nxtX -= N;

				tmp_board[nxtY][nxtX].push_back({ m, s, d });
				tmp_chk[{nxtY, nxtX}]++;
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				board[i][j].clear();
			}
		}
		chk.clear();

		// 2. �̵��� ��� ���� ��, 2�� �̻��� ���̾�� �ִ� ĭ ó��
		for (auto spot : tmp_chk) {
			int y = spot.first.first;
			int x = spot.first.second;
			chk[{y, x}]++;

			if (tmp_board[y][x].size() == 1) {
				board[y][x].push_back({
					tmp_board[y][x][0][0],
					tmp_board[y][x][0][1],
					tmp_board[y][x][0][2] });
				continue;
			}

			int nxtM = 0;
			int nxtS = 0;
			vector<int> nxtD;
			int cnt1 = 0, cnt2 = 0;
			for (int i = 0; i < tmp_board[y][x].size(); i++) {
				nxtM += tmp_board[y][x][i][0];
				nxtS += tmp_board[y][x][i][1];

				if (tmp_board[y][x][i][2] % 2 == 0) cnt1++;
				else cnt2++;
			}

			nxtM /= 5;
			nxtS /= tmp_board[y][x].size();
			if (cnt1 == tmp_board[y][x].size() ||
				cnt2 == tmp_board[y][x].size()) {
				nxtD = { 0, 2, 4, 6 };
			}
			else {
				nxtD = { 1, 3, 5, 7 };
			}

			if (nxtM == 0) continue; // ������ 0�� ���̾�� �Ҹ�Ǿ� ��������.

			for (int i = 0; i < 4; i++) {
				board[y][x].push_back({ nxtM, nxtS, nxtD[i] });
			}
		}
	}

	getAnswer();
}

int main() {
	getInputValue();

	solution();

	cout << answer << endl;
}