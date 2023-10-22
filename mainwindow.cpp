#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),data(new DataListener(this))
{
    ui->setupUi(this);
    ui->widget->xAxis->setRange(0,4096);
    ui->widget->yAxis->setRange(-32767,32767);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete data;
}


void MainWindow::on_actionAbout_triggered(bool checked)
{
    if(!checked){
        QMessageBox::about(this,"About","Developer: Igor Sapunov\nSoftware version: For show skils\n2023year");
    }
}


void MainWindow::on_actionWave_Viewer_triggered(bool checked)
{
if(!checked){
    data->setCallback([this](const QVector<double>& data) {
        QVector<double>x;
        x.reserve(4096);
        for(double i=0;i<4096;++i){
            x.push_back(i);
        }
        ui->widget->addGraph();
        ui->widget->graph(0)->setData(x,data);
        QVector<double>sort_y;
        sort_y.reserve(4096);
        sort_y=data;
        qSort(sort_y);
        double median=sort_y[data.size()/2];
        QVector<double> medians(4096, median);

        ui->widget->addGraph();
        ui->widget->graph(1)->setPen(QPen(Qt::red));
        ui->widget->graph(1)->setData(x,medians);
        ui->widget->replot();
        ui->statusbar->showMessage("Maximum: "+QString::number(*sort_y.rbegin())+" Median: "+QString::number(median));
 });


}
}







