﻿﻿#pragma once
#include "iostream"
#include "task.h"

double k1 = 2.09;
double k2 = 0.09;
double f1 = 1;
double f2 = sin(0.3 * M_PI);
double q1 = 0.3;
double q2 = 0.09;

double nu1 = 0;
double nu2 = 1;

double xi = 0.3;

class TestTask : public Task
{
public:
	TestTask(int, int);
	~TestTask() {}

	void calculate();

};

void u(int N)
{
	double* U = new double[N];

	double x;
	for (int i = 0; i < N; i++)
	{
		x = i * 1.0 / N;
		if (x < xi)
			U[i] = 0.7348403689121157 * exp(x * sqrt(2. / 7.)) + -1.7348403689121157 * exp(-x * sqrt(2. / 7.)) + 1.;
		else
			U[i] = -0.6706091081659652 * exp(x * sqrt(0.4)) + -3.6275438934922134 * (exp(-x * sqrt(0.4))) + exp(-0.4) / 0.16;

	}

	for (int i = 0; i < N + 1; i++)
	{
		std::cout << i * 0.1 << ";" << U[i] << std::endl;
		//std::cout << "V[" << i << "]= " << V[i] << std::endl;
	}


}