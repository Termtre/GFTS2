#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("GFTS2");

    ui->tabWidget->setTabText(0, "Тестовая задача");
    ui->tabWidget->setTabText(1, "Основная задача");
    ui->tabWidget->setCurrentIndex(0);

    ui->tabWidget_2->setTabText(0, "Таблица");
    ui->tabWidget_2->setTabText(1, "Справка");
    ui->tabWidget_2->setCurrentIndex(0);

    ui->tabWidget_3->setTabText(0, "Таблица");
    ui->tabWidget_3->setTabText(1, "Справка");
    ui->tabWidget_3->setCurrentIndex(0);

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget_2->verticalHeader()->hide();

    chart1 = new QChart();
    chart1->legend()->setVisible(true);
    chart1->setTitle("Тестовая задача");

    chart2 = new QChart();
    chart2->legend()->setVisible(false);
    chart2->setTitle("Основная задача");

    axisX1 = new QValueAxis();
    axisX1->setLabelFormat("%f");
    axisX1->setTickCount(10);
    axisX1->setTitleText("x");
    chart1->addAxis(axisX1, Qt::AlignBottom);

    axisX2 = new QValueAxis();
    axisX2->setLabelFormat("%f");
    axisX2->setTickCount(10);
    axisX2->setTitleText("x");
    chart2->addAxis(axisX2, Qt::AlignBottom);

    axisY1 = new QValueAxis();
    axisY1->setLabelFormat("%f");
    axisY1->setTickCount(10);
    axisY1->setTitleText("u, v");
    chart1->addAxis(axisY1, Qt::AlignLeft);

    axisY2 = new QValueAxis();
    axisY2->setLabelFormat("%f");
    axisY2->setTickCount(10);
    axisY2->setTitleText("v");
    chart2->addAxis(axisY2, Qt::AlignLeft);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_firstStart_clicked()
{
    ui->graphicsView->zoomIt(true);

    testAnSeries = new QLineSeries();
    testAnSeries->setName("Аналитическая траектория");
    testSeries = new QLineSeries();
    testSeries->setName("Численная траектория");

    int n = ui->lineEdit->text().toInt();

    TestTask task(n + 1);

    task.calculateTrue(testAnSeries, ui->tableWidget);
    task.calculate(testSeries, ui->tableWidget);

    if (ui->firstShowDot->isChecked())
    {
        testAnSeries->setPointsVisible(true);
        testSeries->setPointsVisible(true);
    }
    else
    {
        testAnSeries->setPointsVisible(false);
        testSeries->setPointsVisible(false);
    }

    chart1->addSeries(testAnSeries);
    chart1->addSeries(testSeries);

    testAnSeries->attachAxis(axisX1);
    testAnSeries->attachAxis(axisY1);

    testSeries->attachAxis(axisX1);
    testSeries->attachAxis(axisY1);

    ui->graphicsView->setChart(chart1);
}


void MainWindow::on_secondStart_clicked()
{
    ui->graphicsView_2->zoomIt(true);

    mainSeries = new QLineSeries();

    int n = ui->lineEdit_2->text().toInt();

    MainTask task(n + 1);
    task.calculate(mainSeries, ui->tableWidget_2);

    if (ui->secondShowDot->isChecked())
    {
        mainSeries->setPointsVisible(true);
    }
    else
    {
        mainSeries->setPointsVisible(false);
    }

    chart2->addSeries(mainSeries);

    mainSeries->attachAxis(axisX2);
    mainSeries->attachAxis(axisY2);

    ui->graphicsView_2->setChart(chart2);
}


void MainWindow::on_firstDel_clicked()
{
    if (testAnSeries || testSeries)
    {
        ui->graphicsView->zoomIt(false);
        chart1->removeAllSeries();
        testAnSeries = nullptr;
        testSeries = nullptr;
    }
}


void MainWindow::on_secondDel_clicked()
{
    if (mainSeries)
    {
        ui->graphicsView_2->zoomIt(false);
        chart2->removeAllSeries();
        mainSeries = nullptr;
    }
}


void MainWindow::on_firstShowDot_clicked(bool checked)
{
    if (testAnSeries || testSeries)
    {
        if (checked)
        {
            testAnSeries->setPointsVisible(true);
            testSeries->setPointsVisible(true);
        }
        else
        {
            testAnSeries->setPointsVisible(false);
            testSeries->setPointsVisible(false);
        }
    }
}


void MainWindow::on_secondShowDot_clicked(bool checked)
{
    if (mainSeries)
    {
        if (checked)
        {
            mainSeries->setPointsVisible(true);
        }
        else
        {
            mainSeries->setPointsVisible(false);
        }
    }
}

