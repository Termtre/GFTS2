#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QtCharts>
#include "../task/testTask.h"
#include "../task/mainTask.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_firstStart_clicked();

    void on_secondStart_clicked();

    void on_firstDel_clicked();

    void on_secondDel_clicked();

    void on_firstShowDot_clicked(bool checked);

    void on_secondShowDot_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

private:
    QChart* chart1;
    QChart* chart2;

    QLineSeries* testAnSeries = nullptr;
    QLineSeries* testSeries = nullptr;
    QLineSeries* mainSeries = nullptr;
    QLineSeries* main2Series = nullptr;

    QValueAxis* axisX1;
    QValueAxis* axisY1;
    QValueAxis* axisX2;
    QValueAxis* axisY2;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
