// �Ｚ ���� : ��ŸƮ�� ��ũ (����Ž��)
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int N;
vector<vector<int>> ability(20, vector<int>(20));
bool team[20];
int answer = 10000; // ������ ū������ �ʱ�ȭ

void solution(int num, int nxtPer) {
	if (num == N / 2) { // �� �����Ⱑ �����ٸ�
		vector<int> start;
		vector<int> link;
		for (int i = 0; i < N; i++) {
			if (team[i]) start.push_back(i);
			else link.push_back(i);
		}

		// �� ���� �ɷ�ġ�� ����
		int startAbiity = 0;
		int linkAbiity = 0;
		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				startAbiity += ability[start[i]][start[j]];
				linkAbiity += ability[link[i]][link[j]];
			}
		}

		// ���� �ɷ�ġ ���̸� ����
		int result = abs(startAbiity - linkAbiity);

		// ��� ����
		if (result < answer) answer = result;

		return;
	}

	// ���� ������. (����Ž��)
	for (int i = nxtPer; i < N; i++) {
		team[i] = true;
		solution(num + 1, i+1);
		team[i] = false;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> ability[i][j];
		}
	}

	solution(0, 0);

	cout << answer << endl;
}