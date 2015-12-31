#include "stdafx.h"
#include "math.h"
#include <iostream>
#include <random>
#include <time.h>
#include <thread>
#include <future>
#include <list>
#include <vector>
using namespace std;
class Valuation {
private:
	normal_distribution<double> distribution;
	default_random_engine generator;
	double sim_stock(double s0, double t, double drift, double sigma);
public:
	Valuation();
	int nsim;
	int num_threads = 100;
	double l();
	double european_valuation_sim(double s0, double k, double t, double drift, double sigma);
	double american_valuation_sim(double s0, double k, double t, double band, double drift, double sigma);
	double american_valuation_sim_threaded(double s0, double k, double t, double band, double drift, double sigma);
	double per_thread(double s0, double k, double t, double band, double drift, double sigma, int n);


};
class AmericanCall : public Valuation{
public:
	double valuate(double s0, double k, double t, double band, double drift, double sigma);
};