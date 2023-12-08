#pragma once

#include <vector>

class Task
{
protected:
	std::vector<std::vector<double>> matrix;               // Трехдиагональная матрица
	std::vector<double> V;                                 // Вектор приближенных решений краевой задачи
	std::vector<double> Phi;                               // Правая часть СЛАУ
	std::vector<double> alpha;                             // Вектор альф для метода прогонки
	std::vector<double> beta;                              // Вектор бет для метода прогонки
	int nodes;                                             // Количество участков сетки()

public:
	Task(int);                         // Конструктор, принимающий количество узлов сетки, включая нулевой
	~Task() {}

#ifdef testMode

	// для тестирования метода прогонки. принимает трехдиагональную матрицу, правую часть СЛАУ 
	void test(const std::vector<std::vector<double>>&, 
		      const std::vector<double>&);

#endif

protected:
	void progonka();                   // Метод прогонки
	void normalization();              // Нормировка матрицы
	void progonkaDirect();             // Прямой ход прогонки
	void progonkaReverse();            // Обратный ход прогонки   
	void progonkaDirectParallel();     // Прямой ход встречной прогонки (Если есть желание - можете реализовать)
	void progonkaReverseParallel();    // Обратный ход встречной прогонки (Если есть желание - можете реализовать)

};