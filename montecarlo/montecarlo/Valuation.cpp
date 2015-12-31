#include "Valuation.h"
Valuation::Valuation(void) {
	distribution = normal_distribution<double>(0.0, 1.0);
	generator = default_random_engine(random_device{}());
	nsim = 2000000;
}
double Valuation::sim_stock(double s0, double t, double drift, double sigma)
{
	double z = distribution(generator);
	double st = s0*exp((drift - pow(sigma, 2) / 2)*t + sigma*z*pow(t, 0.5));
	return st;
}

double Valuation::european_valuation_sim(double s0, double k, double t, double drift, double sigma)
{
	double v = 0;
	for (int i = 0; i < nsim; i++)
	{
		double st = sim_stock(s0, t, drift, sigma);
		if (st > k)
		{
			v += st - k;
		}

	}
	return (v / nsim)*exp(-drift*t);
}
double Valuation::l() {
	return 1.0;
}



double AmericanCall::valuate(double s0, double k, double t, double band, double drift, double sigma) {
	double st, payoff;
	double v = 0;
	double max = 0;
	double max_time = 0;
	int sims_per_thread = nsim / num_threads;
	vector<future<double>> all_threads;
	for (int i = 0; i < num_threads; i++)
	{
		//initiate thread
		future<double> ret = async(&AmericanCall::per_thread, this, s0, k, t, band, drift, sigma, sims_per_thread);
		all_threads.push_back(move(ret));
		//future<double> ret = std::async(&l);
	}
	for (int i = 0; i < num_threads; i++) {
		v += move(all_threads[i]).get();
	}

	return v / num_threads;
}

double AmericanCall::per_thread(double s0, double k, double t, double band, double drift, double sigma, int n)
{
	double st, payoff;
	double v = 0;
	double max = 0;
	double max_time = 0;
	for (int i = 0; i < n; i++)
	{
		st = s0;
		for (double j = 0; j < t; j += band)
		{
			st = sim_stock(st, band, drift, sigma);
			if (st > k)
			{
				payoff = st - k;
				if (payoff > max) {
					max = st - k;
					max_time = j + band;
				}
			}
		}
		v += max*exp(-max_time*drift);
		max = 0; max_time = 0;
	}
	return (v / n);
}