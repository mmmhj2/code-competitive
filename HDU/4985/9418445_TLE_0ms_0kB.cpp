#include <cstdio>
#include <cstring>

using namespace std;

int sigma[10005], n;
bool used[10005];

int main(){
	while(scanf("%d" ,&n) == 1){
		memset(sigma, 0, sizeof(sigma));
		memset(used, 0, sizeof(used));
		for(int i = 1; i <= n; i++){
			scanf("%d" ,&sigma[i]);
		}
		for(int i = 1; i <= n; i++){
			if(used[i])
				continue;
			used[i] = true;
			printf("(%d", i);
			int tmp = i;
			while(sigma[tmp] != i){
				printf(" %d", sigma[tmp]);
				used[sigma[tmp]] = true;
				tmp = sigma[tmp];
			}
			printf(")");
		}
		printf("\n");
	}
	return 0;
}
