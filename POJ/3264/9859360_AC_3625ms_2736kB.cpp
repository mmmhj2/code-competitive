#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<climits>
#include<cstring>
using namespace std;

const int MAXQ = 200000;
const int MAXN = 50000;

int cows[MAXN+5];
int n, q;

struct _node{
	int l, r;
	int min, max;
	
}node[MAXN*4+5];


void construct(int l, int r, int number){
	node[number].l = l;
	node[number].r = r;
	
	if(l == r){
//		printf("INPUT AT %d L %d R %d Number \n", l ,r, number);
		scanf("%d", &node[number].min);
		node[number].max = node[number].min;
		return;
	}
	
	construct(l, (l+r)/2, number*2);
	construct((l+r)/2+1, r, number*2+1);
	
	node[number].min = min(node[number*2].min, node[number*2+1].min);
	node[number].max = max(node[number*2].max, node[number*2+1].max);
}

int getMax(int num, int l, int r){
	
	//printf("Num %d L %d R %d \n", num, l, r);
	
	if(node[num].l >= l && node[num].r <= r){
//		printf("Returned Successful at %d L %d R \n", l ,r);
		return node[num].max;
	}
		
	int mid = (node[num].l + node[num].r) / 2;
	
	if(mid >= r)
		return getMax(num*2, l, r);
	else if(l > mid)
		return getMax(num*2+1,l ,r);
	else
		return max(getMax(num*2, l, mid), getMax(num*2+1, mid+1, r));
}

int getMin(int num, int l, int r){
	if(l <= node[num].l && node[num].r <= r)
		return node[num].min;
		
	int mid = (node[num].l + node[num].r) / 2;
	
	if(mid >= r)
		return getMin(num*2, l, r);
	if(l > mid)
		return getMin(num*2+1,l ,r);
	return min(getMin(num*2, l, mid), getMin(num*2+1, mid+1, r));
}


int main(int argc, char** argv){
	scanf("%d%d", &n, &q);
	construct(1, n, 1);
	while(q--){
		int a, b;
//		cout << "NORMAL" << endl;
		scanf("%d %d", &a, &b);
		printf("%d\n", getMax(1, a, b) - getMin(1, a, b));
	}
	return 0;
}
