#include "mainTask.h"

double MainTask::k1(double x)
{
    return x * x + 2.;
}

double MainTask::k2(double x)
{
    return x * x;
}

double MainTask::q1(double x)
{
    return x;
}

double MainTask::q2(double x)
{
    return x * x;
}

double MainTask::f1(double x)
{
    return 1.;
}

double MainTask::f2(double x)
{
    return sin(M_PI * x);
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
    if (xi >= (x + h / 2.))
    {
        return q1(x);
    }
    else if (xi <= (x - h / 2.))
    {
        return q2(x);
    }
    else
    {
        return 1. / h * (q1((xi + (x - h / 2.)) / 2.) * (xi - (x - h / 2.)) + q2((xi + x + h / 2.) / 2.) * (x + h / 2 - xi));
    }
}

double MainTask::phi(double x, double h)
{
    if (xi >= (x + h / 2.))
    {
        return f1(x);
    }
    else if (xi <= (x - h / 2.))
    {
        return f2(x);
    }
    else
    {
        return 1. / h * (f1((xi + (x - h / 2.)) / 2.) * (xi - (x - h / 2.)) + f2((xi + x + h / 2.) / 2.) * (x + h / 2 - xi));
    }
}

MainTask::MainTask(int _nodes) : nodes(_nodes)
{}

void MainTask::calculate(QLineSeries*& series, QLineSeries*& series2, QTableWidget*& table)
{
    std::vector<double> A(nodes);
    std::vector<double> B(nodes);
    std::vector<double> C(nodes);
    std::vector<double> Phi(nodes);
    std::vector<double> V(nodes);

    int nodes2 = nodes * 2 - 1;

    std::vector<double> A2(nodes2);
    std::vector<double> B2(nodes2);
    std::vector<double> C2(nodes2);
    std::vector<double> Phi2(nodes2);
    std::vector<double> V2(nodes2);

    double x = 0.;
    double h = 1. / (nodes - 1);
    double x2 = 0.;
    double h2 = 1. / (nodes2 - 1);

    C[0] = 1.;
    C2[0] = 1.;

    A[0] = 0.;
    A2[0] = 0.;

    B[0] = 0.;
    B2[0] = 0.;

    Phi[0] = mu1;
    Phi2[0] = mu1;

    Phi[nodes - 1] = mu2;
    Phi2[nodes2 - 1] = mu2;

    B[nodes - 1] = 0.;
    B2[nodes2 - 1] = 0.;

    A[nodes - 1] = 0.;
    A2[nodes2 - 1] = 0.;

    C[nodes - 1] = 1.;
    C2[nodes2 - 1] = 1.;

    table->setRowCount(nodes);

    for (int i = 1; i < (nodes - 1); i++)
    {
        x += h;
        A[i] = a(x, h) / (h * h);
        C[i] = -((a(x, h) + a(x + h, h)) / (h * h) + d(x, h));
        B[i] = a(x + h, h) / (h * h);
        Phi[i] = -phi(x, h);
    }

    for (int i = 1; i < (nodes2 - 1); i++)
    {
        x2 += h2;
        A2[i] = a(x2, h2) / (h2 * h2);
        C2[i] = -((a(x2, h2) + a(x2 + h2, h2)) / (h2 * h2) + d(x2, h2));
        B2[i] = a(x2 + h2, h2) / (h2 * h2);
        Phi2[i] = -phi(x2, h2);
    }

    Task task1(nodes);
    Task task2(nodes2);

    task1.setProgonka(A, B, C, Phi);
    task1.progonka();
    V = task1.getV();
    task2.setProgonka(A2, B2, C2, Phi2);
    task2.progonka();
    V2 = task2.getV();

    x = 0.;

    *series << QPointF(0., 1.);
    table->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 2, new QTableWidgetItem(QString::number(1)));

    for (int i = 1; i < nodes; i++)
    {
        x += h;
        *series << QPointF(x, V[i]);
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(V[i])));
    }

    x2 = 0.;

    for (int i = 0; i < nodes2; i += 2)
    {
        x2 = static_cast<double>(i) * (h2);
        *series2 << QPointF(x2, V2[i]);
        table->setItem(i / 2, 1, new QTableWidgetItem(QString::number(x2)));
        table->setItem(i / 2, 3, new QTableWidgetItem(QString::number(V2[i])));
    }

    for (int i = 0; i < nodes; i++)
    {
        table->setItem(i, 4, new QTableWidgetItem(QString::number(abs(V2[2 * i] - V[i]))));
    }
}

/*void MainTask::calculate1(QLineSeries*& series, QTableWidget*& table)
{
    double x = 0.;
    double h = 1. / (nodes - 1);

    C[0] = 1.;
    B[0] = 0.;
    Phi[0] = mu1;
    Phi[nodes - 1] = mu2;
    C[nodes - 1] = 1.;

    table->setRowCount(nodes);

    for (int i = 1; i < (nodes - 1); i++)
    {
        x += h;
        A[i] = a(x, h) / (h * h);
        C[i] = -((a(x, h) + a(x + h, h)) / (h * h) + d(x, h));
        B[i] = a(x + h, h) / (h * h);
        Phi[i] = -phi(x, h);
    }

    progonka();
    *series << QPointF(0., 1.);
    table->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 2, new QTableWidgetItem(QString::number(1)));

    x = 0.;

    for (int i = 1; i < nodes; i++)
    {
        x += h;
        *series << QPointF(x, V[i]);
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(V[i])));
    }
}

void MainTask::calculate2(QLineSeries*& series, QTableWidget*& table)
{
    double x = 0.;
    double h = 1. / (nodes - 1);

    C[0] = 1.;
    B[0] = 0.;
    Phi[0] = mu1;
    Phi[nodes - 1] = mu2;
    C[nodes - 1] = 1.;

    table->setRowCount(ceil(nodes / 2) + 1);

    for (int i = 1; i < (nodes - 1); i++)
    {
        x += h;
        A[i] = a(x, h) / (h * h);
        C[i] = -((a(x, h) + a(x + h, h)) / (h * h) + d(x, h));
        B[i] = a(x + h, h) / (h * h);
        Phi[i] = -phi(x, h);
    }

    progonka();

    for (int i = 0; i < nodes; i += 2)
    {
        x = static_cast<double>(i) * h;
        *series << QPointF(x, V[i]);
        table->setItem(i / 2, 3, new QTableWidgetItem(QString::number(V[i])));
    }
}*/
