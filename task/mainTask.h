#pragma once

#include "task.h"
#include <QLineSeries>
#include <QTableWidget>
#include <cmath>
#include <vector>

class MainTask
{
private:
    double xi = 0.3;                                       // Кси
    double mu1 = 1.;                                       // Левая граница
    double mu2 = 0.;                                       // Правая граница
    int nodes;                                             // Число узлов

    double k1(double x);                                   // k1, x <= 0.3
    double k2(double x);                                   // k2, x >= 0.3
    double q1(double x);                                   // q1, x >= 0.3
    double q2(double x);                                   // q2, x <= 0.3
    double f1(double x);                                   // f1, x >= 0.3
    double f2(double x);                                   // f2, x <= 0.3

    double a(double x, double h);
    double d(double x, double h);
    double phi(double x, double h);

public:
	MainTask(int);
	~MainTask() {}

    void calculate(QLineSeries*&, QLineSeries*&, QLineSeries*&, QTableWidget*&);
};
