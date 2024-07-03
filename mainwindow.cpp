/*
The Calculator
Creator: Hermes Neri
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->pushButton_Pos_Negat, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_Percentual, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

    connect(ui->pushButton_Sum, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_Subt, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_Multipl, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_Divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

    ui->pushButton_Sum->setCheckable(true);
    ui->pushButton_Subt->setCheckable(true);
    ui->pushButton_Divide->setCheckable(true);
    ui->pushButton_Multipl->setCheckable(true);
    //connect(ui->pushButton_C, SIGNAL(released()), this, SLOT(on_pushButton_clear_released()));'

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_Sum->isChecked()
        || ui->pushButton_Subt->isChecked()
        || ui->pushButton_Multipl->isChecked()
         || ui->pushButton_Divide->isChecked())
        && (!userIsTypingSecondNumber))
    {
        labelNumber =button->text().toDouble();
        userIsTypingSecondNumber = true;
        newLabel = QString::number(labelNumber,'g', 15); //(nome da label, _, qtde de casas)
    }
    else
    {
        if(ui->label_Result->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->label_Result->text() + button->text();
        }
        else
        {
            labelNumber = (ui->label_Result->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber,'g', 15); //(nome da label, _, qtde de casas)
        }
    }
    ui->label_Result->setText(newLabel); //Mostra o texto da tecla pressionada na label_Result
}

void MainWindow::on_pushButton_Comma_released()
{
    ui->label_Result->setText(ui->label_Result->text() + ".");
}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    if(button->text() == "+/-")
    {
        labelNumber = ui->label_Result->text().toDouble();
        labelNumber = (labelNumber * (-1));
        newLabel = QString::number(labelNumber, 'g', 15); //(nome da label, _, qtde de casas)
        ui->label_Result->setText(newLabel);
    }

    if(button->text() == "%")
    {
        labelNumber = ui->label_Result->text().toDouble();
        labelNumber = (labelNumber * (.01));
        newLabel = QString::number(labelNumber, 'g', 15); //(nome da label, _, qtde de casas)
        ui->label_Result->setText(newLabel);
    }
}

void MainWindow::on_pushButton_C_released()
{
    ui->pushButton_Sum->setChecked(false);
    ui->pushButton_Subt->setChecked(false);
    ui->pushButton_Multipl->setChecked(false);
    ui->pushButton_Divide->setChecked(false);

    userIsTypingSecondNumber = false;

    ui->label_Result->setText("0");

}

void MainWindow::on_pushButton_Equal_released()
{
    double labelNumber, secondNum;
    QString newLabel;
    secondNum = ui->label_Result->text().toDouble();

    if(ui->pushButton_Sum->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_Result->setText(newLabel);
        ui->pushButton_Sum->setChecked(false);
    }

    else if(ui->pushButton_Subt->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_Result->setText(newLabel);
        ui->pushButton_Subt->setChecked(false);
    }

    else if(ui->pushButton_Multipl->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_Result->setText(newLabel);
        ui->pushButton_Multipl->setChecked(false);
    }

    else if(ui->pushButton_Divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_Result->setText(newLabel);
        ui->pushButton_Divide->setChecked(false);
    }

    userIsTypingSecondNumber = false;
}

void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui->label_Result->text().toDouble();

    button->setChecked(true);

}

