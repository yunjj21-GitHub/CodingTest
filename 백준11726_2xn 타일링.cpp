// 백준 11726 : 2xn 타일링 (DP)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MOD 10007

int main() {
	int N;
	cin >> N;

	int *dp = new int[N + 1];
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= N; i++) {
		dp[i] = ((dp[i - 1] % MOD) + (dp[i - 2] % MOD)) % MOD;
	}
	cout << dp[N] << endl;
}