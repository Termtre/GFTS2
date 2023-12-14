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
        return h * 1. / (((xi - x + h) / k1) + ((x - xi) / k2));
    }
}

double TestTask::d(double x, double h)
{
    if (xi >= (x + h / 2))
    {
        return q1;
    }
    else if (x <= (x - h / 2))
    {
        return q2;
    }
    else
    {
        return (1. / h) * ((q1 * (xi - x + h / 2.)) + (q2 * (x + h / 2. - xi)));
    }
}

double TestTask::phi(double x, double h)
{
    if (xi >= (x + h / 2.))
    {
        return f1;
    }
    else if (xi < (x - h / 2.))
    {
        return f2;
    }
    else
    {
        return (1. / h) * (f1 * (xi - x + h / 2.) + f2 * (x + h / 2. - xi));
    }
}

TestTask::TestTask(int N) : Task(N)
{}

void TestTask::calculate(QLineSeries*& series, QTableWidget*& table)
{
    double x = 0.;
    double h = 1. / (nodes - 1);

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

    *series << QPointF(0., 1.); // ????
    table->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 2, new QTableWidgetItem(QString::number(1)));

    for (int i = 1; i < nodes; i++)
    {
        x = static_cast<double>(i) * h;
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

    table->setRowCount(nodes);

    *series << QPointF(0., 1.);

    table->setItem(0, 0, new QTableWidgetItem(QString::number(0)));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(x)));
    table->setItem(0, 2, new QTableWidgetItem(QString::number(u)));

    for (int i = 1; i < nodes; i++)
    {
        x += h;
        if (x < xi)
            u = -0.960308 * exp((sqrt(30.) * x) / (sqrt(209.))) + -1.37303 / (exp((sqrt(30.) * x) / (sqrt(209.)))) + 10. / 3.;
        else
            u =  (-2.45985) * exp(x) + (-6.2589) / (exp(x)) + (100. * sin((3. * M_PI) / 10.)) / 9.;

        *series << QPointF(x, u);
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(u)));
    }
}
