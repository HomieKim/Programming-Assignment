#include <iostream>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;
int arr[100000];
int T, n;
long long ans = 0;
void merge(int left, int right) {
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = left;
	int rst[100000] = { 0, };

	// ������ ����Ʈ? �� ���� �Ȼ��°� �̸� merge�ϴ� �Լ��̹Ƿ� ���ʸ���Ʈ���� �ּڰ� ���� �� ���� ���� rst�� �ְ� idx�÷��ְ� �ݺ�
	while (i <= mid && j <= right) {
		if (arr[i] > arr[j]) {
			rst[k++] = arr[j++];
			ans += (mid-i+1)*1LL;
		}
		else {
			rst[k++] = arr[i++];
		}
	}
	// �� �ݺ����� ����Ǵ� ���� �� ����迭�� ���� ���� ���� ������� �־��ָ� ��
	// �ΰ��� ���� �� �ϳ��� false�Ǹ� ������ ������ ���� �迭�� ���� �� ���� 
	if (i > mid) {
		while (j <= right) {
			rst[k++] = arr[j++];
		}
	}
	else {
		while (i <= mid) {
			rst[k++] = arr[i++];
		}
	}
	// ���� �迭�� �Ű� ��� �۾�
	for (int m = left; m <= right; m++) {
		arr[m] = rst[m];
	}
}
void divide(int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		divide(left, mid);
		divide(mid + 1, right);
		merge(left, right);
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	freopen("inv.inp", "r", stdin);
	freopen("inv.out", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}

		divide(0, n - 1);
		cout <<ans << '\n';
		ans = 0;
		memset(arr, 0, sizeof(arr));
	}

}