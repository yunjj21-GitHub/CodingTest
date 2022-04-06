// ���� 1010 : �ٸ� ���� (����Ž��)
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int T; // �׽�Ʈ ���̽��� ��
	cin >> T;
	while (T--) {
		int N, M; // ���� ����Ʈ�� �� N, ���� ����Ʈ�� �� M
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