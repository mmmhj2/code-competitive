#include<cstdio>
#include<iostream>
#include<cstring>

#define UP 0x01
#define DOWN 0x02
#define LEFT 0x04
#define RIGHT 0x08

using namespace std;

char maze[40][40];
int ans,stx,sty,glx,gly;
int W,H;

int checkthrow(int x, int y){
	int ret = 0;
	if(x-1 >= 0)
		if(maze[x-1][y] != '1')
			ret+=UP;
	if(x+1 <= H)
		if(maze[x+1][y] != '1')
			ret+=DOWN;
	if(y-1 >= 0)
		if(maze[x][y-1] != '1')
			ret+=LEFT;
	if(y+1 <= W)
		if(maze[x][y+1] != '1')
			ret+=RIGHT;
	return ret;
}

void DFS(int x,int y,int _ans){
	_ans++;
	if(_ans > 10 || _ans > ans)
		return;
	int dir = checkthrow(x,y);

	if(dir & UP){
		for(int i = x; i > 0; i--){
			if(maze[i][y] == '1'){
				maze[i][y] = '0';
				DFS(i+1,y,_ans);
				maze[i][y] = '1';
				break;
			}else if(maze[i][y] == '3'){
				ans = min(ans,_ans);
				return;
			}
		}
	}if(dir & DOWN){
		for(int i = x; i <= H; i++){
			if(maze[i][y] == '1'){
				maze[i][y] = '0';
				DFS(i-1,y,_ans);
				maze[i][y] = '1';
				break;
			}else if(maze[i][y] == '3'){
				ans = min(ans,_ans);
				return;
			}
		}
	}if(dir & LEFT){
		for(int i = y; i > 0; i--){
			if(maze[x][i] == '1'){
				maze[x][i] = '0';
				DFS(x,i+1,_ans);
				maze[x][i] = '1';
				break;
			}else if(maze[x][i] == '3'){
				ans = min(ans,_ans);
				return;
			}
		}
	}if(dir & RIGHT){
		for(int i = y; i <= W; i++){
			if(maze[x][i] == '1'){
				maze[x][i] = '0';
				DFS(x,i-1,_ans);
				maze[x][i] = '1';
				break;
			}else if(maze[x][i] == '3'){

				ans = min(ans,_ans);
				return;
			}
		}
	}
	return;
}

int main(){
	while(true){
		cin >> W >> H;
		if(W == 0 || H == 0)
			return 0;
		memset(maze, 0, sizeof(maze));
		ans = 100000;
		stx = 0, sty = 0, glx = 0, gly = 0;

		for(int i = 1; i <= H; i++){
			for(int j = 1; j <= W; j++){
				cin >> maze[i][j];
				if(maze[i][j] == '2')
					stx = i, sty = j;
				if(maze[i][j] == '3')
					glx = i, gly = j;
			}
		}

		DFS(stx,sty,0);

		cout << (ans==100000 ? -1 : ans) << endl;
	}
	return 0;
}
