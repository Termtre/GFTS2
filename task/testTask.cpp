#include "testTask.h"
#define _USE_MATH_DEFINES

double TestTask::a(double x, double h)
{
    if (xi >= x)
    {
        return k1;
    }
    else if (xi <= (x - h))
    {
        return k2;
    }
    else
    {
        return 1. / (1. / h * ((xi - x + h) / k1 + (x - xi) / k2));
    }
}

double TestTask::d(double x, double h)
{
    if (xi >= (x + h / 2.))
    {
        return q1;
    }
    else if (xi <= (x - h / 2.))
    {
        return q2;
    }
    else
    {
        return 1. / h * (q1 * (xi - (x - h / 2.)) + q2 * (x + h / 2 - xi));
    }
}

double TestTask::phi(double x, double h)
{
    if (xi >= (x + h / 2.))
    {
        return f1;
    }
    else if (xi <= (x - h / 2.))
    {
        return f2;
    }
    else
    {
        return 1. / h * (f1 * (xi - (x - h / 2.)) + f2 * (x + h / 2 - xi));
    }
}

TestTask::TestTask(int N) : nodes(N)
{}

void TestTask::calculate(QLineSeries*& series, QTableWidget*& table)
{
    double x = 0.;
    double h = 1. / (nodes - 1);

    std::vector<double> A(nodes);
    std::vector<double> B(nodes);
    std::vector<double> C(nodes);
    std::vector<double> Phi(nodes);
    std::vector<double> V(nodes);

    C[0] = 1.;
    A[0] = 0.;
    B[0] = 0.;
    Phi[0] = mu1;
    Phi[nodes - 1] = mu2;
    C[nodes - 1] = 1.;
    A[nodes - 1] = 0.;
    B[nodes - 1] = 0.;

    table->setRowCount(nodes);

    for (int i = 1; i < (nodes - 1); i++)
    {
        x += h;
        /*A[i] = a(x, h) / (h * h);
        C[i] = -((2. * a(x, h)) / (h * h) + d(x, h));
        B[i] = a(x, h) / (h * h);
        Phi[i] = -phi(x, h);*/
        A[i] = a(x, h) / (h * h);
        C[i] = -((a(x, h) + a(x + h, h)) / (h * h) + d(x, h));
        B[i] = a(x + h, h) / (h * h);
        Phi[i] = -phi(x, h);
    }

    Task task1(nodes);
    task1.setProgonka(A, B, C, Phi);
    task1.progonka();
    V = task1.getV();

    *series << QPointF(0., 1.);
    table->setItem(0, 0, new QTableWidgetItem(QString::number(0.)));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(0.)));
    table->setItem(0, 3, new QTableWidgetItem(QString::number(1.)));

    x = 0.0;

    for (int i = 1; i < nodes; i++)
    {
        x += h;
        *series << QPointF(x, V[i]);
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(V[i])));
    }
}

void TestTask::calculateTrue(QLineSeries*& series, QTableWidget*& table)
{
    double x = 0., u = 1.;
    double h = 1. / (nodes - 1.);
    double C1 = -3.542581951274;
    double C2 = -1.20924861794;
    double C3 = -0.28609673798342;
    double C4 = 1.61718565178286;
    double a = 0.378867615211;
    double p = 0.182762209622;

    table->setRowCount(nodes);

    *series << QPointF(0., 1.);

    table->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(x)));
    table->setItem(0, 2, new QTableWidgetItem(QString::number(u)));

    for (int i = 1; i < nodes; i++)
    {
        x += h;
        if (x < xi)
            //u = C1 * exp(a * x) + C2 * exp(-a * x) + 10. / 3.;
            //u = -0.960308 * exp((sqrt(30.) * x) / (sqrt(209.))) + -1.37303 / (exp((sqrt(30.) * x) / (sqrt(209.)))) + 10. / 3.;
            u = -0.960308 * exp(sqrt(30. / 209.) * x) + -1.37303 * exp(-sqrt(30. / 209.) * x) + 10. / 3.;
        else
            //u =  C3 * exp(x) + C4 * exp(-x) + p;
            //u = (-6.2589) * exp(x) + (-2.45985) / (exp(x)) + (100. * sin((3. * M_PI) / 10.)) / 9.;
            u = (-2.45985) * exp(x) + (-6.2589) * (exp(-x)) + sin(0.3 * M_PI) / 0.09;

        *series << QPointF(x, u);
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(u)));
    }
}
