// 백준 4358 : 생태학 (해시)
#include <iostream>
#include <string>
#include <map>
#include <cmath>

using namespace std;

int main() {
	int tot = 0; // 입력된 나무의 전체 개수
	map<string, int> trees; // 각 나무의 종과 개수를 저장

	while (1) {
		string species;
		getline(cin, species);
		if (cin.eof()) break; // EOF가 입력되면 반복문 종료
		trees[species]++;

		tot++;
	}

	// 결과 출력
	for (auto tree : trees) {
		double ratio = (double)tree.second / tot;
		double percentage = ratio * 100;

		// 소수점 4째자리에서 반올림 처리
		percentage *= 10000;
		percentage = round(percentage);
		percentage /= 10000;

		// 소수점 4째자리까지 출력
		cout << fixed;
		cout.precision(4);
		cout << tree.first << " " << percentage << endl;
	}
}