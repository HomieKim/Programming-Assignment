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

	// 양쪽의 리스트? 는 정렬 된상태고 이를 merge하는 함수이므로 양쪽리스트에서 최솟값 비교후 더 작은 값을 rst에 넣고 idx올려주고 반복
	while (i <= mid && j <= right) {
		if (arr[i] > arr[j]) {
			rst[k++] = arr[j++];
			ans += (mid-i+1)*1LL;
		}
		else {
			rst[k++] = arr[i++];
		}
	}
	// 위 반복문이 종료되는 조건 후 결과배열에 들어가지 못한 값을 순서대로 넣어주면 됨
	// 두개의 조건 중 하나라도 false되면 끝나기 때문에 남는 배열이 생길 수 있음 
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
	// 원래 배열에 옮겨 담는 작업
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