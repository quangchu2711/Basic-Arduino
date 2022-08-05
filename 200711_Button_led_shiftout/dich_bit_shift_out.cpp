#include<bits/stdc++.h>
using namespace std;

int main()
{
	int val = 2;
	for(int i = 0; i < 8; i++)
	{
		cout<<(val & 128);
		val = val << 1;
	}
}
