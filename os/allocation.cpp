#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Process {
	int requestTime;
	int exTime;
	int size;
	int PID;
	int endTime;
	int alloc = 0;

}typedef ps;

struct Memory {
	int adress;
	int mPID;
	int mSize;

}typedef memory;

int n;

vector<memory> Mem;
vector<ps*> ready;


// 적재, 반환, 큐 검사

void allcMemory(int i, ps* ps) {
	memory tmp;
	
	tmp.adress = Mem[i].adress;
	tmp.mPID = ps->PID;
	tmp.mSize = ps->size;
	Mem[i].adress += ps->size;
	Mem[i].mSize -= ps->size;
	Mem.insert(Mem.begin()+i, tmp);
	
}

void returnMemory(ps* ps) {
	// ps이 pid가 메모리벡터에 몇번째 인덱스에 있는지 확인
	// 그 인덱스가 0일때 아닐때 2가지 경우로 나뉨, 아닐 때의 경우 중간 값이므로 왼쪽오른쪽 살펴봐야함
	int memidx = 0;
	for (int i = 0; i < Mem.size(); i++) {
		if (ps->PID == Mem[i].mPID) {
			memidx = i;
			break;
		}
	}

	if (memidx == 0) {
		// 인덱스가 0 이면 오른쪽에 있는게 -1 인지 아닌지 확인
		if (Mem[memidx + 1].mPID == -1) {
			Mem[memidx].mPID = -1;
			Mem[memidx].mSize += Mem[memidx + 1].mSize;
			Mem.erase(Mem.begin() + (memidx + 1));
		}
		else {
			Mem[memidx].mPID = -1;
		}
	}
	/*else if (memidx == n - 1) {
		if (Mem[memidx - 1].mPID == -1) {
			Mem[memidx].mPID = -1;
			Mem[memidx].adress = Mem[memidx - 1].adress;
			Mem[memidx].mSize += Mem[memidx - 1].mSize;
			Mem.erase(Mem.begin() + (memidx - 1));
		}
		else {
			Mem[memidx].mPID = -1;
		}*/
//}
	else {
		// 인덱스가 중간일 때 경우 -> 왼쪽만 -1, 오른쪽만 -1, 둘다 -1, 둘다 양수
		if (Mem[memidx - 1].mPID == -1 && Mem[memidx + 1].mPID >= 0) {	// 왼쪽만 -1
			Mem[memidx].adress = Mem[memidx - 1].adress;
			Mem[memidx].mPID = -1;
			Mem[memidx].mSize += Mem[memidx - 1].mSize;
			Mem.erase(Mem.begin() + (memidx - 1));
		}
		else if (Mem[memidx - 1].mPID >= 0 && Mem[memidx + 1].mPID == -1) { // 오른쪽만 -1
			Mem[memidx].mPID = -1;
			Mem[memidx].mSize += Mem[memidx + 1].mSize;
			Mem.erase(Mem.begin() + (memidx + 1));
		}
		else if (Mem[memidx - 1].mPID == -1 && Mem[memidx + 1].mPID == -1) { //양쪽 다 -1
			Mem[memidx].adress = Mem[memidx - 1].adress;
			Mem[memidx].mPID = -1;
			Mem[memidx].mSize += Mem[memidx - 1].mSize + Mem[memidx + 1].mSize;
			Mem.erase(Mem.begin() + (memidx + 1));
			Mem.erase(Mem.begin() + (memidx - 1));
		}
		else {
			Mem[memidx].mPID = -1;
		}
	}
}
bool chkFirst(vector<memory> Mem, ps* ps) {
	for (int i = 0; i < Mem.size(); i++) {
		if (Mem[i].mPID == -1 && ps->size <= Mem[i].mSize) {
			allcMemory(i, ps);
			return true;
		}
	}
	return false;
}
bool chkBest(vector<memory> Mem, ps* ps) {
	int key = 1001;
	bool chk = false;
	int keyidx = 0;
	for (int i = 0; i < Mem.size(); i++) {
		if (Mem[i].mPID == -1 && ps->size <= Mem[i].mSize) {
			if (key > Mem[i].mSize) {
				key = Mem[i].mSize;
				keyidx = i;
			}
			chk = true;
		}
	}
	if (chk == true) {
		allcMemory(keyidx, ps);
		return true;
	}
	else {
		return false;
	}
}
bool chkWorst(vector<memory> Mem, ps* ps) {
	int key = 0;
	bool chk = false;
	int keyidx = 0;
	for (int i = 0; i < Mem.size(); i++) {
		if (Mem[i].mPID == -1 && ps->size <= Mem[i].mSize) {
			if (key < Mem[i].mSize) {
				key = Mem[i].mSize;
				keyidx = i;
			}
			chk = true;
		}
	}
	if (chk == true) {
		allcMemory(keyidx, ps);
		return true;
	}
	else {
		return false;
	}
}

