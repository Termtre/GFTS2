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

    chartRaz1 = new QChart();
    chartRaz1->legend()->setVisible(false);
    chartRaz1->setTitle("Разность численной траектории и аналитической");

    chartRaz2 = new QChart();
    chartRaz2->legend()->setVisible(false);
    chartRaz2->setTitle("Разность численных траекторий");

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

    razX1 = new QValueAxis();
    razX1->setLabelFormat("%f");
    razX1->setTickCount(10);
    razX1->setTitleText("x");
    chartRaz1->addAxis(razX1, Qt::AlignBottom);

    razX2 = new QValueAxis();
    razX2->setLabelFormat("%f");
    razX2->setTickCount(10);
    razX2->setTitleText("x");
    chartRaz2->addAxis(razX2, Qt::AlignBottom);

    razY1 = new QValueAxis();
    razY1->setLabelFormat("%f");
    razY1->setTickCount(10);
    razY1->setTitleText("|ui - vi| * 10^10");
    chartRaz1->addAxis(razY1, Qt::AlignLeft);

    razY2 = new QValueAxis();
    razY2->setLabelFormat("%f");
    razY2->setTickCount(10);
    razY2->setTitleText("|v2i - vi| * 10^10");
    chartRaz2->addAxis(razY2, Qt::AlignLeft);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);

    ui->textEdit_3->setText("Справка");
    ui->textEdit_3->append("Для решения задачи использована равномерная сетка с числом разбиений n = " + QString().number(0) + ";");
    ui->textEdit_3->append("Задача должна быть решена с погрешностью не более ε = 0.5⋅10^{-6};");
    ui->textEdit_3->append("Задача решена с погрешностью ε1 = " + QString().number(0) + ";");
    ui->textEdit_3->append("Максимальное отклонение аналитического и численного решений наблюдается в точке x = " + QString().number(0) + ";");
    ui->textEdit_3->append("Численная и аналитическая траектории вычислена с шагом: " + QString().number(0) + ";");

    ui->textEdit_4->setText("Справка");
    ui->textEdit_4->append("Для решения задачи использована равномерная сетка с числом разбиений n = " + QString().number(0) + ";");
    ui->textEdit_4->append("Задача должна быть решена с погрешностью не более ε = 0.5⋅10^{-6};");
    ui->textEdit_4->append("Задача решена с погрешностью ε2 = " + QString().number(0) + ";");
    ui->textEdit_4->append("Максимальная разность численных решений в общих узлах сетки наблюдается в точке x = " + QString().number(0) + ";");
    ui->textEdit_4->append("Численная траектория с шагом: " + QString().number(0) + ";");
    ui->textEdit_4->append("Численная траектория с большим числом разбиений вычислены с шагом: " + QString().number(0) + ";");

    ui->checkBox->setChecked(true);
    ui->checkBox_2->setChecked(true);
    ui->checkBox_3->setChecked(true);
    ui->checkBox_4->setChecked(true);
    ui->firstShowDot->setChecked(true);
    ui->secondShowDot->setChecked(true);

    ui->radioButton_3->setChecked(true);
    ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_firstStart_clicked()
{
    if (ui->lineEdit->text().toInt() <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Число разбиений должно быть больше 0");
        msgBox.exec();
        return;
    }

    ui->graphicsView->zoomIt(true);

    testAnSeries = new QLineSeries();
    testAnSeries->setName("Аналитическая траектория");
    testSeries = new QLineSeries();
    testSeries->setName("Численная траектория");
    raz1 = new QLineSeries();
    raz1->setVisible(true);

    int n = ui->lineEdit->text().toInt();

    TestTask task(n + 1);

    task.calculate(testSeries, testAnSeries, raz1, ui->tableWidget);

    if (ui->checkBox->isChecked()) testAnSeries->setVisible(true);
    else testAnSeries->setVisible(false);

    if (ui->checkBox_2->isChecked()) testSeries->setVisible(true);
    else testSeries->setVisible(false);

    if (ui->firstShowDot->isChecked())
    {
        testAnSeries->setPointsVisible(true);
        testSeries->setPointsVisible(true);
        raz1->setPointsVisible(true);
    }
    else
    {
        testAnSeries->setPointsVisible(false);
        testSeries->setPointsVisible(false);
        raz1->setPointsVisible(false);
    }

    chart1->addSeries(testAnSeries);
    chart1->addSeries(testSeries);
    chartRaz1->addSeries(raz1);

    testAnSeries->attachAxis(axisX1);
    testAnSeries->attachAxis(axisY1);
    raz1->attachAxis(razX1);

    testSeries->attachAxis(axisX1);
    testSeries->attachAxis(axisY1);
    raz1->attachAxis(razY1);

    if (ui->radioButton_3->isChecked())
    {
        ui->graphicsView->setChart(chart1);
    }
    else
    {
        ui->graphicsView->setChart(chartRaz1);
    }

    double e1 = 0.;
    double x1 = 0.;

    for (int i = 0; i <= n; i++)
    {
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
    ui->textEdit_3->append("Численная и аналитическая траектории вычислены с шагом: " + QString().number(ui->tableWidget->item(1, 1)->text().toDouble() - ui->tableWidget->item(0, 1)->text().toDouble()) + ";");
}


void MainWindow::on_secondStart_clicked()
{
    if (ui->lineEdit_2->text().toInt() <= 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Число разбиений должно быть больше 0");
        msgBox.exec();
        return;
    }

    ui->graphicsView_2->zoomIt(true);

    mainSeries = new QLineSeries();
    mainSeries->setName("Численная траектория");
    main2Series = new QLineSeries();
    main2Series->setName("Численная траектория с удвоенным числом разбиений");
    raz2 = new QLineSeries();
    raz2->setVisible(true);

    int n = ui->lineEdit_2->text().toInt();

    MainTask task(n + 1);
    task.calculate(mainSeries, main2Series, raz2, ui->tableWidget_2);

    if (ui->checkBox_3->isChecked()) main2Series->setVisible(true);
    else main2Series->setVisible(false);

    if (ui->checkBox_4->isChecked()) mainSeries->setVisible(true);
    else mainSeries->setVisible(false);

    if (ui->secondShowDot->isChecked())
    {
        mainSeries->setPointsVisible(true);
        main2Series->setPointsVisible(true);
        raz2->setPointsVisible(true);
    }
    else
    {
        mainSeries->setPointsVisible(false);
        main2Series->setPointsVisible(false);
        raz2->setPointsVisible(false);
    }

    chart2->addSeries(mainSeries);
    chart2->addSeries(main2Series);
    chartRaz2->addSeries(raz2);

    mainSeries->attachAxis(axisX2);
    mainSeries->attachAxis(axisY2);
    raz2->attachAxis(razX2);

    main2Series->attachAxis(axisX2);
    main2Series->attachAxis(axisY2);
    raz2->attachAxis(razY2);

    if (ui->radioButton->isChecked())
    {
        ui->graphicsView_2->setChart(chart2);
    }
    else
    {
        ui->graphicsView_2->setChart(chartRaz2);
    }

    double e2 = 0.;
    double x2 = 0.;

    for (int i = 0; i <= n; i++)
    {
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
    ui->textEdit_4->append("Численная траектория вычислена с шагом: " + QString().number(ui->tableWidget_2->item(1, 1)->text().toDouble() - ui->tableWidget_2->item(0, 1)->text().toDouble()) + ";");
    ui->textEdit_4->append("Численная траектория с большим числом разбиений вычислена с шагом: " + QString().number((ui->tableWidget_2->item(1, 1)->text().toDouble() - ui->tableWidget_2->item(0, 1)->text().toDouble()) / 2.) + ";");
}


void MainWindow::on_firstDel_clicked()
{
    if (testAnSeries || testSeries)
    {
        ui->graphicsView->zoomIt(false);
        chart1->removeAllSeries();
        testAnSeries = nullptr;
        testSeries = nullptr;
        chartRaz1->removeAllSeries();
        raz1 = nullptr;
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
        chartRaz2->removeAllSeries();
        raz2 = nullptr;
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
            raz1->setPointsVisible(true);
        }
        else
        {
            testAnSeries->setPointsVisible(false);
            testSeries->setPointsVisible(false);
            raz1->setPointsVisible(false);
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
            raz2->setPointsVisible(true);
        }
        else
        {
            mainSeries->setPointsVisible(false);
            main2Series->setPointsVisible(false);
            raz2->setPointsVisible(false);
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


void MainWindow::on_radioButton_3_clicked(bool checked)
{
    if (checked)
    {
        ui->graphicsView->setChart(chart1);
    }
}


void MainWindow::on_radioButton_4_clicked(bool checked)
{
    if (checked)
    {
        ui->graphicsView->setChart(chartRaz1);
    }
}


void MainWindow::on_radioButton_clicked(bool checked)
{
    if (checked)
    {
        ui->graphicsView_2->setChart(chart2);
    }
}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if (checked)
    {
        ui->graphicsView_2->setChart(chartRaz2);
    }
}

