// �Ｚ ���� : ������ ���� ���� (���� + ����Ž��)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int M, S; // �ʱ� ������� �� M, ����� ���� Ƚ�� S
int sY, sX; // ����� ��ġ ������ ����
vector<int> f_map[4][4];
vector<int> c_map[4][4];
int sm_map[4][4];
// ����� ������ ���� (�����Ͽ�)
int s_dy[4] = { -1, 0, 1, 0 };
int s_dx[4] = { 0, -1, 0, 1 };
// ������� ������ ���� (�ݽð� ����)
int f_dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int f_dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int t = 1; // ���� �� ��° ���������� ����
int maxFish; 
vector<int> bestRoute;
int answer = 0;

void getInputValue() {
	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		int y, x, d;
		cin >> y >> x >> d;
		f_map[y - 1][x - 1].push_back(d - 1);
	}
	cin >> sY >> sX;
	sY--;
	sX--;
}

void copyFishStart() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c_map[i][j] = f_map[i][j];
		}
	}
}

void moveFish() {
	vector<int> tmp_map[4][4];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < f_map[i][j].size(); k++) {
				int y = i;
				int x = j;
				int d = f_map[i][j][k];

				int z;
				for (z = 0; z < 8; z++) {
					int nxtD = (d + 8 - z) % 8;
					int nxtY = y + f_dy[nxtD];
					int nxtX = x + f_dx[nxtD];

					// ���� �� �����̶��
					if (0 > nxtY || nxtY >= 4 || 0 > nxtX || nxtX >= 4) continue;

					// �� �ְų� ����� ������ ���� �ִ� �ڸ����
					if (nxtY == sY && nxtX == sX) continue;

					// ����� ������ �����ִٸ�
					if (sm_map[nxtY][nxtX] != 0 && t - sm_map[nxtY][nxtX] <= 2) continue;

					tmp_map[nxtY][nxtX].push_back(nxtD);
					break;
				}

				if (z == 8) tmp_map[y][x].push_back(d);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			f_map[i][j] = tmp_map[i][j];
		}
	}
}

int sharkSimulation(vector<int> route) {
	bool visit[4][4] = { false, };

	int fishNum = 0;
	int y = sY;
	int x = sX;
	for (int d : route) {
		y += s_dy[d];
		x += s_dx[d];

		if (0 > y || y >= 4 || 0 > x || x >= 4) return -1;

		if (!visit[y][x]) {
			visit[y][x] = true;
			fishNum += f_map[y][x].size();
		}
	}

	return fishNum;
}

void searchBestMove(vector<int> route) {
	if (route.size() == 3) {
		int fishNum = sharkSimulation(route);

		if (fishNum > maxFish) {
			maxFish = fishNum;
			bestRoute = route;
		}
		
		return;
	}

	for (int i = 0; i < 4; i++) {
		route.push_back(i);
		searchBestMove(route);
		route.pop_back();
	}
}

void moveShark() {
	for (int d : bestRoute) {
		sY += s_dy[d];
		sX += s_dx[d];

		if (f_map[sY][sX].size()) {
			f_map[sY][sX].clear();
			sm_map[sY][sX] = t;
		}
	}
}

void copyFishFinish() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < c_map[i][j].size(); k++) {
				f_map[i][j].push_back(c_map[i][j][k]);
			}
		}
	}
}

void getAnswer() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer += f_map[i][j].size();
		}
	}
}

void solution() {
	for (t; t <= S; t++) {
		// 1. ����⸦ �����Ѵ�.
		copyFishStart();

		// 2. ��� ����Ⱑ ��ĭ �̵��Ѵ�.
		moveFish();

		// 3. �� �����ؼ� 3ĭ �̵��Ѵ�.
		maxFish = -1;
		vector<int> tmp;
		searchBestMove(tmp);
		moveShark();

		// 5. ����� ������ �Ϸ�ȴ�.
		copyFishFinish();
	}

	getAnswer();
}

int main() {
	getInputValue(); // �Է°��� �޾ƿ�

	solution();

	cout << answer << endl;
}