int main() {
	ifstream fin("allocation.inp");
	ofstream fout("allocation.out");


	// 데이터 입력 받기

	fin >> n;
	ps** list = (ps**)malloc(sizeof(ps*) * n - 1);
	ps** list2 = (ps**)malloc(sizeof(ps*) * n - 1);
	ps** list3 = (ps**)malloc(sizeof(ps*) * n - 1);
	for (int i = 0; i < n; i++) {
		list[i] = new ps();
		list[i]->PID = i;
		fin >> list[i]->requestTime;
		fin >> list[i]->exTime;
		fin >> list[i]->size;
	}
	for (int i = 0; i < n; i++) {
		list2[i] = new ps();
		list2[i]->PID = i;
		list2[i]->requestTime = list[i]->requestTime;
		list2[i]->exTime = list[i]->exTime;
		list2[i]->size = list[i]->size;
		list3[i] = new ps();
		list3[i]->PID = i;
		list3[i]->requestTime = list[i]->requestTime;
		list3[i]->exTime = list[i]->exTime;
		list3[i]->size = list[i]->size;
	}
	// 출력

	memory initmem = { 0, -1, 1000 };
	//list 복사, memory할당
	Mem.push_back(initmem);

	int time = 0;
	while (true) {
		int chk = 0;
		for (int i = 0; i < n; i++) {
			if (list[i]->endTime == time && list[i]->endTime != 0) { // time이 종료시간과 같으면 반환해야함
				// 반환하면 메모리 상태 갱신  -1 연속되는 거있으면 합쳐 주고 다시 할당 되는지 봐야함
				// 프로세스가 동시에 반환 될 수도 있으니까 반환 다 한 후에  chk함
				returnMemory(list[i]);

				chk++;
			}
		}
		if (chk > 0) {	// 반환이 있었을 경우 que체크
			int k = ready.size();
			for (int i = 0; i < k; i++) {
				ps* j = ready.front();
				ready.erase(ready.begin());
				if (chkFirst(Mem, j)) {
					list[j->PID]->endTime = time + list[j->PID]->exTime;
					list[j->PID]->alloc = 1;
				}
				else {
					ready.push_back(j);
				}
			}
		}

		for (int i = 0; i < n; i++) {
			if (list[i]->requestTime == time) { // 요청시간이 time과 같으면
				// firstfit 으로 메모리에 적재 적재할 때 크기보다 작은게 없으면 대기큐에 들어감
				// 대기큐에 있는 시간동안 endtime에 합쳐줘야함 = 대기큐에서 요청이 나가는 time을 더해주면 될 듯
				if (chkFirst(Mem, list[i])) {	// 조건 검사에서 firstfit으로 할당 만약 할당할게 없으면 대기큐에 들어감
					list[i]->endTime = list[i]->requestTime + list[i]->exTime;
					list[i]->alloc = 1;
				}
				else {
					ready.push_back(list[i]);
				}
			}
		}
		if (list[n - 1]->alloc == 1) {
			break;
		}
		time++;
	}

	for (int i = 0; i < Mem.size(); i++) {
		if (Mem[i].mPID == n - 1) {
			fout << Mem[i].adress << endl;
			//cout << Mem[i].adress << endl;
		}
	}
	
	//best
	if (!Mem.empty()) {
		Mem.clear();
	}
	if (!ready.empty()) {
		ready.clear();
	}
	
	Mem.push_back(initmem);

	

	time = 0;
	while (true) {


		int chk = 0;
		for (int i = 0; i < n; i++) {
			if (list2[i]->endTime == time && list2[i]->endTime != 0) {
				returnMemory(list2[i]);

				chk++;
			}
		}
		if (chk > 0) {	// 반환이 있었을 경우 que체크
			int k = ready.size();
			for (int i = 0; i < k; i++) {
				ps* j = ready.front();
				ready.erase(ready.begin());
				if (chkBest(Mem, j)) {
					list2[j->PID]->endTime = time + list2[j->PID]->exTime;
					list2[j->PID]->alloc = 1;
				}
				else {
					ready.push_back(j);
				}
			}
		}

		for (int i = 0; i < n; i++) {
			if (list2[i]->requestTime == time) {
				if (chkBest(Mem, list2[i])) {
					list2[i]->endTime = list2[i]->requestTime + list2[i]->exTime;
					list2[i]->alloc = 1;
				}
				else {
					ready.push_back(list2[i]);
				}
			}
		}

		if (list2[n - 1]->alloc == 1) {
			break;
		}
		time++;
	}

	for (int i = 0; i < Mem.size(); i++) {
		if (Mem[i].mPID == n - 1) {
			fout << Mem[i].adress << endl;
			//cout << Mem[i].adress << endl;
		}
	}

	//worst
	if (!Mem.empty()) {
		Mem.clear();
	}
	if (!ready.empty()) {
		ready.clear();
	}
	
	Mem.push_back(initmem);


	time = 0;
	while (true) {

		int chk = 0;
		for (int i = 0; i < n; i++) {
			if (list3[i]->endTime == time && list3[i]->endTime != 0) {
				returnMemory(list3[i]);
				chk++;
			}
		}
		if (chk > 0) {	// 반환이 있었을 경우 que체크
			int k = ready.size();
			for (int i = 0; i < k; i++) {
				ps* j = ready.front();
				ready.erase(ready.begin());
				if (chkWorst(Mem, j)) {
					list3[j->PID]->endTime = time + list3[j->PID]->exTime;
					list3[j->PID]->alloc = 1;
				}
				else {
					ready.push_back(j);
				}
			}
		}

		for (int i = 0; i < n; i++) {
			if (list3[i]->requestTime == time) {
				if (chkWorst(Mem, list3[i])) {
					list3[i]->endTime = list3[i]->requestTime + list3[i]->exTime;
					list3[i]->alloc = 1;
				}
				else {
					ready.push_back(list3[i]);
				}
			}
		}

		if (list3[n - 1]->alloc == 1) {
			break;
		}

		time++;
	}

	for (int i = 0; i < Mem.size(); i++) {
		if (Mem[i].mPID == n - 1) {
			fout << Mem[i].adress << endl;
			//cout << Mem[i].adress << endl;
		}
	}
	
}