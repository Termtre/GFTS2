#include "testTask.h"
#define _USE_MATH_DEFINES
#include <math.h>

TestTask::TestTask(int nodes) : Task(nodes)
{
private:
	matrix = std::vector<std::vector<double>> pole(nodes, std::vector<double>(nodes));
	double h = 1/nodes;
	double x* = new double[nodes + 1];
	double A* = new double[nodes + 1];
	double B* = new double[nodes + 1];
	double C* = new double[nodes + 1];
	double* U = new double[nodes + 1];
	double* V = new double[nodes + 1];
	V[0] = 0; V[nodes] = 1;
	double Alph = new double[nodes + 1];
	double Bet = new double[nodes + 1];
	Alph[0] = 0; Bet[0] = nu1;



	double a(double h, double* x, int i)
	{

		if (x[i] <= xi) return k1;
		else if (x[i - 1] >= xi) return k2;
		else
		{
			return  h * 1. / (((xi - x[i] + h) / k1) + ((x[i] - xi) / k2));
		}
	}

	double d(double h, double* x, int i)
	{
		if (x[i] + h / 2 <= xi) return q1;
		else if (x[i] - h / 2 >= xi) return q2;
		else return (1 / h) * ((q1 * (xi - x[i] + h / 2)) + (q2 * (x[i] + h / 2 - xi)));
	}

	double fi(double h, double* x, int i)
	{
		if (x[i] + h / 2 <= xi) return f1;
		else if (x[i] - h / 2 >= xi) return f2;
		else
		{
			return (1 / h) * (f1 * (xi - x[i] + h / 2) + f2 * (x[i] + h / 2 - xi));
		}
	}


public:
	void find_ABC()
	{
		for (int i = 1; i < nodes; i++)
		{
			A[i] = a(h, x, i) / (h * h);
			B[i] = (a(h, x, i) + a(h, x, i + 1)) / (h * h) + d(h, x, i);
			C[i] = a(h, x, i+1) / (h * h);
		}
	}
	void print_ABC()
	{
		std::cout << "A" << "\t" << "B" << "\t" << "C" << endl;
		for (int i = 0; i < N + 1; i++)
		{
			std::cout << A[i] << "\t" << B[i] << "\t" << C[i] << endl;
		}
	}
	void find_Alph_Bet()
	{
		for (int i = 1; i < nodes; i++)
		{
			al[i] = (B[i]) / (C[i] - A[i] * al[i-1]);
			be[i] = (fi(h, x, i-1) + A[i] * be[i-1]) / (C[i] - al[i-1] * A[i]);

		}
	}
	void find_Vi()
	{
		for (int i = N - 1; i > 0; i--)
		{
			V[i] = al[i] * V[i + 1] + be[i];
		}
	}
	void print_V_vec()
	{
		std::cout << "x" << "\t" << "V" << endl;
		for (int i = 0; i < N + 1; i++)
		{
			std::cout << i * 0.1 << "\t" << V[i] << std::endl;
			//std::cout << "V[" << i << "]= " << V[i] << std::endl;
		}
	}
	void main_func()
	{
		find_ABC();
		find_Alph_Bet();
		find_Vi();
		print_V_vec();
	}

}
