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
    chart2->legend()->setVisible(true);
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
    axisY2->setTitleText("v, v2");
    chart2->addAxis(axisY2, Qt::AlignLeft);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);

    ui->textEdit_3->setText("Справка");
    ui->textEdit_3->append("Для решения задачи использована равномерная сетка с числом разбиений n = " + QString().number(0) + ";");
    ui->textEdit_3->append("Задача должна быть решена с погрешностью не более ε = 0.5⋅10^{-6};");
    ui->textEdit_3->append("Задача решена с погрешностью ε1 = " + QString().number(0) + ";");
    ui->textEdit_3->append("Максимальное отклонение аналитического и численного решений наблюдается в точке x = " + QString().number(0) + ";");

    ui->textEdit_4->setText("Справка");
    ui->textEdit_4->append("Для решения задачи использована равномерная сетка с числом разбиений n = " + QString().number(0) + ";");
    ui->textEdit_4->append("Задача должна быть решена с погрешностью не более ε = 0.5⋅10^{-6};");
    ui->textEdit_4->append("Задача решена с погрешностью ε2 = " + QString().number(0) + ";");
    ui->textEdit_4->append("Максимальная разность численных решений в общих узлах сетки наблюдается в точке x = " + QString().number(0) + ";");

    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->checkBox_4->setChecked(true);
    ui->firstShowDot->setChecked(true);
    ui->secondShowDot->setChecked(true);
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

    if (ui->checkBox->isChecked()) testAnSeries->setVisible(true);
    else testAnSeries->setVisible(false);

    if (ui->checkBox_2->isChecked()) testSeries->setVisible(true);
    else testSeries->setVisible(false);

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

    double e1 = 0.;
    double x1 = 0.;

    for (int i = 0; i <= n; i++)
    {
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(abs(ui->tableWidget->item(i, 3)->text().toDouble() - ui->tableWidget->item(i, 2)->text().toDouble()))));
        if (e1 < ui->tableWidget->item(i, 4)->text().toDouble())
        {
            e1 = ui->tableWidget->item(i, 4)->text().toDouble();
            x1 = ui->tableWidget->item(i, 1)->text().toDouble();
        }
    }

    ui->textEdit_3->setText("Справка");
    ui->textEdit_3->append("Для решения задачи использована равномерная сетка с числом разбиений n = " + QString().number(ui->tableWidget->rowCount() - 1) + ";");
    ui->textEdit_3->append("Задача должна быть решена с погрешностью не более ε = 0.5⋅10^{-6};");
    ui->textEdit_3->append("Задача решена с погрешностью ε1 = " + QString().number(e1) + ";");
    ui->textEdit_3->append("Максимальное отклонение аналитического и численного решений наблюдается в точке x = " + QString().number(x1) + ";");
}


void MainWindow::on_secondStart_clicked()
{
    ui->graphicsView_2->zoomIt(true);

    mainSeries = new QLineSeries();
    mainSeries->setName("Численная траектория");
    main2Series = new QLineSeries();
    main2Series->setName("Численная траектория с удвоенным числом разбиений");

    int n = ui->lineEdit_2->text().toInt();

    MainTask task(n + 1);
    task.calculate(mainSeries, ui->tableWidget_2);
    MainTask task2(2 * n + 1);
    task2.calculate2(main2Series, ui->tableWidget_2);

    if (ui->checkBox_3->isChecked()) main2Series->setVisible(true);
    else main2Series->setVisible(false);

    if (ui->checkBox_4->isChecked()) mainSeries->setVisible(true);
    else mainSeries->setVisible(false);

    if (ui->secondShowDot->isChecked())
    {
        mainSeries->setPointsVisible(true);
        main2Series->setPointsVisible(true);
    }
    else
    {
        mainSeries->setPointsVisible(false);
        main2Series->setPointsVisible(true);
    }

    chart2->addSeries(mainSeries);
    chart2->addSeries(main2Series);

    mainSeries->attachAxis(axisX2);
    mainSeries->attachAxis(axisY2);

    main2Series->attachAxis(axisX2);
    main2Series->attachAxis(axisY2);

    ui->graphicsView_2->setChart(chart2);

    double e2 = 0.;
    double x2 = 0.;

    for (int i = 0; i <= n; i++)
    {
        ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem(QString::number(abs(ui->tableWidget_2->item(i, 3)->text().toDouble() - ui->tableWidget_2->item(i, 2)->text().toDouble()))));
        if (e2 < ui->tableWidget_2->item(i, 4)->text().toDouble())
        {
            e2 = abs(ui->tableWidget_2->item(i, 4)->text().toDouble());
            x2 = ui->tableWidget_2->item(i, 1)->text().toDouble();
        }
    }

    ui->textEdit_4->setText("Справка");
    ui->textEdit_4->append("Для решения задачи использована равномерная сетка с числом разбиений n = " + QString().number(ui->tableWidget_2->rowCount() - 1) + ";");
    ui->textEdit_4->append("Задача должна быть решена с погрешностью не более ε = 0.5⋅10^{-6};");
    ui->textEdit_4->append("Задача решена с погрешностью ε2 = " + QString().number(e2) + ";");
    ui->textEdit_4->append("Максимальная разность численных решений в общих узлах сетки наблюдается в точке x = " + QString().number(x2) + ";");
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
    if (mainSeries || main2Series)
    {
        ui->graphicsView_2->zoomIt(false);
        chart2->removeAllSeries();
        mainSeries = nullptr;
        main2Series = nullptr;
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
    if (mainSeries || main2Series)
    {
        if (checked)
        {
            mainSeries->setPointsVisible(true);
            main2Series->setPointsVisible(true);
        }
        else
        {
            mainSeries->setPointsVisible(false);
            main2Series->setPointsVisible(false);
        }
    }
}


void MainWindow::on_checkBox_2_clicked(bool checked)
{
    if (testSeries)
    {
        if (checked)
        {
            testSeries->setVisible(true);
        }
        else
        {
            testSeries->setVisible(false);
        }
    }
}


void MainWindow::on_checkBox_clicked(bool checked)
{
    if (testAnSeries)
    {
        if (checked)
        {
            testAnSeries->setVisible(true);
        }
        else
        {
            testAnSeries->setVisible(false);
        }
    }
}


void MainWindow::on_checkBox_4_clicked(bool checked)
{
    if (mainSeries)
    {
        if (checked)
        {
            mainSeries->setVisible(true);
        }
        else
        {
            mainSeries->setVisible(false);
        }
    }
}


void MainWindow::on_checkBox_3_clicked(bool checked)
{
    if (main2Series)
    {
        if (checked)
        {
            main2Series->setVisible(true);
        }
        else
        {
            main2Series->setVisible(false);
        }
    }
}

