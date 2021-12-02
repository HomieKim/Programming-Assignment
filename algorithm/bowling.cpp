#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
struct frm
{	
	int first = 0;;
	int second = 0;
	int third = 0;
	int isStrike = 0;
	int isSpare = 0;
	
};
int main() {

	int a, b,c,t;
	ifstream fin("bowling.inp");
	ofstream fout("bowling.out");
	//cin >> t;
	fin >> t;
	for (int T = 0; T < t; T++) {
		frm frame[10];
		for (int i = 0; i < 10; i++) {
			//cin >> a;
			fin >> a;
			frame[i].first = a;
			if (i == 9) {
				//cin >> b;
				fin >> b;
				frame[i].second = b;
				if (a + b >= 10) {
					//cin >> c;
					fin >> c;
					frame[i].third = c;
				}
			}
			else {
				if (a != 10) {
					//cin >> b;
					fin >> b;
					frame[i].second = b;
					if (a + b == 10) {
						frame[i].isSpare = 1;
					}
				}
				else {
					frame[i].isStrike = 1;
				}

			}

		}

		int ans = 0;
		// °è»ê
		for (int i = 0; i < 10; i++) {
			if (i == 9) {
				ans += frame[i].first + frame[i].second + frame[i].third;
				break;
			}
			if (frame[i].isStrike == 1) {
				if (frame[i + 1].isStrike == 1) {
					if (i == 8) {
						ans += frame[i + 1].first + frame[i + 1].second;
					}
					ans += 10 + frame[i + 2].first;
				}
				else {
					ans += frame[i + 1].first + frame[i + 1].second;
				}

			}
			else if (frame[i].isSpare == 1) {
				ans += frame[i + 1].first;
			}

			ans += frame[i].first + frame[i].second;
		}

		//cout << ans << endl;
		fout << ans << '\n';
	}
	

}