#include<bits/stdc++.h>

using namespace std;

int main(){

	clock_t Ticks[2];

	Ticks[0] = clock();

	for(int j=0; j<=100000000; j++){
		
	}

	Ticks[1] = clock();

	double tempo = (Ticks[1] - Ticks[0]) * 1000 / CLOCKS_PER_SEC;

	cout << "Tempo gasto: " << tempo << " ms." << endl;

	return 0;
	
}
