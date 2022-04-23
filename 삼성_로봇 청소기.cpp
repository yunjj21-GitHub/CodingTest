// 삼성 기출 : 로봇 청소기
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
int map[50][50];
bool finish[50][50]; // 청소가 완료되었는지 저장
int robotY, robotX, dir;

// 차례로 북, 동, 남, 서로의 움직임을 정의
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int answer = 0;

// 입력값을 받아옴
void getInputValue() {
	cin >> N >> M;
	cin >> robotY >> robotX >> dir;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void solution() {
	while (1) {
		// 1. 현재좌표 청소
		int flag = true;

		if (!finish[robotY][robotX]) {
			finish[robotY][robotX] = true;
			answer++;
		}

		// 2-a. 진행방향의 바로 왼쪽 좌표 확인
		for (int i = 0; i < 4; i++) {
			if (dir > 0) dir--;
			else dir = 3;
			int nxtY = robotY + dy[dir];
			int nxtX = robotX + dx[dir];

			// 청소되지 않은 빈 공간이라면
			if (!finish[nxtY][nxtX] && !map[nxtY][nxtX]) {
				// 한칸 전진
				robotY = nxtY;
				robotX = nxtX;
				
				flag = false; // 1번으로 돌아갈 것임을 표시
				break;
			}
		}

		if (flag) { // 2-b. 종료조건 확인
			// 진행방향의 바로 뒤쪽 좌표
			int backY, backX;
			if (dir <= 1) {
				backY = robotY + dy[dir + 2];
				backX = robotX + dx[dir + 2];
			}
			else {
				backY = robotY + dy[dir - 2];
				backX = robotX + dx[dir - 2];
			}

			// 진행방향의 바로 뒤쪽 좌표가 벽이라면 작동을 멈춘다.
			if (map[backY][backX] == 1) break;
			else { // 진행방향의 바로 뒤쪽 좌표가 벽이 아니라면 한칸 후진한다.
				robotY = backY;
				robotX = backX;
			}
		}
	}
}

int main() {
	// 입력값을 받아옴
	getInputValue();

	solution();

	cout << answer << endl;
}