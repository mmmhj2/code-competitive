#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

int C,L,ans;

priority_queue <int, vector<int>, greater<int> > QP;
pair <int ,int> cow[2505], lot[2505];

int main(){
	cin >> C >> L;
	for(int i = 1; i <= C; i++)
		cin >> cow[i].first >> cow[i].second;
	sort(cow+1, cow+C+1);
	/*
	for(int i = 1; i <= C; i++)
		cout << cow[i].first << cow[i].second;
	*/
	for(int i = 1; i <= L; i++)
		cin >> lot[i].first >> lot[i].second;
	sort(lot+1, lot+L+1);
	
	int t = 0;
	
	for(int i = 1; i <= L; i++){
		while(t <= C && cow[t].first <= lot[i].first){
			QP.push(cow[t].second);
			t++;
		}while(!QP.empty() && lot[i].second){
			int tCow = QP.top();QP.pop();
			if(tCow >= lot[i].first){
				lot[i].second--;ans++;
			}
		}
	}
	cout << ans;
}
