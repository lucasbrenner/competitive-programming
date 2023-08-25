#include "../contest/template.cpp"
#include "fft.cpp"

//res[i] = somatorio a[j] * b[(i - j + n) % n]
//Nlog

void circularConv(vector<double> &a, vector<double> &b, vector<double> &res) {
	//assert(a.size() == b.size());
	int n = a.size();
	res = conv(a, b);
	for(int i = n; i < (int)res.size(); i++) res[i%n] = (res[i%n]+res[i]);
	res.resize(n);
}

