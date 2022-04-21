// 삼성 기출 : 톱니바퀴 (구현 + 재귀)
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector<vector<bool>> wheel(4, vector<bool>(8));
int K;
queue<pair<int, int>> cmd;
// int rightNS = 2;
// int leftNS = 6;

void getInputValue() {
	// 입력값을 받아옴
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			char NS;
			cin >> NS;

			if (NS == '0') wheel[i][j] = 0;
			else wheel[i][j] = 1;
		}
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		int wheelNum, dir;
		cin >> wheelNum >> dir;
		cmd.push({ wheelNum, dir });
	}
}

void rotate(int wheelNum, int dir, int startWheelNum) { // wheelNum에 해당하는 바퀴가 회전한다.
	bool rightNS = wheel[wheelNum][2];
	bool leftNS = wheel[wheelNum][6];

	vector<bool> tmp(8);
	if (dir == 1) { // 시계 방향 회전이라면
		tmp[0] = wheel[wheelNum][7];
		for (int i = 1; i <= 7; i++) {
			tmp[i] = wheel[wheelNum][i - 1];
		}
		wheel[wheelNum] = tmp;
	}
	else { // 반시계 방향 회전이라면
		tmp[7] = wheel[wheelNum][0];
		for (int i = 0; i < 7; i++) {
			tmp[i] = wheel[wheelNum][i + 1];
		}
		wheel[wheelNum] = tmp;
	}

	// 다음 회전할 바퀴 탐색
	// 왼쪽 바퀴 회전 여부 확인
	// (wheelNum - 1 != startWheelNum : 퍼져나가야 하는거지 다시 되돌아와서는 안된다.)
	if (wheelNum > 0 && wheelNum - 1 != startWheelNum) {
		int nxtNS = wheel[wheelNum - 1][2];
		if (leftNS != nxtNS) rotate(wheelNum - 1, dir * -1, wheelNum);
	}

	// 오른쪽 바퀴 회전 여부 확인
	if (wheelNum < 3 && wheelNum + 1 != startWheelNum) {
		int nxtNS = wheel[wheelNum + 1][6];
		if (rightNS != nxtNS) rotate(wheelNum + 1, dir * -1, wheelNum);
	}
}

void solution() {
	while (!cmd.empty()) {
		int wheelNum = cmd.front().first - 1; // 회전할 바퀴 (인덱싱)
		int dir = cmd.front().second; // 회전할 방향
		cmd.pop();

		rotate(wheelNum, dir, wheelNum);
	}
}

int countScore() { // 점수를 계산한다.
	int answer = 0;
	if (wheel[0][0]) answer += 1;
	if (wheel[1][0]) answer += 2;
	if (wheel[2][0]) answer += 4;
	if (wheel[3][0]) answer += 8;
	return answer;
}

int main() {
	// 입력값을 받아옴
	getInputValue();


	solution();

	// 점수를 계산한다.
	cout << countScore() << '\n';
}