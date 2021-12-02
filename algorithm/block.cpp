#include <iostream>
#include <vector>
#include <algorithm>


#pragma warning(disable:4996)
using namespace std;
struct Block
{
	pair<int, int> lower_left;
	pair<int, int> upper_right;
	Block(int x, int y, int p, int q) {
		this->lower_left.first = x;
		this->lower_left.second = y;
		this->upper_right.first = p;
		this->upper_right.second = q;
	}
}typedef block;
int T, n;
vector<block> vec;
bool cmp1(block& b1, block& b2) {	// ���� �Ʒ� ��ǥ�� y��(second)�������� ����
	return b1.lower_left.second < b2.lower_left.second;
}

bool cmp2(block& b1, block& b2) {	// ���� �Ʒ� ��ǥ�� x��(first)�������� ����
	return b1.lower_left.first < b2.lower_left.first;
}

vector<int> idx;

// ���� ��� : upper_right�� second���� �ִ��� ���̰�, upper_right�� first�� �ִ��� ����
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//freopen("block.inp", "r", stdin);
	//freopen("block.out", "w", stdout);
	cin >> T;

	while (T--) {
		cin >> n;
		int x1, x2, y1, y2;
		for (int i = 0; i < n; i++) {
			cin >> x1 >> y1 >> x2 >> y2;
			vec.push_back(Block(x1, y1, x2, y2));
		}

		bool flag;
		while (true) {
			flag = false;
			//�Ʒ������� �̵� ����
			sort(vec.begin(), vec.end(), cmp1);
			if (vec[0].lower_left.second != 0) {
				vec[0].upper_right.second = vec[0].upper_right.second - vec[0].lower_left.second;
				vec[0].lower_left.second = 0;
				flag = true;
			}
			for (int i = 1; i < vec.size(); i++) {
				int max_height = 0;
				for (int j = i - 1; j >= 0; j--) {	 // 3���� ��� ��� 1. ������ ��ħ 2. ���� ��ħ 3. �ȿ� ���Ե�
					if (vec[j].upper_right.second <= vec[i].lower_left.second && !(vec[j].lower_left.first >= vec[i].upper_right.first || vec[j].upper_right.first <= vec[i].lower_left.first)) {
						max_height = max(max_height, vec[j].upper_right.second);
					}
				}
				if (vec[i].lower_left.second == max_height) continue;
				vec[i].upper_right.second = max_height + vec[i].upper_right.second - vec[i].lower_left.second;
				vec[i].lower_left.second = max_height;
				flag = true;
			}

			// �������� �̵� ����
			sort(vec.begin(), vec.end(), cmp2);
			if (vec[0].lower_left.first != 0) {
				vec[0].upper_right.first = vec[0].upper_right.first - vec[0].lower_left.first;
				vec[0].lower_left.first = 0;
				flag = true;
			}
			for (int i = 1; i < vec.size(); i++) {
				int max_width = 0;
				for (int j = i - 1; j >= 0; j--) {
					if (vec[j].upper_right.first <= vec[i].lower_left.first && !(vec[j].lower_left.second >= vec[i].upper_right.second || vec[j].upper_right.second <= vec[i].lower_left.second)) {
						max_width = max(max_width, vec[j].upper_right.first);
					}
				}
				if (vec[i].lower_left.first == max_width) continue;
				vec[i].upper_right.first = max_width + vec[i].upper_right.first - vec[i].lower_left.first;
				vec[i].lower_left.first = max_width;
				flag = true;
			}

			if (!flag) break;
		}
		int width = 0;
		int height = 0;
		for (int i = 0; i < vec.size(); i++) {
			width = max(width, vec[i].upper_right.first);
			height = max(height, vec[i].upper_right.second);
		}
		idx.clear();
		vec.clear();
		cout << width << " " << height << '\n';
	}

}