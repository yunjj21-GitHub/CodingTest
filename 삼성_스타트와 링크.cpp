// 삼성 기출 : 스타트와 링크 (완전탐색)
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int N;
vector<vector<int>> ability(20, vector<int>(20));
bool team[20];
int answer = 10000; // 임의의 큰값으로 초기화

void solution(int num, int nxtPer) {
	if (num == N / 2) { // 팀 나누기가 끝났다면
		vector<int> start;
		vector<int> link;
		for (int i = 0; i < N; i++) {
			if (team[i]) start.push_back(i);
			else link.push_back(i);
		}

		// 각 팀의 능력치를 구함
		int startAbiity = 0;
		int linkAbiity = 0;
		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				startAbiity += ability[start[i]][start[j]];
				linkAbiity += ability[link[i]][link[j]];
			}
		}

		// 팀의 능력치 차이를 구함
		int result = abs(startAbiity - linkAbiity);

		// 답안 갱신
		if (result < answer) answer = result;

		return;
	}

	// 팀을 나눈다. (완전탐색)
	for (int i = nxtPer; i < N; i++) {
		team[i] = true;
		solution(num + 1, i+1);
		team[i] = false;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> ability[i][j];
		}
	}

	solution(0, 0);

	cout << answer << endl;
}