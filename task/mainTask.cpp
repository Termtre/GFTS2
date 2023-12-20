#include "mainTask.h"

double MainTask::k1(double x)
{
    return x;
}

double MainTask::k2(double x)
{
    return 1.;
}

double MainTask::q1(double x)
{
    return x * x;
}

double MainTask::q2(double x)
{
    return x;
}

double MainTask::f1(double x)
{
    return 1.;
}

double MainTask::f2(double x)
{
    return x * x - 1.;
}

double MainTask::a(double x, double h)
{
    if (xi >= x)
    {
        return k1(x - h / 2.);
    }
    else if (xi <= (x - h))
    {
        return k2(x - h / 2.);
    }
    else
    {
        return 1. / (1. / h * ((xi - x + h) / (k1((x - h + xi) / 2.)) + (x - xi) / (k2((xi + x) / 2.))));
    }
}

double MainTask::d(double x, double h)
{
    if (xi >= (x + h / 2))
    {
        return q1(x);
    }
    else if (x <= (x - h / 2))
    {
        return q2(x);
    }
    else
    {
        return 1. / h * q1(((xi + x - h / 2.) / 2.) * (xi - (x - h / 2.)) + (x + h / 2.- xi) * q2(k2((xi + x + h / 2.) / 2.)));
    }
}

double MainTask::phi(double x, double h)
{
    if (xi >= (x + h / 2.))
    {
        return f1(x);
    }
    else if (xi < (x - h / 2.))
    {
        return f2(x);
    }
    else
    {
        return 1. / h * f1(((xi + x - h / 2.) / 2.) * (xi - (x - h / 2.)) + (x + h / 2.- xi) * f2(k2((xi + x + h / 2.) / 2.)));
    }
}

MainTask::MainTask(int nodes) : Task(nodes)
{
    V.resize(nodes * 2);
    Phi.resize(nodes * 2);
    A.resize(nodes * 2);
    B.resize(nodes * 2);
    C.resize(nodes * 2);
    alpha.resize(nodes * 2, 0.);
    beta.resize(nodes * 2);
    //nodes2 = nodes * 2;
}

void MainTask::calculate(QLineSeries*& series, QTableWidget*& table)
{
    double x = 0.;
    double h = 1. / (nodes - 1);
    double h2 = h / 2.;
    double x2 = 0.;
    double v2 = 0.;

    C[0] = 1.;
    B[0] = 0.;
    Phi[0] = mu1;
    Phi[nodes - 1] = mu2;
    C[nodes - 1] = 1.;

    table->setRowCount(nodes);

    for (int i = 1; i < nodes; i++)
    {
        x = i * h;
        A[i] = a(x, h) / (h * h);
        C[i] = (a(x, h) + a(x + h, h)) / (h * h) + d(x, h);
        B[i] = a(x, h) / (h * h);
        Phi[i] = phi(x, h);
    }

    progonka();

    table->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 2, new QTableWidgetItem(QString::number(1)));

    for (int i = 1; i < nodes; i++)
    {
        x = static_cast<double>(i) * h;
        *series << QPointF(x, V[i]);
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(V[i])));
    }
}

void MainTask::calculate2(QLineSeries *&, QTableWidget *&)
{

}
