// 삼성 기출 : 온풍기 안녕! (구현)
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define RIGHT 0
#define LEFT 1
#define TOP 2
#define BTM 3

int R, C, K, W;
vector<vector<int>> map; // 각 칸의 온도 정보를 저장
bool wallMap[25][25][4]; // 각 칸의 벽 정보를 저장 {RIGHT, LEFT, TOP. BTM}
vector<vector<int>> heater; // 온풍기 정보를 저장 {y, x, h_d}
vector<pair<int, int>> searchPos; // 조사하려고 하는 칸의 정보를 저장 {y, x}
vector<vector<int>> wall; // 벽 정보를 저장 {y, x, t}
int answer = 0; // 답안

// 온풍기에서 나오는 바람의 방향 (4가지) h_dy[h_d]
int h_dy[4] = { 0, 0, -1, 1 };
int h_dx[4] = { 1, -1, 0, 0 };

// 바람이 퍼지는 방향 (3가지) w_dy[h_d][w_d]
int w_dy[4][3] = { {-1, 0, 1}, {1, 0, -1}, {-1, -1, -1}, {1, 1, 1} };
int w_dx[4][3] = { {1, 1, 1}, {-1, -1, -1}, {-1, 0, 1}, {1, 0, -1} };

// 확인해야 하는 벽의 방향 (2가지) chk_d[h_d][w_d][cur/nxt]
int chk_d[4][3][2] = {
	{{TOP, LEFT}, {RIGHT, LEFT}, {BTM, LEFT}},
	{{BTM, RIGHT}, {LEFT, RIGHT}, {TOP, RIGHT}},
	{{LEFT, BTM}, {TOP, BTM}, {RIGHT, BTM}},
	{{RIGHT, TOP}, {BTM, TOP}, {LEFT, TOP}} };

bool checkWall(int y, int x, int nxtY, int nxtX, int h_d, int w_d) {
	int cur_d = chk_d[h_d][w_d][0];
	int nxt_d = chk_d[h_d][w_d][1];

	if (wallMap[y][x][cur_d] || wallMap[nxtY][nxtX][nxt_d]) return false;
	else return true;
}

void spreadWind(int y, int x, int h_d) {
	vector<vector<bool>> visit(R, vector<bool>(C, false));
	
	int startY = y + h_dy[h_d];
	int startX = x + h_dx[h_d];
	if (0 > startY || startY >= R || 0 > startX || startX >= C) return;

	queue<vector<int>> q; // {y, x, tem}
	visit[startY][startX] = true;
	map[startY][startX] += 5;
	q.push({ startY, startX, 5 });
	while (!q.empty()) {
		int y = q.front()[0];
		int x = q.front()[1];
		int tem = q.front()[2];
		q.pop();

		if (tem == 1) continue;

		for (int w_d = 0; w_d < 3; w_d++) {
			int nxtY = y + w_dy[h_d][w_d];
			int nxtX = x + w_dx[h_d][w_d];

			// 격자 밖의 영역이라면
			if (0 > nxtY || nxtY >= R || 0 > nxtX || nxtX >= C) continue;
			
			// 이미 온도가 더해진 영역이라면
			if (visit[nxtY][nxtX]) continue;

			// 바람이 벽에 의해 막힌다면
			if (!checkWall(y, x, nxtY, nxtX, h_d, w_d)) continue;

			visit[nxtY][nxtX] = true;
			map[nxtY][nxtX] += (tem - 1);
			q.push({ nxtY, nxtX, tem - 1 });
		}
	}
}

void heaterWork() {
	for (int i = 0; i < heater.size(); i++) {
		int y = heater[i][0];
		int x = heater[i][1];
		int h_d = heater[i][2];

		spreadWind(y, x, h_d);
	}
}

void settingWall() {
	for (int i = 0; i < W; i++) {
		int y = wall[i][0];
		int x = wall[i][1];
		int t = wall[i][2];

		if (t == 0) {
			wallMap[y][x][TOP] = 1;
			if (y - 1 >= 0) wallMap[y - 1][x][BTM] = 1;
		}
		else { // t == 1
			wallMap[y][x][RIGHT] = 1;
			if (x + 1 < C) wallMap[y][x + 1][LEFT] = 1;
		}
	}
}

void controlTemperature() {
	vector<vector<int>> newMap = map;

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			
			for (int d = 0; d < 4; d++) { // h_dy, h_dx 인접한칸 탐색에서 재사용
				int nxtY = y + h_dy[d];
				int nxtX = x + h_dx[d];

				// 격자 밖 영역이라면
				if (0 > nxtY || nxtY >= R || 0 > nxtX || nxtX >= C) continue;

				// 인접한 두 칸 사이에 벽이 있다면
				if (wallMap[y][x][d]) continue;

				// 온도를 조절한다.
				newMap[y][x] += ((map[nxtY][nxtX] - map[y][x]) / 4);
			}
		}
	}

	// map에 복사한다.
	map = newMap;
}

void printMap() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void decreaseTemperature() {
	for (int x = 0; x < C - 1; x++) if(map[0][x]) map[0][x]--;
	for (int y = 0; y < R - 1; y++) if (map[y][C - 1]) map[y][C - 1]--;
	for (int x = C - 1; x >= 1; x--) if (map[R - 1][x]) map[R - 1][x]--;
	for (int y = R - 1; y >= 1; y--) if(map[y][0]) map[y][0]--;
}

bool isItEnd() {
	for (pair<int, int> s : searchPos) {
		if (map[s.first][s.second] < K) return false;
	}

	return true;
}

void solution() {
	settingWall();

	int chocolte = 0;
	while (chocolte <= 100) {
		// 1. 집에 있는 모든 온풍기에 바람이 나온다.
		heaterWork();

		// 2. 온도가 조정된다.
		controlTemperature();

		// 3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소한다.
		decreaseTemperature();

		// 4. 초콜릿을 하나 먹는다.
		chocolte++;

		// 5. 조사하는 모든 칸의 온도가 K 이상이 되는지 검사한다.
		if (isItEnd()) break;
	}
	answer = chocolte;
}

int main() {
	cin >> R >> C >> K;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int input;
			cin >> input;

			if (1 <= input && input <= 4) { // 온풍기 정보를 받는다.
				heater.push_back({ i, j, input - 1 });
			}
			else if (input == 5) { // 조사하려고 하는 칸의 정보를 받는다.
				searchPos.push_back({ i, j });
			}
		}
	}
	cin >> W;
	for (int i = 0; i < W; i++) {
		int y, x, t;
		cin >> y >> x >> t;
		wall.push_back({ y - 1, x - 1, t });
	}
	map.resize(R, vector<int>(C, 0));

	solution();

	cout << answer << endl;
}