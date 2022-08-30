#include <algorithm>
#include <cstdio>
 
#define REDIRECT(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define CLOSEALL() fclose(stdin), fclose(stdout)
 
using namespace std;
 
const int MAXN = 3e5 + 10;
 
int N;
pair <int, int> a[MAXN];
 
int main()
{
	//REDIRECT("sort");
 
	int cnt = 0;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++)
		scanf("%d", &a[i].first), a[i].second = i;
	sort(&a[1], &a[N + 1]);
 
	for(int i = 1; i <= N; i++)
		if((a[i].second % 2) != (i % 2))
			cnt++;
 
	printf("%d\n", cnt / 2);
 
	CLOSEALL();
 
	return 0;
}