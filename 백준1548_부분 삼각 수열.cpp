#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N; // 입력될 수열의 크기
vector<int> num; // 입력된 수열의 원소를 저장
vector<pair<int, int>> comb(3); // 만들어진 부분 수열의 가장 작은 값 2개와 큰 값 1개를 저장
int maxLength; // 부분 삼각 수열의 최대 크기

void makeComb(int cnt, int start) {
	if (cnt == 3) {
		if (comb[0].first + comb[1].first > comb[2].first) { // 삼각 수열의 조건을 만족하는지 확인
			int len = (comb[2].second - comb[1].second - 1) + 3; // 부분 수열의 크기를 구한다.
			if (len > maxLength) {
				// 가능한 부분 삼각 수열의 최대 크기 갱신
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

	sort(num.begin(), num.end()); // 주어진 수열 오름차순 정렬

	// 가능한 모든 부분 수열을 만든다. (완전탐색)
	makeComb(0, 0);
}

int main() {
	int answer; // 답안

	cin >> N;
	num.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}

	solution();
	answer = maxLength;

	// 답안 출력
	cout << answer << endl;
}