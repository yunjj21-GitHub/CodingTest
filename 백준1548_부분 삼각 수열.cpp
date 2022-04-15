#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N; // �Էµ� ������ ũ��
vector<int> num; // �Էµ� ������ ���Ҹ� ����
vector<pair<int, int>> comb(3); // ������� �κ� ������ ���� ���� �� 2���� ū �� 1���� ����
int maxLength; // �κ� �ﰢ ������ �ִ� ũ��

void makeComb(int cnt, int start) {
	if (cnt == 3) {
		if (comb[0].first + comb[1].first > comb[2].first) { // �ﰢ ������ ������ �����ϴ��� Ȯ��
			int len = (comb[2].second - comb[1].second - 1) + 3; // �κ� ������ ũ�⸦ ���Ѵ�.
			if (len > maxLength) {
				// ������ �κ� �ﰢ ������ �ִ� ũ�� ����
				maxLength = len;
			}
		}

		return;
	}
	
	for (int i = start; i < N; i++) {
		comb[cnt].first = num[i];
		comb[cnt].second = i;
		makeComb(cnt + 1, i + 1);
	}
}

void solution() {
	if (N < 3) maxLength = N;
	else maxLength = 2;

	sort(num.begin(), num.end()); // �־��� ���� �������� ����

	// ������ ��� �κ� ������ �����. (����Ž��)
	makeComb(0, 0);
}

int main() {
	int answer; // ���

	cin >> N;
	num.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}

	solution();
	answer = maxLength;

	// ��� ���
	cout << answer << endl;
}