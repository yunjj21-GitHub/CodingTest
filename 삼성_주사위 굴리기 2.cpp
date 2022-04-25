// 삼성 기출 : 주사위 굴리기 2 (구현 + DFS)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M; // 지도의 세로 길이 N, 가로 길이 M
int map[20][20]; // 지도 정보를 저장
int K; // 주사위의 이동 횟수
int answer = 0; // 답안
vector<int> dice(6); // 주사위의 상태 정보를 저장 {윗, 북, 동, 서, 남, 밑}
int dir = 0; // 주사위의 이동 방향을 저장 (0 : 우, 1 : 하, 2 : 좌, 3 : 상)
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

// 주사위를 굴리는 메서드
void rollDice() {
	vector<int> tmp;
	// {윗, 북, 동, 서, 남, 밑}
	if (dir == 0) { // 우
		tmp = { dice[3], dice[1], dice[0], dice[5], dice[4], dice[2] };
	}
	else if (dir == 1) { // 하
		tmp = { dice[1], dice[5], dice[2], dice[3], dice[0], dice[4] };
	}
	else if (dir == 2) { // 좌
		tmp = { dice[2], dice[1], dice[5], dice[0], dice[4], dice[3] };
	}
	else { // 상
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

	// visit 배열 초기화
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visit[i][j] = false;
		}
	}
}

void setDir(int y, int x, int num) {
	if (dice[5] > map[y][x]) { // 시계방향으로 90도 회전
		dir = (++dir) % 4;
	}
	else if(dice[5] < map[y][x]) { // 반시계방향으로 90도 회전
		dir = (dir += 3) % 4;
	}
}

void solution() {
	// 주사위 상태 초기 설정
	int y = 0;
	int x = 0;
	dice = { 1, 2, 3, 4, 5, 6 };

	while (K--) {
		// 주사위가 위치할 다음 좌표
		y += dy[dir];
		x += dx[dir];

		// 이동 방향에 칸이 없다면
		if (0 > y || y >= N || 0 > x || x >= M) {
			dir = (dir += 2) % 4; // 이동 방향을 반대로 한다.
			y += (dy[dir] * 2); // 이동 취소 + 반대 방향으로 한 칸
			x += (dx[dir] * 2); 
		}

		rollDice(); // 한 칸 굴러간다.
		
		getScore(y, x, map[y][x]); // 점수를 획득한다.

		setDir(y, x, map[y][x]); // 다음 진행 방향 설정
	}
}

int main() {
	getInputValue();

	solution();

	cout << answer << endl;
}