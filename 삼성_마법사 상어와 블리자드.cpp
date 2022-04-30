// 삼성 기출 : 마법사 상어와 블리자드 (구현)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> map;
vector<pair<int, int>> orderOfMAp; // map의 탐색 순서를 저장 {y, x}
// map의 탐색 방향을 저장 (좌하우상)
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { -1, 0, 1, 0 };
vector<pair<int, int>> magic;
// 마법의 진행 방향을 저장 (상하좌우)
int m_dy[4] = { -1, 1, 0, 0 };
int m_dx[4] = { 0, 0, -1, 1 };

int explodeNum[3]; // 폭발한 구슬의 개수
int answer = 0;

void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool isItRightRange(int y, int x) {
	if (y >= 0 && y < N && x >= 0 && x < N) return true;
	else return false;
}

void settingOrderOfMap() {
	int y = N / 2;
	int x = N / 2;
	int d = 0;
	int len = 1;
	while (isItRightRange(y, x)) {
		for (int i = 0; i < len; i++) {
			y += dy[d];
			x += dx[d];

			// map 밖의 영역이라면
			if (!isItRightRange(y, x)) continue;

			orderOfMAp.push_back({ y, x });
		}

		d = (++d) % 4;
		if (d % 2 == 0) len++;
	}
}

void moveMarble() {
	vector<vector<int>> newMap(N, vector<int>(N, 0));

	int newSpot = 0;
	for (pair<int, int> yx : orderOfMAp) {
		// 구슬이 없는 좌표라면
		if (!map[yx.first][yx.second]) continue;

		pair<int, int> newYX = { orderOfMAp[newSpot].first, orderOfMAp[newSpot].second };
		newMap[newYX.first][newYX.second] = map[yx.first][yx.second];
		newSpot++;
	}

	map = newMap;
}

void destoryMarble(int t) {
	int y = N / 2;
	int x = N / 2;
	int d = magic[t].first;
	int s = magic[t].second;

	for (int i = 0; i < s; i++) {
		y += m_dy[d];
		x += m_dx[d];

		if (!isItRightRange(y, x)) continue;

		map[y][x] = 0;
	}

	// 모든 구슬이 앞으로 당겨진다.
	moveMarble();
}

void marbleExplode() {
	bool flag = true;

	while (flag) {
		flag = false;

		int preMarble = 0;
		vector<pair<int, int>> marbles;

		for (pair<int, int> yx : orderOfMAp) {

			if (preMarble != map[yx.first][yx.second]) {

				if (marbles.size() >= 4) {
					flag = true;
					for (pair<int, int> m : marbles) {
						map[m.first][m.second] = 0;
					}
					explodeNum[preMarble - 1] += marbles.size();
				}
				preMarble = map[yx.first][yx.second];
				marbles.clear();
			}
			marbles.push_back({ yx.first, yx.second });
		}

		// 모든 구슬이 앞으로 당겨진다.
		moveMarble();
	}
}

void marbleChange() {
	pair<int, int> group = { 0, map[N/2][N/2 - 1]}; // {size, num}
	vector<int> result;

	for (pair<int, int> yx : orderOfMAp) {
		if (group.second != map[yx.first][yx.second]) {
			result.push_back(group.first);
			result.push_back(group.second);

			group.first = 0;
			group.second = map[yx.first][yx.second];
		}

		group.first++;
	}

	int resIdx = 0;
	for (pair<int, int> yx : orderOfMAp) {
		if (resIdx == result.size()) break;

		map[yx.first][yx.second] = result[resIdx++];
	}
}

void getAnswer() {
	answer = 
		explodeNum[0] * 1 +
		explodeNum[1] * 2 +
		explodeNum[2] * 3;
}

void solution() {
	int time = 0;
	while (time < M) {
		// 1. 구슬이 파괴된다.
		destoryMarble(time);

		// 2. 구슬이 폭발한다.
		marbleExplode();

		// 3. 구슬이 변화한다.
		marbleChange();

		time++;
	}

	// 답안을 구한다.
	getAnswer();
}

int main() {
	cin >> N >> M;
	map.resize(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		magic.push_back({ d - 1, s });
	}
	settingOrderOfMap();

	solution();

	cout << answer << endl;
}