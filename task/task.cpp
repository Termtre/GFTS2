#include "task.h"

Task::Task(int n) : nodes(n)
{
    V.resize(nodes);
    Phi.resize(nodes);
    A.resize(nodes);
    B.resize(nodes);
    C.resize(nodes);
    alpha.resize(nodes, 0.);
    beta.resize(nodes, 0);

}

void Task::progonka()
{
    //normalization();
    progonkaDirect();
    progonkaReverse();
}

void Task::resize(int n)
{
    nodes = n;
    V.resize(nodes);
    Phi.resize(nodes);
    A.resize(nodes);
    B.resize(nodes);
    C.resize(nodes);
    alpha.resize(nodes, 0.);
    beta.resize(nodes, 0);
}

void Task::normalization()
{
    B[0] /= C[0];
    Phi[0] /= C[0];
    C[0] = 1.;

    A[nodes - 1] /= C[nodes - 1];
    Phi[nodes - 1] /= C[nodes - 1];
    C[nodes - 1] = 1.;
}

void Task::progonkaDirect()
{
    alpha[1] = -B[0];
    beta[1] = Phi[0];

    for (int i = 1; i < (nodes - 1); i++)
    {
        alpha[i + 1] = B[i] / (-C[i] - alpha[i] * A[i]);
        beta[i + 1] = (-Phi[i] + A[i] * beta[i]) / (-C[i] - alpha[i] * A[i]);
    }
}

void Task::progonkaReverse()
{
    V[nodes - 1] = (A[nodes - 1] * beta[nodes - 1] - Phi[nodes - 1]) / (-A[nodes - 1] * alpha[nodes - 1] - 1.);

    for (int i = nodes - 2; i >= 0; i--)
    {
        V[i] = alpha[i + 1] * V[i + 1] + beta[i + 1];
    }
}
