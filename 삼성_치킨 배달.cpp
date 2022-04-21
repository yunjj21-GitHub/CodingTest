// �Ｚ ���� : ġŲ ��� (����Ž�� + ����)
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#define MAX 500000

int answer = MAX;
int N, M;
vector<pair<int, int>> chicken; // {y, x}
vector<pair<int, int>> house; // {y, x}
vector<pair<int, int>> comb;

void getInputValue() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int spot;
			cin >> spot;

			if (spot == 1) house.push_back({ i, j }); // ���̶��
			else if (spot == 2) chicken.push_back({ i, j }); // ġŲ���̶��
		}
	}
}

int makeCalculation() {
	int result = 0;
	for (int i = 0; i < house.size(); i++) {

		// �� ������ ġŲ�Ÿ��� �ּڰ��� ���Ѵ�.
		int disMin = MAX; // ������ ū ������ �ʱ�ȭ
		for (int j = 0; j < comb.size(); j++) {
			int dis = abs(house[i].first - comb[j].first)
				+ abs(house[i].second - comb[j].second);

			// �� ���� ġŲ�Ÿ� �ּڰ� ����
			if (disMin > dis) disMin = dis;
		}

		result += disMin;
	}

	return result;
}

void makeComb(int num, int start) {
	if (num == M) { // M���� ġŲ�� ������ �Ϸ�Ǿ��ٸ�

		// ������ ġŲ�Ÿ� �ּڰ� ����
		int totDis = makeCalculation();
		if (answer > totDis) answer = totDis;

		return;
	}

	for (int i = start; i < chicken.size(); i++) {
		comb[num].first = chicken[i].first;
		comb[num].second = chicken[i].second;
		makeComb(num + 1, i + 1);
	}
}

int main() {
	// �Է°��� �޾ƿ�
	getInputValue();
	
	// M���� ġŲ�� ���� (����Ž��)
	comb.resize(M);
	makeComb(0, 0);

	// ����� ����Ѵ�.
	cout << answer << endl;
}