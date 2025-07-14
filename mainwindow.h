#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtGlobal>
#include <QMessageBox>
#include <QTextStream>

extern float currency_rate[10];

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
    void Convert(qint32 currency_1, qint32 currency_2);

private slots:
    void on_Convert_PushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
