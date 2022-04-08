// 백준 1463 : 1로 만들기 (DP)
#include <iostream>
#include <vector>
#include <vector>

using namespace std;

#define MAX 1000000

int main() {
	int N;
	cin >> N;

	vector<int> dp(N + 1, MAX);
	dp[N] = 0;
	if (N % 3 == 0) dp[N / 3] = 1;
	if (N % 2 == 0) dp[N / 2] = 1;
	for (int i = N - 1; i >= 1; i--) {
		dp[i] = min(dp[i], dp[i + 1] + 1);

		if (i % 3 == 0) dp[i / 3] = min(dp[i / 3], dp[i] + 1);
		if (i % 2 == 0) dp[i / 2] = min(dp[i / 2], dp[i] + 1);
	}
	
	cout << dp[1] << endl;
}