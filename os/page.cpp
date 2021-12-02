#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Memory
{
	int frame;
	int PID;
	int page;
	int alloc = 0; // 할당 되면 1로 바꿈
	int count;
	int opt;

}typedef mem;

struct Reference
{
	int PID;
	int page;
	
}typedef ref_;

int lru;

bool isFault(ref_ refer, mem** list) {
	int i = 0;
	while(true) {
		if (list[i]->alloc == 0) {
			break;
		}
		if (list[i]->PID == refer.PID && list[i]->page == refer.page) {
			lru = i;
			return false;
		}
		i++;
	}
	return true;
}
int selFIFO(int n, int i, ref_ refer, mem** list) {
	int j = 0;
	int chk = 1000001;
	int sel;
	// 먼저 들어온것 일수록 count값 작다 => count값이 젤 작은거 프레임번호를  리턴
	while (true) {
		if (list[j]->alloc == 0) {
			break;
		}
		if (list[j]->PID == refer.PID) {
			if (chk > list[j]->count) {
				chk = list[j]->count;
				sel = list[j]->frame;
			}
		}
		j++;
	}
	return sel;
}
int selLRU(int n, int i, ref_ refer, mem** list) {
	int j = 0;
	int chk = 1000001;
	int sel;
	// 먼저 들어온것 일수록 count값 작다 => count값이 젤 작은거 프레임번호를  리턴
	while (true) {
		if (list[j]->alloc == 0) {
			break;
		}
		if (list[j]->PID == refer.PID) {
			if (chk > list[j]->count) {
				chk = list[j]->count;
				sel = list[j]->frame;
			}
		}
		j++;
	}
	return sel;
}
void searchFIFO(int n, int i,int count,ref_ refer, mem** list) {
	int cnt = 0;
	int j = 0;
	while (true) {
		if (list[j]->alloc == 0) {
			break;
		}
		if (list[j]->PID == refer.PID) {
			cnt++;
		}
		j++;
	}

	if (cnt < n) {
		//빈자리에 할당
		list[j]->frame = j;
		list[j]->PID = refer.PID;
		list[j]->page = refer.page;
		list[j]->alloc = 1;
		list[j]->count = count;
	}
	else {
		// 교체해야함
		int sel = selFIFO(n,i,refer,list);
		list[sel]->page = refer.page;
		list[sel]->count = count;
	}
}

