// 삼성 기출 : 컨베이어 벨트 위의 로봇 (구현)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, K;
int beltLen;
vector<pair<int, bool>> belt; // {dur, isThereRobot}
int answer = 0;

// 입력값을 받아옴
void getInputValue() {
	cin >> N >> K; 
	beltLen = 2 * N;
	for (int i = 0; i < beltLen; i++) {
		int dur;
		cin >> dur;
		belt.push_back({ dur, false });
	}
}

// 컨베이어 벨트의 회전
void conveyorBeltTurns() {
	vector<pair<int, bool>> tmp(beltLen);
	tmp[0].first = belt[beltLen - 1].first;
	tmp[0].second = belt[beltLen - 1].second;
	for (int i = 1; i < beltLen; i++) {
		tmp[i].first = belt[i - 1].first;
		tmp[i].second = belt[i - 1].second;
	}
	belt = tmp;
}

// 로봇의 움직임
void moveRobot() {
	for (int i = N-2; i >= 0; i--) {
		// 해당 위치에 로봇이 없다면
		if (!belt[i].second) continue;
		
		// 이동할 칸의 내구성이 1이하거나 이동할 칸에 로봇이 있다면
		if (belt[i + 1].first < 1 || belt[i + 1].second) continue;

		// 로봇이 이동
		belt[i].second = false;
		belt[i + 1].first--;
		belt[i + 1].second = true;
	}
}

void letDownRobot() {
	if (belt[N - 1].second) belt[N - 1].second = false;
}

void putUpNewRobot() {
	if (belt[0].first > 0) {
		belt[0].first--;
		belt[0].second = true;
	}
}

bool checkTotalDur() {
	int cnt = 0;
	for (int i = 0; i < beltLen; i++) {
		if (belt[i].first == 0) cnt++;
	}

	if (cnt >= K) return false;
	else return true;
}

void solution() {
	while (checkTotalDur()) {
		// 단계 정보 갱신
		answer++;

		// 회전한다. (컨베이어 벨트의 회전 + 로봇의 움직임)
		// 컨베이어 벨트의 회전
		conveyorBeltTurns();

		// 내리는 위치에 로봇이 있다면 내린다.
		letDownRobot();

		// 로봇의 움직임
		moveRobot();

		// 내리는 위치에 로봇이 있다면 내린다.
		letDownRobot();

		// 새로운 로봇을 올린다.
		putUpNewRobot();
	}
}

int main() {
	// 입력값을 받아옴
	getInputValue();

	solution();

	cout << answer << endl;
}