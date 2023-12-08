#include "task.h"

Task::Task(int n) : nodes(n)
{
	V.resize(nodes);
	Phi.resize(nodes);
	matrix.resize(nodes);
	alpha.resize(nodes - 1);
	beta.resize(nodes - 1);

	for (int i = 0; i < nodes; i++)
		matrix[i].resize(nodes);

}

#ifdef testMode
void Task::test(const std::vector<std::vector<double>>& testm, const std::vector<double>& testphi)
{ 

	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			matrix[i][j] = testm[i][j];
			std::cout << matrix[i][j] << " ";
		}

		Phi[i] = testphi[i];
		std::cout << "  " << Phi[i];
		std::cout << std::endl;
	}

	normalization();

	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << "  " << Phi[i];
		std::cout << std::endl;
	}

	progonkaDirect();

	std::cout << "Alpha[i]: ";

	for (int i = 0; i < nodes - 1; i++)
		std::cout << alpha[i] << " ";
	std::cout << std::endl;

	std::cout << "Beta[i]: ";

	for (int i = 0; i < nodes - 1; i++)
		std::cout << beta[i] << " ";
	std::cout << std::endl;

	progonkaReverse();

	std::cout << "V[i]: ";

	for (int i = 0; i < nodes; i++)
		std::cout << V[i] << " ";
	std::cout << std::endl;
}
#endif

void Task::progonka()
{
	normalization();
	progonkaDirect();
	progonkaReverse();
}

void Task::normalization()
{
	for (int i = 0; i < nodes; i++)
	{
		if (i == 0)
		{
			matrix[i][i + 1] /= matrix[i][i];
		}
		else if (i == (nodes - 1))
		{
			matrix[i][i - 1] /= matrix[i][i];
		}
		else
		{
			matrix[i][i + 1] /= matrix[i][i];
			matrix[i][i - 1] /= matrix[i][i];
		}

		Phi[i] /= matrix[i][i];
		matrix[i][i] = 1.;
	}
}

void Task::progonkaDirect()
{
	alpha[0] = -matrix[0][1];
	beta[0] = Phi[0];

	for (int i = 1; i < (nodes - 1); i++)
	{
		alpha[i] = matrix[i][i + 1] / (-matrix[i][i] - alpha[i - 1] * matrix[i][i - 1]);
		beta[i] = (-Phi[i] + matrix[i][i - 1] * beta[i - 1]) / (-matrix[i][i] - alpha[i - 1] * matrix[i][i - 1]);
	}
}

void Task::progonkaReverse()
{
	V[nodes - 1] = (-Phi[nodes - 1] + beta[nodes - 2] * matrix[nodes - 1][nodes - 2]) / (-1. - alpha[nodes - 2] * matrix[nodes - 1][nodes - 2]);

	for (int i = nodes - 2; i >= 0; i--)
	{
		V[i] = alpha[i] * V[i + 1] + beta[i];
	}
}
