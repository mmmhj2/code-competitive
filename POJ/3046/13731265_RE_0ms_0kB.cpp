#include <iostream>
using namespace std;

const int MAXN = 1000;
const int MODO = 1000000;

int T, A, S, B;
int N[MAXN + 5];
int DP[2][MAXN + 5];

int main()
{
	cin >> T >> A >> S >> B ;

	int index;
	for(int i = 1 ; i <= A ; i++)
		cin >> index, N[index]++;

	int * oldArray = DP[0];
	int * newArray = DP[1];

	DP[0][0] = DP[1][0] = 1 ;

	for(int i = 1; i <= T; i++)
	{
		for(int j = 1; j <= B; j++)
		{
			if(j - N[i] > 0)        // 决策：选择该家族
				newArray[j] = (oldArray[j] + newArray[j - 1] - oldArray[j - N[i] - 1] + MODO) % MODO;
			else                    // 决策：不选择该家族
				newArray[j] = (oldArray[j] + newArray[j - 1]) % MODO;
		}
		swap(newArray, oldArray);
	}

	int ans = 0;
	for(int i = S; i <= B; i++)
		ans = (ans + oldArray[i]) % MODO ;

	cout << ans << endl ;
	return 0;
}
