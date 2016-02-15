#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // set the constraint on the spin box
    ui->_number->setMaximum(10000);
    ui->_cycle->setMaximum(1000);
    // set the default value of the spin box
    ui->_number->setValue(1000);
    ui->_cycle->setValue(20);

    // change the digram setting
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("variance S");
    ui->customPlot->yAxis->setLabel("BER(in %)");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, 1);
    ui->customPlot->yAxis->setRange(0, 30);
    ui->customPlot->legend->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MakePlot(QVector<double> x, QVector<double> y, QVector<double> z)
{
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    // max product
    ui->customPlot->graph(0)->setName("Max-Product");
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->addGraph();
    // sum product
    ui->customPlot->graph(1)->setName("Sum-Product");
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot->graph(1)->setData(x, z);
    ui->customPlot->replot();
}

void MainWindow::on_pushButton_clicked()
{

    // set the number and the cycle value of the algorithm
    if(ui->_number->value() == 0 || ui->_cycle->value() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("number and cycle should not be empty");
        msgBox.exec();

    } else {

        decode->_num = ui->_number->value();
        decode->_cycle = ui->_cycle->value();

        QVector<double> x;
        QVector<double> y;
        QVector<double> z;
        for (int i = 8; i >= 1 ; i = i/2)
        {
            decode->setVariance(1.0/i);
            decode->run();
            double max_result = decode->getMaxResult();
            double sum_result = decode->getSumResult();

            // set the x and y value
            x.push_back(1.0/i);
            y.push_back(max_result);
            z.push_back(sum_result);

        }

        //remove the previous graph
        ui->customPlot->clearGraphs();

        // draw the diagram
        MakePlot(x,y,z);
    }

}
