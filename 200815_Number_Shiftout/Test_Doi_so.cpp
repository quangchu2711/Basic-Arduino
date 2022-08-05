#include<bits/stdc++.h>
using namespace std;

int Dem(int val)
{
	int dem = 0;
	while(val > 0)
	{
		val % 10;
		dem++;
		val = val / 10;
	}
	return dem;
}

int main()
{
//	int Array[4];
//	int val = 1234;
//	int a = 1000;
//	int dem = 3;
//	while(dem >= 0)
//	{
//		Array[dem] = val % 10;
//		val = val / 10; 
//		dem--;
//	}
//	for(int i = 0; i <= 3; i++) cout<<Array[i]<<" ";
	cout<<Dem(134);
}
