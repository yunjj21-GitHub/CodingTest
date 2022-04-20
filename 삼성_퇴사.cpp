// 삼성 기출 : 퇴사 (DP + 완전탐색)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<pair<int, int>> job(16);
int dp[30]; // dp[day] = day날 저녁까지 얻을 수 있는 최대 수익

int solution() {
	for (int startDay = 1; startDay <= N; startDay++) {
		int endDay = startDay + job[startDay].first - 1;

		int preMax = 0;
		for (int preDay = 0; preDay < startDay; preDay++) {
			if (dp[preDay] > preMax) preMax = dp[preDay];
		}
		dp[endDay] = max(job[startDay].second + preMax, dp[endDay]);
	}

	// 결과 출력
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		if (dp[i] > answer) answer = dp[i];
	}

	return answer;
}

int main() {
	// 입력값을 받아옴
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> job[i].first >> job[i].second;
	}

	// 결과 출력
	cout << solution() << endl;
}