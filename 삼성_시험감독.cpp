// 삼성 기출 : 시험 감독
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N; // 시험장의 개수
vector<int> num; // 각 시험장에 있는 응시자의 수를 저장
int B, C; // 각각 총감독관과 부감독관이 감시할 수 있는 응시자의 수 B, C
long long answer = 0;

int main() {
	cin >> N;
	num.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
	cin >> B >> C;

	for (int i = 0; i < N; i++) {
		// 필요한 총감독관의 수를 구한다.
		num[i] -= B;
		answer++;

		// 필요한 부감독관의 수를 구한다.
		if (num[i] > 0) {
			answer += num[i] / C;
			if (num[i] % C > 0) answer++;
		}
	}

	cout << answer << endl;
}