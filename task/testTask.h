#pragma once

#include "task.h"
#include <cmath>

class TestTask : public Task
{
private:
    double k1 = 2.09;                       // x <= xi
    double k2 = 0.09;                       // x >= xi
    double f1 = 1.;                         // x <= xi
    double f2 = sin(0.3 * M_PI);            // x >= xi
    double q1 = 0.3;                        // x <= xi
    double q2 = 0.09;                       // x => xi

    double a(double x, double h);
    double d(double x, double h);
    double phi(double x, double h);

public:
    TestTask(int);
	~TestTask() {}

    void calculate(QLineSeries*&, QTableWidget*&);                     // Вычислить траекторию методом баланса
    void calculateTrue(QLineSeries*&, QTableWidget*&);                 // Вычислить траекторию аналитически

};
