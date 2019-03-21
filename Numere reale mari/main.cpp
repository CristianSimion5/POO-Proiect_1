#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

#include "big_real.h"

using namespace std;

int main() {
	ifstream in("big_real.in");
	ofstream out("big_real.out");
	int n;
	in >> n;
	big_real V[1000];
	for (int i = 0; i < n; i++)
		in >> V[i];
	sort(V, V + n);
	for (int i = 0; i < n; i++)
		out << V[i] << "\n";
	cout << V[1] << " + " << V[2] << " = " << V[1] + V[2] << "\n";
	cout << V[3] << " + " << V[4] << " = " << V[3] + V[4] << "\n";
	cout << V[2] << " - " << V[0] << " = " << V[2] - V[0] << "\n";
	cout << V[9] << " / " << V[0] << " = " << V[9] / V[0] << "\n";
	cout << V[7] << " * " << V[8] << " = " << V[7] * V[8] << "\n";
	return 0;
}
