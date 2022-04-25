// �Ｚ ���� : ��� ���б� (����Ž�� + DFS + ���� + ����)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define EMPTY -5

int N, M; // ������ ũ�� N, �Ϲ� ��� ���� �� M(1~M)
int board[50][50]; // ������ ������ ����
bool visit[50][50]; // DFSŽ�� �� ���, �� ��ǥ�� �湮 ���θ� ����
int blockSize; // �� ����� ������
int rainbowBlockNum = 0; // ������ ����� ��
vector<pair<int, int>> rainbowBlock;
map<pair<int, int>, vector<pair<int, int>>> m;
vector<pair<int, int>> group;
vector<vector<int>> possibleBlock;
int answer = 0;
int dy[4] = { 0, 0, 1, -1 };
int dx[4] = { 1, -1, 0, 0 };

bool cmp(vector<int> a, vector<int> b) {
	if (a[0] == b[0]) {
		if (a[1] == b[1]) {
			if (a[2] == b[2]) {
				return a[3] > b[3]; // ���غ���� ���� �������� ��������
			}
			return a[2]> b[2]; // ���غ���� ���� �������� ��������
		}
		return a[1] > b[1]; // ����������� ������ �������� ��������
	}
	return a[0] > b[0]; // ����� ũ�⸦ �������� ��������
}

void getInputValue() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}

void DFS(int y, int x, int color) {
	// �湮�߰ų�, ���� ��ġ���� �ʴµ� ��������ϵ� �ƴ϶��
	if (visit[y][x] ||
		(board[y][x] != color && board[y][x] != 0)) {
		return;
	}

	visit[y][x] = true;

	// ����������̶��
	if (board[y][x] == 0) {
		rainbowBlockNum++;
		rainbowBlock.push_back({ y, x });
	}

	blockSize++;
	group.push_back({ y, x });

	for (int i = 0; i < 4; i++) {
		int nxtY = y + dy[i];
		int nxtX = x + dx[i];

		if (0 > nxtY || nxtY >= N || 0 > nxtX || nxtX >= N) continue;

		DFS(nxtY, nxtX, color);
	}
}

void findBlockGroup() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// ���� �湮���� ���� �Ϲ� ����̶��
			if (!visit[i][j] && 
				(M >= board[i][j] &&
				board[i][j] >= 1)) {
				blockSize = 0;
				rainbowBlockNum = 0;
				rainbowBlock.clear();
				group.clear();
				DFS(i, j, board[i][j]);

				// ������ ��� ��湮 ���
				for (pair<int, int> rb : rainbowBlock) {
					visit[rb.first][rb.second] = false;
				}

				if (group.size() < 2) continue;

				possibleBlock.push_back({
					blockSize, rainbowBlockNum,
					i, j });
				m[{i, j}] = group;
			}
		}
	}
}

void removeBlock() {
	int startY = possibleBlock[0][2];
	int startX = possibleBlock[0][3];

	vector<pair<int, int>> g = m[{startY, startX}];
	for (int i = 0; i < g.size(); i++) {
		board[g[i].first][g[i].second] = EMPTY;
	}

	answer += (g.size() * g.size());
}

void gravityWorks() {
	// ���� ����� ã�´�.
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == -1 || board[i][j] == EMPTY) continue;

			// �ش� ����� ��ĭ�� ���� �� �ִ��� Ȯ���ϰ� ������.
			int curI = i; // ���� ����� ��ġ�� ��
			while (1) {
				if (curI == N) break;

				// ���� ĭ�� ������� �ʴٸ�
				if (board[curI + 1][j] != EMPTY) break;

				// ����� ������.
				int tmp = board[curI + 1][j];
				board[curI + 1][j] = board[curI][j];
				board[curI][j] = tmp;

				curI++;
			}
		}
	}
}

void rotateBoard() {
	int tmp[50][50];
	// ���ڸ� ȸ���� ����.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmp[i][j] = board[j][(N - 1) - i];
		}
	}

	// ȸ���� ���� ������ �����Ѵ�.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = tmp[i][j];
		}
	}
}

void solution() {
	while (1) {
		// ��� �׷��� ��� ã�´�.
		findBlockGroup();

		if (possibleBlock.size() == 0) break;

		// ������ ����� ã�´�.
		sort(possibleBlock.begin(), possibleBlock.end(), cmp);

		// ����� �����ϰ� ������ ȹ���Ѵ�.
		removeBlock();

		// ���ڿ� �߷��� �ۿ��Ѵ�.
		gravityWorks();

		// ���ڰ� �ݽð� �������� 90�� ȸ���Ѵ�.
		rotateBoard();

		// �ٽ� ���ڿ� �߷��� �ۿ��Ѵ�.
		gravityWorks();

		// ���� �÷��̿� �ʿ��� ���� �� �迭 �ʱ�ȭ
		possibleBlock.clear();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visit[i][j] = false;
			}
		}
		m.clear();
	}
}

int main() {
	getInputValue();

	solution();

	cout << answer << endl;
}