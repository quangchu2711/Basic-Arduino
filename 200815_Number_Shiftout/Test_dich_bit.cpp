#include<bits/stdc++.h>
using namespace std;

int main()
{
	int val = 7;
	for(int i =0; i <= 7; i++)
	{
		cout<<!((val & 128) != 0);
		val = val << 1;
	}
	int val1 = 7;
	cout<<endl;
	for(int i =0; i <= 7; i++)
	{
		cout<<!!(val1 & (1 <<(7 - i)));
	}
	cout<<endl;
	int val2 = 7;
	for(int i =0; i <= 7; i++)
	{
		cout<<!!(val2 & 1);
		val2 = val2 >> 1;
	}
}
