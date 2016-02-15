#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include "decoding.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void MakePlot(QVector<double> x, QVector<double> y, QVector<double> z);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Decoding *decode = new Decoding();
};

#endif // MAINWINDOW_H
