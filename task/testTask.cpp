#include "testTask.h"

using namespace std;

double a(double h,double* x, int i)
{
	
	if (x[i] <= xi) return k1;
	else if (x[i - 1] >= xi) return k2;
	else
	{
		return  h * 1. / (((xi - x[i]+h) / k1) + ((x[i] - xi) / k2));
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
		return (1 / h) * (f1 * (xi - x[i]+h/2) + f2* (x[i]+h/2 - xi));
	}
}

//TestTask::TestTask(int nodes,int N) : Task(nodes)
int main()
{
	int N = 10;

	double h = 1. / N;

	double* x = new double[N + 1];
	for (int i = 0; i <= N; i++)
	{
		x[i] = i * h;
	}

	double* A = new double[N + 1];
	double* B = new double[N + 1];
	double* C = new double[N + 1];


	for (int i = 1; i < N; i++)
	{
		A[i] = a(h, x, i) / h / h;
		C[i] = (a(h, x, i) + a(h, x, i + 1)) / h / h + d(h, x, i);
		B[i] = a(h, x, i + 1) / h / h;
		cout << "A[" << i << "]=" << A[i] << endl;
		cout << "C[" << i << "]=" << -C[i] << endl;
		cout << "B[" << i << "]=" << B[i] << endl;
		cout << "------------------------" << endl;
	}



	double* U = new double[N + 1];
	double* V = new double[N + 1];
	V[0] = 0; V[N] = 1;

	double* al = new double[N + 1];
	double* be = new double[N + 1];

	al[0] = 0;
	be[0] = nu1;
	std::cout << "al[1]= 0"<< std::endl;
	std::cout << "be[1]= 0" << std::endl;
	std::cout << "ans[1]= 0" << std::endl << "-----------------------" << std::endl;
	for (int i = 0; i < N-1; i++)
	{
		al[i + 1] = (B[i+1])/(C[i + 1]-A[i + 1]*al[i]);
		be[i + 1] = (fi(h, x, i) + A[i + 1] * be[i]) / (C[i + 1] - al[i] * A[i + 1]);



		std::cout << "al[" << i + 1 << "]= " << al[i + 1] << std::endl;
		std::cout << "be[" << i + 1 << "]= " << be[i + 1] << std::endl;
		std::cout << "ans[" << i+1  << "]= " << -fi(h, x, i+1) << std::endl<< "-----------------------" << std::endl;
	}
	std::cout << "al[N]= 0" << std::endl;
	std::cout << "be[N]= 0" << std::endl;
	std::cout << "ans[N]= 1" << std::endl << "-----------------------" << std::endl;

	V[N] =nu2;
	for (int i = N-1; i >0 ; i--)
	{
		V[i] = al[i] * V[i + 1] + be[i];
	}

	for (int i = 0; i < N + 1; i++)
	{
		std::cout <<i*0.1<< ";" << V[i] << std::endl;
		//std::cout << "V[" << i << "]= " << V[i] << std::endl;
	}

	u(N);

}
