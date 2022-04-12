// 백준 9095 : 1, 2, 3 더하기
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;

		// dp[n] = n을 1, 2, 3의 합으로 나타내는 방법의 수
		int* dp = new int[N+1];

		dp[1] = 1;
		dp[2] = 2;
		dp[3] = 4;
		for (int i = 4; i <= N; i++) {
			dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
		}
		cout << dp[N] << endl;
	}
}