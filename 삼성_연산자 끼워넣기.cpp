// �Ｚ ���� : ������ �����ֱ� (����Ž��)
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N;
vector<int> num(11);
vector<int> opNum(4);
int resMax = -2000000000; // ������ ���� ������ �ʱ�ȭ
int resMin = 2000000000; // ������ ū ������ �ʱ�ȭ
vector<int> numOpUsed(4);

void solution(int res, int numIdx) {
	if (numIdx == N) { // ������ ������ ����� �Ϸ��ߴٸ�
		if (res > resMax) resMax = res;
		if (res < resMin) resMin = res;

		return;
	}

	for (int i = 0; i < 4; i++) {
		if (i == 0 && (numOpUsed[i] < opNum[i])) { // +
			numOpUsed[i]++;
			solution(res + num[numIdx], numIdx + 1);
			numOpUsed[i]--;
		}
		else if (i == 1 && (numOpUsed[i] < opNum[i])) { // -
			numOpUsed[i]++;
			solution(res - num[numIdx], numIdx + 1);
			numOpUsed[i]--;
		}
		else if (i == 2 && (numOpUsed[i] < opNum[i])) { // *
			numOpUsed[i]++;
			solution(res * num[numIdx], numIdx + 1);
			numOpUsed[i]--;
		}
		else if(i==3 && (numOpUsed[i] < opNum[i])) { // /
			numOpUsed[i]++;
			solution(res / num[numIdx], numIdx + 1);
			numOpUsed[i]--;
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
	for (int i = 0; i < 4; i++) {
		cin >> opNum[i];
	}

	solution(num[0], 1);

	cout << resMax << '\n' << resMin << endl;
}