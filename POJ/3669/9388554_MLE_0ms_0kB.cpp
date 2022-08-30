#include<queue>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iostream>
///////////////////////////////////////////////////
using namespace std;
typedef short st;
///////////////////////////////////////////////////
struct MAP{
	bool map[302][302];
	st elapsed,stx,sty;
	MAP(){
		memset(map,0,sizeof(map)); 
		elapsed = 0,stx = 0 ,sty = 0;
	}
}hitpos;

struct Meteor{
	st x,y,EstimatedArrival;
	Meteor(){
		x = 0, y = 0, EstimatedArrival = 0;
	}
}EstimatedMeteor[50005];
///////////////////////////////////////////////////
int M,leastCompact = 1,ans = 1000000000;
///////////////////////////////////////////////////
int output(MAP _map){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			cout << _map.map[i][j];
		}
		cout << endl;
	}
	cout << "POS:" << _map.stx << " " << _map.sty << endl;
	return 0;
}
///////////////////////////////////////////////////
int _comp(const void *a, const void *b){
	return (*(Meteor*)a).EstimatedArrival - (*(Meteor*)b).EstimatedArrival;
}

bool Check(int x,int y,MAP _map){
	if(x < 0 || x > 300) return false;
	if(y < 0 || y > 300) return false;
	if(_map.map[x][y] == 1) return false;
	return true;
}

int MeteorStrike(st x, st y, MAP &_map){
	if(x == 0 && y == 0){
		_map.map[0][0] = 1, _map.map[1][0] = 1, _map.map[0][1] = 1;
	}else if(x == 0){
		_map.map[x][y] = 1, _map.map[x][y-1] = 1, _map.map[x][y+1] = 1, _map.map[x+1][y] = 1;
	}else if(y == 0){
		_map.map[x][y] = 1, _map.map[x-1][y] = 1, _map.map[x+1][y] = 1, _map.map[x][y+1] = 1;
	}else{
		_map.map[x][y] = 1, _map.map[x-1][y] = 1, _map.map[x+1][y] = 1, \
		_map.map[x][y-1] = 1, _map.map[x][y+1] = 1;
	}
	return 0;
}

int Update(MAP &_map){
	for(int i = 1; i <= M; i++){
		if(_map.elapsed >= EstimatedMeteor[i].EstimatedArrival)
			MeteorStrike(EstimatedMeteor[i].x, EstimatedMeteor[i].y, _map);
		if(_map.elapsed < EstimatedMeteor[i].EstimatedArrival){
			leastCompact = i+1;
			break;
		}
	}
	return 0;
}

int BFS(){
	queue <MAP> q;
	MAP tmp;
	q.push(tmp);
	while(!q.empty()){
		tmp = q.front();
		//printf("%d %d %d \n RECENT: \n",tmp.elapsed,tmp.stx,tmp.sty);
		//output(tmp);
		q.pop();
		
		tmp.elapsed++;
		//cout << tmp.elapsed;
		if(hitpos.map[tmp.stx][tmp.sty] == 0){
			//cout << "GOAL" << endl;
			ans = tmp.elapsed-1;
			return 0;
		}

		//cout << "UPDATED" <<endl;
		Update(tmp);
		//output(tmp);
		MAP t = tmp;
		if(Check(t.stx+1, t.sty, tmp)){
			//cout << "PROCEED" << endl;
			t.stx++,t.map[t.stx][t.sty] = true;
			q.push(t);
			t = tmp;
		}if(Check(t.stx-1, t.sty, tmp)){
			//cout << "PROCEED" << endl;
			t.stx--,t.map[t.stx][t.sty] = true;
			q.push(t);
			t = tmp;
		}if(Check(t.stx, t.sty+1, tmp)){
			//cout << "PROCEED" << endl;
			t.sty++,t.map[t.stx][t.sty] = true;
			q.push(t);
			t = tmp;
		}if(Check(t.stx, t.sty-1, tmp)){
			//cout << "PROCEED" << endl;
			t.sty--,t.map[t.stx][t.sty] = true;
			q.push(t);
			t = tmp;
		}
	}
	return -1;
}

int main(){
	cin >> M;
	for(int i = 1; i <= M; i++){
		cin >> EstimatedMeteor[i].x >> EstimatedMeteor[i].y >> EstimatedMeteor[i].EstimatedArrival;
		//cout << "\\ACCEPTED DATA" << endl;
		MeteorStrike(EstimatedMeteor[i].x, EstimatedMeteor[i].y, hitpos);
	}
	qsort(&EstimatedMeteor[1], M, sizeof(Meteor), _comp);
	//output(hitpos);
	BFS();
	cout << ((ans == 1000000000) ? -1 : ans);
}

