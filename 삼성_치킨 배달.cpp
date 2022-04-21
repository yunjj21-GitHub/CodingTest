// 삼성 기출 : 치킨 배달 (완전탐색 + 구현)
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

			if (spot == 1) house.push_back({ i, j }); // 집이라면
			else if (spot == 2) chicken.push_back({ i, j }); // 치킨집이라면
		}
	}
}

int makeCalculation() {
	int result = 0;
	for (int i = 0; i < house.size(); i++) {

		// 각 집들의 치킨거리의 최솟값을 구한다.
		int disMin = MAX; // 임의의 큰 값으로 초기화
		for (int j = 0; j < comb.size(); j++) {
			int dis = abs(house[i].first - comb[j].first)
				+ abs(house[i].second - comb[j].second);

			// 각 집의 치킨거리 최솟값 갱신
			if (disMin > dis) disMin = dis;
		}

		result += disMin;
	}

	return result;
}

void makeComb(int num, int start) {
	if (num == M) { // M개의 치킨집 선택이 완료되었다면

		// 마을의 치킨거리 최솟값 갱신
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
	// 입력값을 받아옴
	getInputValue();
	
	// M개의 치킨집 선택 (완전탐색)
	comb.resize(M);
	makeComb(0, 0);

	// 결과를 출력한다.
	cout << answer << endl;
}