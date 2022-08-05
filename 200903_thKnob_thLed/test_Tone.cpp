#include<bits/stdc++.h>
using namespace std;

void Tone(int val)
{
	float value = (float) (1.0 / val) * 0.5;
	int value_tone = (int) (value* pow(10, 6));
	cout<<value_tone;
}

int main()
{
	Tone(4000);
}
