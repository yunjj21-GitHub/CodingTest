// 삼성 기출 : 마법사 상어와 토네이도 (구현)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N; // 지도의 크기
vector<vector<int>> map; // 각 칸의 모레의 양을 저장
// 토네이도의 움직임 정의 (좌, 하, 우, 상)
int t_dy[4] = { 0, 1, 0, -1 };
int t_dx[4] = { -1, 0, 1, 0 };
// 모래의 움직임 정의 (좌, 하, 우, 상)
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
vector<int> s_md = { 1, 7, 10, 2, 1, 7, 10, 2, 5}; // 사이즈 9

int answer = 0; // 영역 밖으로 나간 모래 (답안)

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
	// 토네이도의 초기위치 설정 (map의 인덱스 : 0~N-1)
	int y = N / 2;
	int x = N / 2;
	int dir = 0; // 토네이도의 진행 방향 (0~3)
	int len = 1; // 토네이도의 직진 길이

	while (isItRightRange(y, x)) {
		// 토네이도의 움직임
		for (int i = 0; i < len; i++) {
			y += t_dy[dir];
			x += t_dx[dir];

			if (!isItRightRange(y, x)) break;

			// 모래의 움직임
			if (!map[y][x]) continue; // 해당 좌표에 모래가 없다면

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
				else { // 영역을 벗어나지 않았다면
					map[nxtY][nxtX] += dis;
				}
			}
		}

		// 진행방향 갱신
		dir = (++dir) % 4;
		if (dir % 2 == 0) len++; // 0 또는 2 방향일때, 직진길이 갱신
	}
}

int main() {
	getInputValue();

	solution();

	cout << answer << endl;
}