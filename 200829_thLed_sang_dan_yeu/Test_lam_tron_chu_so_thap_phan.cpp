#include<bits/stdc++.h>
using namespace std;

void analogWrite(int led, int val)
{
	float value = (float) (val / 256.0);
	cout<<value<<endl;
	value = round(value * 100.0) / 100.0;
	cout<<value<<endl;
	int T_HIGH = (int)(value * 1000);
	int T_LOW = 1000 - T_HIGH;
	cout<<T_HIGH<<endl<<T_LOW;
}

int main()
{
//	float val = 37.5111111;
//	float x = floor(val * 100) / 100;
//	float y = round(val * 100) / 100;
//	float z = ceilf(val * 100) / 100;
//	cout<<x<<endl;
//	cout<<y<<endl;
//	cout<<z<<endl;
	analogWrite(5, 255);
}
