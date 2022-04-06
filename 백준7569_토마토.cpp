// ���� 7569 : �丶�� (BFS + 3���� ���)
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// ������ ���� ĭ�� �� M, ���� ĭ�� �� N, �׾ƿø� ������ �� H
int M, N, H;

// ������ Ž�� ���
int dz[6] = { 1, -1, 0, 0, 0, 0 };
int dy[6] = { 0, 0, 0, 0, 1, -1 };
int dx[6] = { 0, 0, 1, -1, 0, 0 };

// BFS Ž�� �� ���
queue<vector<int>> q; // {h, y, x, day}

int main() {
	// �Է°��� �޾ƿ� (�ʱ�ȭ)
	cin >> M >> N >> H;
	// ������ �� ĭ�� ���� ������ ����
	vector<vector<vector<int>>> box(H, vector<vector<int>>(N, vector<int>(M)));
	for (int z = 0; z < H; z++) { // �׾ƿø� ���� �� ��ŭ
		for (int y = 0; y < N; y++) { // ������ ���� ���� ��ŭ
			for (int x = 0; x < M; x++) { // ������ ���� ���� ��ŭ
				cin >> box[z][y][x];
				if (box[z][y][x] == 1) q.push({ z, y, x, 0});
			}
		}
	}

	// BFS Ž��
	int result = 0;
	while (!q.empty()) {
		int z = q.front()[0];
		int y = q.front()[1];
		int x = q.front()[2];
		int day = q.front()[3];
		q.pop();

		if (day > result) result = day;

		for (int i = 0; i < 6; i++) {
			int nxtZ = z + dz[i];
			int nxtY = y + dy[i];
			int nxtX = x + dx[i];

			// Ž�� ������ ������ �ƴ϶��
			if (nxtZ < 0 || nxtZ >= H ||
				nxtY < 0 || nxtY >= N ||
				nxtX < 0 || nxtX >= M) continue;
			
			// ������ �丶�䰡 �ƴ϶��
			if (box[nxtZ][nxtY][nxtX] != 0) continue;

			q.push({ nxtZ, nxtY, nxtX, day + 1 });
			box[nxtZ][nxtY][nxtX] = 1; // ���� �丶��� ó��
		}
	}

	// ���� ���� �丶�䰡 �ִ��� Ȯ��
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int z = 0; z < M; z++) {
				if (box[i][j][z] == 0) result = -1;
			}
		}
	}

	// ��� ���
	cout << result << endl;
}