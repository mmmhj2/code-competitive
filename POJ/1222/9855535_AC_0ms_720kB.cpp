#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;

const int dir[5][2] = {{0,0},{1,0},{0,1},{-1,0},{0,-1}};

int n;
int flip[10][10];
int opt[10][10];
int tile[10][10];

int getAns();
int getClr(int, int);
int Calc();
int printAns(int);

int main(){
	cin >> n;
	for(int cnt = 1; cnt <= n; cnt++){
		for(int i = 1; i <= 5; i++){
			for(int j = 1; j <= 6; j++){
				int t;
				cin >> tile[i][j];
//				tile[i][j] = (t == 1 ? 0 : 1);
			}
			//cin.flush();
		}
		/*for(int i = 1; i <= 5; i++){
			for(int j = 1; j <= 6; j++){
				cout << tile[i][j];
			}
			//cin.flush();
		}8.*/
		cout << "PUZZLE #" << cnt << endl;
		getAns();
	}
}

int getAns(){
	int res = -1;
	for(int i = 0; i < 64; i++){
		memset(flip, 0x00, sizeof(flip));
		for(int j = 1; j <= 6; j++){
			flip[1][7 - j] = ((i) >> (j-1)) & 1;
		}
		int num = Calc();
		if(num >= 0 && (res < 0 || res > num)){
			res = num;
			memcpy(opt, flip, sizeof(flip));
		}
	}
	printAns(res);
	return res;
}

int getClr(int x, int y){
	int c = tile[x][y];
	for(int d = 0; d < 5; d++){
		int x2 = x + dir[d][0];
		int y2 = y + dir[d][1];
		c += flip[x2][y2];
	}
	return c % 2;
}

int Calc(){
	for(int i = 2; i <= 5; i++){
		for(int j = 1; j <= 6; j++){
			if(getClr(i-1, j)){
				flip[i][j] = 1;
			}
		}
	}
	
	for(int j = 1; j <= 6; j++){
		if(getClr(5, j) != 0){
//			cout << "FAILED AT" << j << endl;
			return -1;
		}
	}
	//cout << "PASSED" << endl;
	
	int res = 0;
	for(int i = 1; i <= 5; i++)
		for(int j = 1; j <= 6; j++)
			res += flip[i][j];
	return res;
}

int printAns(int res){
	if(res < 0)
		cout << "IMPOSSIBLE" << endl;
	else{
		for(int i = 1; i <= 5; i++){
			cout << opt[i][1];
			for(int j = 2; j <= 6; j++){
				cout << " " << opt[i][j];
			}
			cout << endl;
		}
	}
	return res;
}
