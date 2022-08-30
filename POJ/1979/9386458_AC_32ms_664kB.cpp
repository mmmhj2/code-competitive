#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

char maze[40][40];
int ans,stx,sty;
int W,H;

void DFS(int x,int y){
	maze[x][y] = '*';
	if(maze[x+1][y] == '.' && x+1 <= H){
		DFS(x+1,y);
	}if(maze[x-1][y] == '.'){
		DFS(x-1,y);
	}if(maze[x][y+1] == '.' && y+1 <= W){
		DFS(x,y+1);
	}if(maze[x][y-1] == '.'){
		DFS(x,y-1);
	}
}

int main(){
	while(scanf("%d %d",&W,&H)){
		if(W == 0 && H == 0)
			return 0;
		memset(maze, 0, sizeof(maze));
		int ans = 0;
		stx = 0; sty = 0;
		
		for(int i = 1; i <= H; i++){
			cin >> &maze[i][1];
			for(int j = 1; j <= W; j++){
				if(maze[i][j] == '@')
					stx = i, sty = j;
			}
		}
		
		//printf("%d %d", stx,sty);
		DFS(stx,sty);
		
		for(int i = 1; i <= H; i++){
			//cout << endl;
			for(int j = 1; j <= W+1; j++){
				//cout << maze[i][j];
				if(maze[i][j] == '*')
					ans++;
			}
		}
		
		printf("%d\n", ans);
	}
	return 0;
}