// ���� 4358 : ������ (�ؽ�)
#include <iostream>
#include <string>
#include <map>
#include <cmath>

using namespace std;

int main() {
	int tot = 0; // �Էµ� ������ ��ü ����
	map<string, int> trees; // �� ������ ���� ������ ����

	while (1) {
		string species;
		getline(cin, species);
		if (cin.eof()) break; // EOF�� �ԷµǸ� �ݺ��� ����
		trees[species]++;

		tot++;
	}

	// ��� ���
	for (auto tree : trees) {
		double ratio = (double)tree.second / tot;
		double percentage = ratio * 100;

		// �Ҽ��� 4°�ڸ����� �ݿø� ó��
		percentage *= 10000;
		percentage = round(percentage);
		percentage /= 10000;

		// �Ҽ��� 4°�ڸ����� ���
		cout << fixed;
		cout.precision(4);
		cout << tree.first << " " << percentage << endl;
	}
}