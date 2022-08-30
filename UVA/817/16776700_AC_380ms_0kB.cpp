#include <bits/stdc++.h>
using namespace std;

const char operators[3] = { '+', '-', '*' };
string str;
namespace getStringVal
{
	bool cmpPriority(char x, char y)
	{
		if ((x == '+' || x == '-') && y == '*')
			return false;
		return true;
	}

	int getSimpleVal(int op1, int op2, char op)
	{
		switch (op)
		{
		case '+':
			return op1 + op2;
		case '-':
			return op1 - op2;
		default:
			return op1 * op2;
		}
	}

	int getStringVal(const string & s)
	{
		stack<char> op;
		stack<int> num;
		int len = s.length();
		//cerr << s << endl ;
		for (int i = 0; i < len; i++)
		{
			int res = 0, pos = i;
			while (pos < len && (s[pos] >= '0' && s[pos] <= '9'))
				res = res * 10 + s[pos++] - '0';
			//cerr << "Checking string from " << i << " to " << pos << " is " << res << endl ;
			if (pos - i > 1 && s[i] == '0')		// has leading zeros
				return 0xC0000000;

			num.push(res);

			if (pos < len)
			{
				if (op.empty())
					op.push(s[pos]);
				else
				{
					while (!op.empty() && cmpPriority(op.top(), s[pos]))
					{
						int op1, op2, opt;
						op2 = num.top(), num.pop();
						op1 = num.top(), num.pop();
						opt = op.top(), op.pop();
						num.push(getSimpleVal(op1, op2, opt));
					}
					op.push(s[pos]);
				}
			}
			i = pos;
		}

		while (!op.empty())
		{
			int op1, op2, opt;
			op2 = num.top(), num.pop();
			op1 = num.top(), num.pop();
			opt = op.top(), op.pop();
			num.push(getSimpleVal(op1, op2, opt));
		}
		return num.top();
	}
}

int maxDeep;
set<string> ans;

void IDDFS(int dep, int pos, string str)
{
	if (dep >= maxDeep)
	{
		//cerr << "Evaluating string " << str << " to be " << getStringVal::getStringVal(str) << endl ;
		if (getStringVal::getStringVal(str) == 2000)
		{

			ans.insert(str);
		}
		return;
	}

	int len = str.length();
	if (len - pos - 1 < maxDeep - dep)
		return;
	for (int i = pos + 1; i < len; i++)
		for (int op = 0; op < 3; op++)
		{
			string nxt = str;
			nxt.insert(i, 1, operators[op]);
			IDDFS(dep + 1, i + 1, nxt);
		}
}

int main()
{
	int _case = 0;
	string str;

	while (cin >> str && str.front() != '=')
	{
		ans.clear();
		str.pop_back();			// C++11
		for(maxDeep = 1; maxDeep < (int)str.length(); maxDeep++)
			IDDFS(0, 0, str);
		cout << "Problem " << ++_case << endl ;
		if(ans.empty())
			cout << "  IMPOSSIBLE" << endl ;
		else
			for(set<string>::iterator itr = ans.begin(); itr != ans.end(); ++itr)
				cout << "  " << *itr << '=' << endl ;
	}
	return 0;
}
