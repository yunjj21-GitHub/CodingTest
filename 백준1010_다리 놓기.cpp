// 백준 1010 : 다리 놓기 (완전탐색)
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int T; // 테스트 케이스의 수
	cin >> T;
	while (T--) {
		int N, M; // 서쪽 사이트의 수 N, 동쪽 사이트의 수 M
		cin >> N >> M;

		int dp[31][31] = { 0 };
		for (int i = 1; i <= M - N + 1; i++) {
			dp[1][i] = 1;
		}

		for (int i = 2; i <= N; i++) {
			for (int j = i; j <= M - (N - i); j++) {
				dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
			}
		}

		int result = 0;
		for (int i = N; i <= M; i++) {
			result += dp[N][i];
		}
		cout << result << endl;
	}
}