#include <cstdio>
#include <cstring>

int sigma[100005], n;
bool used[100005];

int main(){
	while(scanf("%d" ,&n) != EOF){
		memset(used, 0, sizeof(used));
		for(int i = 1; i <= n; i++){
			scanf("%d" ,&sigma[i]);
		}
		for(int i = 1; i <= n; i++){
			if(!used[i]){
				used[i] = true;
				printf("(%d", i);
				int tmp = sigma[i];
				while(!used[tmp]){
					printf(" %d", tmp);
					used[tmp] = true;	
					tmp = sigma[tmp];
				}
				printf(")");
			}
		}
		printf("\n");
	}
	return 0;
}
