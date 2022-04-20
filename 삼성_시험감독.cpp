// �Ｚ ���� : ���� ����
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N; // �������� ����
vector<int> num; // �� �����忡 �ִ� �������� ���� ����
int B, C; // ���� �Ѱ������� �ΰ������� ������ �� �ִ� �������� �� B, C
long long answer = 0;

int main() {
	cin >> N;
	num.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
	cin >> B >> C;

	for (int i = 0; i < N; i++) {
		// �ʿ��� �Ѱ������� ���� ���Ѵ�.
		num[i] -= B;
		answer++;

		// �ʿ��� �ΰ������� ���� ���Ѵ�.
		if (num[i] > 0) {
			answer += num[i] / C;
			if (num[i] % C > 0) answer++;
		}
	}

	cout << answer << endl;
}