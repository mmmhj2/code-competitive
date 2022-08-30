#include <iostream>
#include <queue>
#include <cmath>
#include <utility>
#include <algorithm>

using namespace std;

struct _pos{
	int set;
	int x,y;
	bool operable;
	_pos(){
		operable = false;
	}
}computer[1005];
int N,d;

double calcDisSq(_pos A, _pos B);
int findParent(int x);
int setUnion(int X, int Y);
int repair(int x);
int query(int x, int y);
void printCurrent(void);


int main(){
	cin >> N >> d;
	for(int i = 1; i <= N; i++){
		cin >> computer[i].x >> computer[i].y;
		computer[i].set = i;
	}
	char comm;
	while(cin >> comm){
		switch(comm){
			case 'O':
			{
				int x;cin >> x;
				repair(x);
				break;
			}
			case 'S':
			{
				int x,y;cin >> x >> y;
				int res = query(x,y);
				if(res)
					cout << "SUCCESS" << endl;
				else
					cout << "FAIL" << endl;
				break;
			}
			case 'P':
			{
				printCurrent();
				break;
			}
		}
	}
	return 0;
}

double calcDisSq(_pos A, _pos B){
	//cout << "Dis between is " << (A.x-B.x)*(A.x-B.x)+ (A.y-B.y)*(A.y-B.y) << endl;
	return (A.x-B.x)*(A.x-B.x)+ (A.y-B.y)*(A.y-B.y);
}

int findParent(int x){
	if(computer[x].set == x)	return x;
	return computer[x].set = findParent(computer[x].set);
}

int setUnion(int x, int y){
	int xr(findParent(x)), yr(findParent(y));
	if(xr == yr) return -1;
	computer[yr].set = xr;
	return 0;
}

int repair(int x){
	computer[x].operable = true;
	for(int i = 1; i <= N; i++){
		//for(int j = 1; j <= N; j++)
		//		cout << computer[j].set;
		//cout << endl;
		if((calcDisSq(computer[x], computer[i]) <= d*d ) && computer[i].operable){
			setUnion(x,i);
		}
	}
	return 0;
}

int query(int x, int y){
	return findParent(x) == findParent(y);
}

void printCurrent(void){
	for(int i = 1; i <= N; i++)
		cout << computer[i].set << " " ;
	cout << endl;
}
