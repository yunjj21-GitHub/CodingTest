// �Ｚ ���� : �����̾� ��Ʈ ���� �κ� (����)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, K;
int beltLen;
vector<pair<int, bool>> belt; // {dur, isThereRobot}
int answer = 0;

// �Է°��� �޾ƿ�
void getInputValue() {
	cin >> N >> K; 
	beltLen = 2 * N;
	for (int i = 0; i < beltLen; i++) {
		int dur;
		cin >> dur;
		belt.push_back({ dur, false });
	}
}

// �����̾� ��Ʈ�� ȸ��
void conveyorBeltTurns() {
	vector<pair<int, bool>> tmp(beltLen);
	tmp[0].first = belt[beltLen - 1].first;
	tmp[0].second = belt[beltLen - 1].second;
	for (int i = 1; i < beltLen; i++) {
		tmp[i].first = belt[i - 1].first;
		tmp[i].second = belt[i - 1].second;
	}
	belt = tmp;
}

// �κ��� ������
void moveRobot() {
	for (int i = N-2; i >= 0; i--) {
		// �ش� ��ġ�� �κ��� ���ٸ�
		if (!belt[i].second) continue;
		
		// �̵��� ĭ�� �������� 1���ϰų� �̵��� ĭ�� �κ��� �ִٸ�
		if (belt[i + 1].first < 1 || belt[i + 1].second) continue;

		// �κ��� �̵�
		belt[i].second = false;
		belt[i + 1].first--;
		belt[i + 1].second = true;
	}
}

void letDownRobot() {
	if (belt[N - 1].second) belt[N - 1].second = false;
}

void putUpNewRobot() {
	if (belt[0].first > 0) {
		belt[0].first--;
		belt[0].second = true;
	}
}

bool checkTotalDur() {
	int cnt = 0;
	for (int i = 0; i < beltLen; i++) {
		if (belt[i].first == 0) cnt++;
	}

	if (cnt >= K) return false;
	else return true;
}

void solution() {
	while (checkTotalDur()) {
		// �ܰ� ���� ����
		answer++;

		// ȸ���Ѵ�. (�����̾� ��Ʈ�� ȸ�� + �κ��� ������)
		// �����̾� ��Ʈ�� ȸ��
		conveyorBeltTurns();

		// ������ ��ġ�� �κ��� �ִٸ� ������.
		letDownRobot();

		// �κ��� ������
		moveRobot();

		// ������ ��ġ�� �κ��� �ִٸ� ������.
		letDownRobot();

		// ���ο� �κ��� �ø���.
		putUpNewRobot();
	}
}

int main() {
	// �Է°��� �޾ƿ�
	getInputValue();

	solution();

	cout << answer << endl;
}