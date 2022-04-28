// 삼성 기출 : 마법사 상어와 기출 (구현 + 완전탐색)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int M, S; // 초기 물고기의 수 M, 상어의 연습 횟수 S
int sY, sX; // 상어의 위치 정보를 저장
vector<int> f_map[4][4];
vector<int> c_map[4][4];
int sm_map[4][4];
// 상어의 움직임 정의 (상좌하우)
int s_dy[4] = { -1, 0, 1, 0 };
int s_dx[4] = { 0, -1, 0, 1 };
// 물고기의 움직임 정의 (반시계 방향)
int f_dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int f_dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int t = 1; // 현재 몇 번째 연습중인지 저장
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

					// 격자 밖 영역이라면
					if (0 > nxtY || nxtY >= 4 || 0 > nxtX || nxtX >= 4) continue;

					// 상어가 있거나 물고기 냄새가 남아 있는 자리라면
					if (nxtY == sY && nxtX == sX) continue;

					// 물고기 냄새가 남아있다면
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
		// 1. 물고기를 복제한다.
		copyFishStart();

		// 2. 모든 물고기가 한칸 이동한다.
		moveFish();

		// 3. 상어가 연속해서 3칸 이동한다.
		maxFish = -1;
		vector<int> tmp;
		searchBestMove(tmp);
		moveShark();

		// 5. 물고기 복제가 완료된다.
		copyFishFinish();
	}

	getAnswer();
}

int main() {
	getInputValue(); // 입력값을 받아옴

	solution();

	cout << answer << endl;
}