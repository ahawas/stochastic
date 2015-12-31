// montecarlo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <time.h>
#include "Valuation.h"
using namespace std;


int main()
{
	AmericanCall v = AmericanCall();
	clock_t t;

	v.nsim = 100;
	v.num_threads = 100;
	t = clock();
	cout << v.valuate(100, 110, 1, 0.01, 0.03, 0.25) << endl;
	t = clock() - t;
	printf("Async: It took me %f seconds, using %d threads.\n",  ((float)t) / CLOCKS_PER_SEC, v.num_threads);

	/*v.num_threads = 50;
	t = clock();
	cout << v.american_valuation_sim_threaded(100, 110, 1, 0.01, 0.03, 0.25) << endl;
	t = clock() - t;
	printf("Async: It took me %f seconds, using %d threads.\n", ((float)t) / CLOCKS_PER_SEC, v.num_threads);


	t = clock();
	cout<< v.american_valuation_sim(100, 110, 1, 0.01,0.03, 0.25)<<endl;
	t = clock() - t;
	printf("Serial: It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);*/


	char c; cin >> c;

    return 0;
}

