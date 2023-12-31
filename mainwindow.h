#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QVector>
#include"datalistener.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered(bool checked);

    void on_actionWave_Viewer_triggered(bool checked);


private:
    Ui::MainWindow *ui;
    DataListener *data;//*
};
#endif // MAINWINDOW_H
