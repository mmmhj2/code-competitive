#include <iostream>
#include <cstring>

using namespace std;

int sigma[10005], n;
bool used[10005];

int main(){
	while(cin >> n){
		memset(sigma, 0, sizeof(sigma));
		memset(used, 0, sizeof(used));
		for(int i = 1; i <= n; i++){
			cin >> sigma[i];
		}
		for(int i = 1; i <= n; i++){
			if(used[i])
				continue;
			used[i] = true;
			cout << "(" << i;
			int tmp = i;
			while(sigma[tmp] != i){
				cout << " " << sigma[tmp] ;
				used[sigma[tmp]] = true;
				tmp = sigma[tmp];
			}
			cout << ")";
		}
		cout << endl;
	}
	return 0;
}
