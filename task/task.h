#pragma once

#include <vector>
#include <QLineSeries>
#include <QTableWidget>

class Task
{
protected:
    double xi = 0.3;                                       // Кси
    double mu1 = 1.;                                       // Левая граница
    double mu2 = 0.;                                       // Правая граница

    std::vector<double> A;                                 // Левый элемент от диагонали
    std::vector<double> C;                                 // Диагональ
    std::vector<double> B;                                 // Правый элемент от диагонали
	std::vector<double> V;                                 // Вектор приближенных решений краевой задачи
	std::vector<double> Phi;                               // Правая часть СЛАУ
	std::vector<double> alpha;                             // Вектор альф для метода прогонки
	std::vector<double> beta;                              // Вектор бет для метода прогонки
	int nodes;                                             // Количество участков сетки()

public:
	Task(int);                         // Конструктор, принимающий количество узлов сетки, включая нулевой
	~Task() {}

private:
    void normalization();              // Нормировка матрицы
    void progonkaDirect();             // Прямой ход прогонки
    void progonkaReverse();            // Обратный ход прогонки
    void progonkaDirectParallel();     // Прямой ход встречной прогонки (Если есть желание - можете реализовать)
    void progonkaReverseParallel();    // Обратный ход встречной прогонки (Если есть желание - можете реализовать)

protected:
	void progonka();                   // Метод прогонки
    void resize(int n);                // Изменение полей

};
