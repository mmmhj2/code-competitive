#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int MAX_INT = 0x7fffffff;
const int MAXBOWL = 20;

int dir[MAXBOWL+1];
int fip[MAXBOWL+1];

int solve(int);

int main(int argc, char **argv){
	for(int i = 1; i <= MAXBOWL; i++)
		cin >> dir[i];
	cout << min(solve(0), solve(1)) << endl;
}

int solve(int fir){
	int sum = 0, res = 0;
	dir[1] = fir;
	memset(fip, 0x00, sizeof(fip));
	for(int i = 0; i < 20; i++){
		if((sum + dir[i]) % 2 != 0){
			res++;	fip[i] = 1;
		}
		sum += fip[i];
		if(i - 2 >= 0){
			sum -= fip[i-2];
		}
	}
	if((dir[MAXBOWL] + sum) % 2 != 0)
		return MAX_INT;
	return res;
}
