#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtGlobal>
#include <QString>
#include <QFile>

float currency_rate[10] = {0.849,0.7324,144.56,3.2726,0.8627,170.28,3.8548,197.38,4.4684, 0.0226};
// Элементы массива (курсы): USD-EUR, USD-GBP, USD-JPY, USD-BYN, EUR-GBP, EUR-JPY, EUR-BYN, GBP-JPY, GBP-BYN, JPY-BYN

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->money_after_conversion->setReadOnly(true);
    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(ui->verticalLayoutWidget);
}

MainWindow::~MainWindow()
{
    delete ui;

    QFile file("Result.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.resize(0);
        file.close();
    }
    else
    {
        QMessageBox::StandardButton message = QMessageBox::warning(this,"Предупреждение","Не удалось открыть файл Result.txt",QMessageBox::Ok);
    }

}

void MainWindow::Convert(qint32 currency_1, qint32 currency_2)
{
    QString str;
    str = ui->money_before_conversion->text();
    qint32 result = str.toInt();
    if(result < 0)
    {
        QMessageBox::StandardButton reply = QMessageBox::warning(this,"Предупреждение","Отрицательное число не может быть использовано в качестве денежной суммы.",QMessageBox::Ok);
        if(reply == QMessageBox::Ok)
        {
            ui->money_before_conversion->setText("");
            ui->money_after_conversion->setText("");
            return;
        }
    }
    qint32 index = 0;

    if (currency_1 == currency_2)
    {
        result = result * 1;
    }

    else if(currency_1 < currency_2)
    {
        int i = 0;
        while(i < currency_1)
        {
            index = index + 5 - i -1;
            i=i+1;
        }
        index = index + (currency_2 - currency_1 -1);
        result = result * currency_rate[index];
    }

    else if(currency_1 > currency_2)
    {
        int temp = currency_1;
        currency_1 = currency_2;
        currency_2 = temp;
        int i = 0;
        while(i < currency_1)
        {
            index = index + 5 - i -1;
            i=i+1;
        }
        index = index + (currency_2 - currency_1 -1);
        result = result / currency_rate[index];
    }

    ui->money_after_conversion->setText(QString::number(result));

    QFile file("Result.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << QString::number(result);
        file.close();
    }
    else
    {
        QMessageBox::StandardButton message = QMessageBox::warning(this,"Предупреждение","Не удалось открыть файл Result.txt",QMessageBox::Ok);
    }

}

void MainWindow::on_Convert_PushButton_clicked()
{
    qint32 currency_1 = ui->Currency_ComboBox_1->currentIndex();
    qint32 currency_2 = ui->Currency_ComboBox_2->currentIndex();
    Convert (currency_1, currency_2);
}
