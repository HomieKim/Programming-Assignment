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


// ����, ��ȯ, ť �˻�

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
	// ps�� pid�� �޸𸮺��Ϳ� ���° �ε����� �ִ��� Ȯ��
	// �� �ε����� 0�϶� �ƴҶ� 2���� ���� ����, �ƴ� ���� ��� �߰� ���̹Ƿ� ���ʿ����� ���������
	int memidx = 0;
	for (int i = 0; i < Mem.size(); i++) {
		if (ps->PID == Mem[i].mPID) {
			memidx = i;
			break;
		}
	}

	if (memidx == 0) {
		// �ε����� 0 �̸� �����ʿ� �ִ°� -1 ���� �ƴ��� Ȯ��
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
		// �ε����� �߰��� �� ��� -> ���ʸ� -1, �����ʸ� -1, �Ѵ� -1, �Ѵ� ���
		if (Mem[memidx - 1].mPID == -1 && Mem[memidx + 1].mPID >= 0) {	// ���ʸ� -1
			Mem[memidx].adress = Mem[memidx - 1].adress;
			Mem[memidx].mPID = -1;
			Mem[memidx].mSize += Mem[memidx - 1].mSize;
			Mem.erase(Mem.begin() + (memidx - 1));
		}
		else if (Mem[memidx - 1].mPID >= 0 && Mem[memidx + 1].mPID == -1) { // �����ʸ� -1
			Mem[memidx].mPID = -1;
			Mem[memidx].mSize += Mem[memidx + 1].mSize;
			Mem.erase(Mem.begin() + (memidx + 1));
		}
		else if (Mem[memidx - 1].mPID == -1 && Mem[memidx + 1].mPID == -1) { //���� �� -1
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


	// ������ �Է� �ޱ�

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
	// ���

	memory initmem = { 0, -1, 1000 };
	//list ����, memory�Ҵ�
	Mem.push_back(initmem);

	int time = 0;
	while (true) {
		int chk = 0;
		for (int i = 0; i < n; i++) {
			if (list[i]->endTime == time && list[i]->endTime != 0) { // time�� ����ð��� ������ ��ȯ�ؾ���
				// ��ȯ�ϸ� �޸� ���� ����  -1 ���ӵǴ� �������� ���� �ְ� �ٽ� �Ҵ� �Ǵ��� ������
				// ���μ����� ���ÿ� ��ȯ �� ���� �����ϱ� ��ȯ �� �� �Ŀ�  chk��
				returnMemory(list[i]);

				chk++;
			}
		}
		if (chk > 0) {	// ��ȯ�� �־��� ��� queüũ
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
			if (list[i]->requestTime == time) { // ��û�ð��� time�� ������
				// firstfit ���� �޸𸮿� ���� ������ �� ũ�⺸�� ������ ������ ���ť�� ��
				// ���ť�� �ִ� �ð����� endtime�� ��������� = ���ť���� ��û�� ������ time�� �����ָ� �� ��
				if (chkFirst(Mem, list[i])) {	// ���� �˻翡�� firstfit���� �Ҵ� ���� �Ҵ��Ұ� ������ ���ť�� ��
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
		if (chk > 0) {	// ��ȯ�� �־��� ��� queüũ
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
		if (chk > 0) {	// ��ȯ�� �־��� ��� queüũ
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