void searchLRU(int n, int i, int count, ref_ refer, mem** list) {
	int cnt = 0;
	int j = 0;
	while (true) {
		if (list[j]->alloc == 0) {
			break;
		}
		if (list[j]->PID == refer.PID) {
			cnt++;
		}
		j++;
	}

	if (cnt < n) {
		//빈자리에 할당
		list[j]->frame = j;
		list[j]->PID = refer.PID;
		list[j]->page = refer.page;
		list[j]->alloc = 1;
		list[j]->count = count;
	}
	else {
		// 교체해야함
		int sel = selLRU(n, i, refer, list);
		list[sel]->page = refer.page;
		list[sel]->count = count;
	}
}
int setOpt(int i, vector<ref_> referList, mem* list) {
	for (int j = i+1; j < referList.size(); j++) {
		if (referList[j].page == list->page && referList[j].PID == list->PID) {
			return j;
		}
	}
	return 100000;
}
int selOPT(int n, int i, ref_ refer, mem** list, vector<ref_> referList) {
	int sel = 0;
	int j = 0;
	//cout << "*** " << i << " ***" << endl;
	while (true) {
		if (list[j]->alloc == 0) {
			break;
		}
		list[j]->opt = setOpt(i,referList,list[j]);
		//cout << "list"<< list[j]->frame <<" : "<<list[j]->opt << endl;
		//cout << list[j]->frame << " : "<<list[j]->PID << " , " << list[j]->page << endl;
		j++;
	}
	int tmp = -1;
	int chk = 1000001;
	int k = 0;
	while (true) {
		if (list[k]->alloc == 0) {
			break;
		}
		
		if (list[k]->PID == refer.PID) {
			
			if (tmp == list[k]->opt) {
				if (chk > list[k]->count) {
					sel = list[k]->frame;
					tmp = list[k]->opt;
					chk = list[k]->count;
				}
			}
			else if (tmp < list[k]->opt) {
				sel = list[k]->frame;
				tmp = list[k]->opt;
				chk = list[k]->count;
			}
		}
		
		k++;
	}
	
	return sel;
}
void searchOPT(int n, int i, int count, ref_ refer, mem** list, vector<ref_> referList) {
	int cnt = 0;
	int j = 0;
	while (true) {
		if (list[j]->alloc == 0) {
			break;
		}
		if (list[j]->PID == refer.PID) {
			cnt++;
		}
		j++;
	}

	if (cnt < n) {
		//빈자리에 할당
		list[j]->frame = j;
		list[j]->PID = refer.PID;
		list[j]->page = refer.page;
		list[j]->alloc = 1;
		list[j]->count = count;
	}
	else {
		// 교체해야함
		int sel = selOPT(n, i, refer, list, referList);
		list[sel]->page = refer.page;
		list[sel]->count = count;
	}
}
int main(){

	ifstream fin("page.inp");
	ofstream fout("page.out");
	int n;
	fin >> n;
	int process;
	int pageNum;
	vector<ref_> refList;
	while (true) {
		fin >> process;
		fin >> pageNum;

		if (process == -1) {
			break;
		}
		else {
			ref_ tmp;
			tmp.PID = process;
			tmp.page = pageNum;
			refList.push_back(tmp);
		}
	}
	mem** list = (mem**)malloc(sizeof(mem*) * 10001);
	mem** list2 = (mem**)malloc(sizeof(mem*) * 10001);
	mem** list3 = (mem**)malloc(sizeof(mem*) * 10001);
	
	int faultCnt = 0;
	// 돌려보고 안되면 mem 크기 더 키워야햠 ps갯수 최대 100 프레임 갯수 최대 100 임
	for (int i = 0; i < 10001; i++) {
		list[i] = new mem();
		list2[i] = new mem();
		list3[i] = new mem();
	}
	
	
	//FIFO 제일 먼저들어온거 어떠케 찾지..?
	int cnt = 1;
	for (int i = 0; i < refList.size(); i++) {
		if (i == 0) {
			list[i]->frame = i;
			list[i]->PID = refList[i].PID;
			list[i]->page = refList[i].page;
			list[i]->alloc = 1;
			list[i]->count = cnt;
			faultCnt++;
			cnt++;
		}
		else if (isFault(refList[i] , list)) {
			searchFIFO(n,i,cnt,refList[i],list);
			faultCnt++;
			cnt++;
		}
		
	}

	int k = 0;
	//cout << "FIFO : " << faultCnt << endl;
	fout << "FIFO: " << faultCnt << endl;
	while (true) {
		if (list[k]->alloc == 0) {
			break;
		}
		//cout << "<" << list[k]->frame << ", " << list[k]->PID << ", " << list[k]->page << ">" << endl;
		fout << list[k]->frame << " " << list[k]->PID <<" "<< list[k]->page << endl;
		k++;
	}

	// fifo 끝

	faultCnt = 0;
	cnt = 1;

	for (int i = 0; i < refList.size(); i++) {
		if (i == 0) {
			list2[i]->frame = i;
			list2[i]->PID = refList[i].PID;
			list2[i]->page = refList[i].page;
			list2[i]->alloc = 1;
			list2[i]->count = cnt;
			faultCnt++;
			cnt++;
		}
		else {
			if (isFault(refList[i], list2)) {
				searchLRU(n, i, cnt, refList[i], list2);
				faultCnt++;
				cnt++;
			}
			else {
				list2[lru]->count = cnt;
				cnt++;
			}
		}

		
	}

	k = 0;
	//cout << "LRU : " << faultCnt << endl;
	fout << "LRU: " << faultCnt << endl;
	while (true) {
		if (list2[k]->alloc == 0) {
			break;
		}
		//cout << "<" << list2[k]->frame << ", " << list2[k]->PID << ", " << list2[k]->page << ">" << endl;
		fout << list2[k]->frame << " " << list2[k]->PID << " "<<list2[k]->page << endl;
		k++;
	}
	// LRU끝

	faultCnt = 0;
	cnt = 1;

	for (int i = 0; i < refList.size(); i++) {
		if (i == 0) {
			list3[i]->frame = i;
			list3[i]->PID = refList[i].PID;
			list3[i]->page = refList[i].page;
			list3[i]->alloc = 1;
			list3[i]->count = cnt;
			faultCnt++;
			cnt++;
		}
		else if (isFault(refList[i], list3)) {
			searchOPT(n, i, cnt, refList[i], list3, refList);
			faultCnt++;
			cnt++;
		}
		
	}

	k = 0;
	//cout << "OPT : " << faultCnt << endl;
	fout << "OPT: " << faultCnt << endl;
	while (true) {
		if (list3[k]->alloc == 0) {
			break;
		}
		//cout << "<" << list3[k]->frame << ", " << list3[k]->PID << ", " << list3[k]->page << ">" << endl;
		fout << list3[k]->frame << " " << list3[k]->PID << " "<<list3[k]->page << endl;
		k++;
	}

	fin.close();
	fout.close();

}