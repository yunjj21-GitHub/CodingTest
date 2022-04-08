// ���� 9655 : �� ���� (DP)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int N; // �� ����
	cin >> N;

	// dp[�� ��ȣ] = �ش� ���� ������ �ּ� ����
	int* dp = new int[N + 1];

	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= N; i++) {
		dp[i] = min(dp[i - 1], dp[i - 3]) + 1;
	}

	string result;
	if (dp[N] % 2 == 0) {
		result = "CY"; // â���� �̱��.
	}
	else {
		result = "SK"; // ����� �̱��.
	}

	cout << result << endl;
}