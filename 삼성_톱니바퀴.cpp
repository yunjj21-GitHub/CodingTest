// �Ｚ ���� : ��Ϲ��� (���� + ���)
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector<vector<bool>> wheel(4, vector<bool>(8));
int K;
queue<pair<int, int>> cmd;
// int rightNS = 2;
// int leftNS = 6;

void getInputValue() {
	// �Է°��� �޾ƿ�
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			char NS;
			cin >> NS;

			if (NS == '0') wheel[i][j] = 0;
			else wheel[i][j] = 1;
		}
	}
	cin >> K;
	for (int i = 0; i < K; i++) {
		int wheelNum, dir;
		cin >> wheelNum >> dir;
		cmd.push({ wheelNum, dir });
	}
}

void rotate(int wheelNum, int dir, int startWheelNum) { // wheelNum�� �ش��ϴ� ������ ȸ���Ѵ�.
	bool rightNS = wheel[wheelNum][2];
	bool leftNS = wheel[wheelNum][6];

	vector<bool> tmp(8);
	if (dir == 1) { // �ð� ���� ȸ���̶��
		tmp[0] = wheel[wheelNum][7];
		for (int i = 1; i <= 7; i++) {
			tmp[i] = wheel[wheelNum][i - 1];
		}
		wheel[wheelNum] = tmp;
	}
	else { // �ݽð� ���� ȸ���̶��
		tmp[7] = wheel[wheelNum][0];
		for (int i = 0; i < 7; i++) {
			tmp[i] = wheel[wheelNum][i + 1];
		}
		wheel[wheelNum] = tmp;
	}

	// ���� ȸ���� ���� Ž��
	// ���� ���� ȸ�� ���� Ȯ��
	// (wheelNum - 1 != startWheelNum : ���������� �ϴ°��� �ٽ� �ǵ��ƿͼ��� �ȵȴ�.)
	if (wheelNum > 0 && wheelNum - 1 != startWheelNum) {
		int nxtNS = wheel[wheelNum - 1][2];
		if (leftNS != nxtNS) rotate(wheelNum - 1, dir * -1, wheelNum);
	}

	// ������ ���� ȸ�� ���� Ȯ��
	if (wheelNum < 3 && wheelNum + 1 != startWheelNum) {
		int nxtNS = wheel[wheelNum + 1][6];
		if (rightNS != nxtNS) rotate(wheelNum + 1, dir * -1, wheelNum);
	}
}

void solution() {
	while (!cmd.empty()) {
		int wheelNum = cmd.front().first - 1; // ȸ���� ���� (�ε���)
		int dir = cmd.front().second; // ȸ���� ����
		cmd.pop();

		rotate(wheelNum, dir, wheelNum);
	}
}

int countScore() { // ������ ����Ѵ�.
	int answer = 0;
	if (wheel[0][0]) answer += 1;
	if (wheel[1][0]) answer += 2;
	if (wheel[2][0]) answer += 4;
	if (wheel[3][0]) answer += 8;
	return answer;
}

int main() {
	// �Է°��� �޾ƿ�
	getInputValue();


	solution();

	// ������ ����Ѵ�.
	cout << countScore() << '\n';
}