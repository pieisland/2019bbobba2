#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
#include<queue>
#include<math.h>
using namespace std;

/*
19.07.04.목
잃어버린 괄호. greedy
숫자 만드는 부분에서 당황.
음수는 한 번만 나오면 그 뒤는 다 빼기로 할 수 있다는 걸 알면
문제 자체는 어렵지 않다.
*/

int check;
int ans;

void makenumber(vector<int> n)
{
	int t = n.size();
	int num = 0;
	for (int i = 0; i < t; i++)
	{
		num += n[i] * pow(10, t - 1 - i);
	}

	if (check == 1)
		ans -= num;
	else
		ans += num;
}

int main(){

	string s;
	cin >> s;

	vector<int> number;

	for (int i = 0; i < s.size(); i++)
	{
		//음수 한 번만 나오면 사실 다 음수처리하면 됨.
		if (s[i] == '-')
		{
			makenumber(number);
			number.clear();
			check = 1;
		}
		else if (s[i] == '+')
		{
			makenumber(number);
			number.clear();
		}
		else//숫자
		{
			int num = s[i] - '0';//
			number.push_back(num);
		}
	}

	makenumber(number);

	cout << ans << endl;

	return 0;
}
