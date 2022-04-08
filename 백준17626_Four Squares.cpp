// น้มุ 17626 : Four Squares (DP)
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;

	int dp[50001] = { 0 };
	dp[1] = 1;
	for (int i = 1; i <= n; i++) {
		dp[i] = dp[1] + dp[i - 1];
		for (int j = 2; j * j <= i; j++) {
			dp[i] = min(dp[i], 1 + dp[i - j * j]);
		}
	}
	cout << dp[n] << endl;
}