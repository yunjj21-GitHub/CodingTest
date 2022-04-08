// 백준 9655 : 돌 게임 (DP)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int N; // 돌 개수
	cin >> N;

	// dp[돌 번호] = 해당 돌을 가져간 최소 순서
	int* dp = new int[N + 1];

	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= N; i++) {
		dp[i] = min(dp[i - 1], dp[i - 3]) + 1;
	}

	string result;
	if (dp[N] % 2 == 0) {
		result = "CY"; // 창영이 이긴다.
	}
	else {
		result = "SK"; // 상근이 이긴다.
	}

	cout << result << endl;
}