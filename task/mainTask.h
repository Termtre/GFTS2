#pragma once

#include "task.h"

class MainTask : public Task
{
private:
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

    void calculate(QLineSeries*&, QTableWidget*&);
    void calculate2(QLineSeries*&, QTableWidget*&);
};
