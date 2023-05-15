#include "calctest2.h"
#include "ui_calctest2.h"
#include "qmath.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool powTrigger = false;

CalcTest2::CalcTest2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalcTest2)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; ++i)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = CalcTest2::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Pow, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->ButtonPoint, SIGNAL(released()), this,
            SLOT(PointPressed()));
    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    connect(ui->Square, SIGNAL(released()), this,
            SLOT(SquarePressed()));
    connect(ui->Reciprocal, SIGNAL(released()), this,
            SLOT(ReciprocalPressed()));
    connect(ui->SquareRoot, SIGNAL(released()), this,
            SLOT(SquareRootPressed()));
    connect(ui->Sin, SIGNAL(released()), this,
            SLOT(SinPressed()));
    connect(ui->Cos, SIGNAL(released()), this,
            SLOT(CosPressed()));
    connect(ui->Exp, SIGNAL(released()), this,
            SLOT(ExpPressed()));
    connect(ui->NatLog, SIGNAL(released()), this,
            SLOT(NatLogPressed()));
    connect(ui->Ceil, SIGNAL(released()), this,
            SLOT(CeilPressed()));
    connect(ui->Floor, SIGNAL(released()), this,
            SLOT(FloorPressed()));
    connect(ui->Percent, SIGNAL(released()), this,
            SLOT(PercentPressed()));

    connect(ui->Backspace, SIGNAL(released()), this,
            SLOT(BackspacePressed()));
    connect(ui->ClearEntry, SIGNAL(released()), this,
            SLOT(ClearEntryPressed()));
}

CalcTest2::~CalcTest2()
{
    delete ui;
}

void CalcTest2::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if ((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    } else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void CalcTest2::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    powTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    } else {
        powTrigger = true;
    }
    ui->Display->setText("");
}

void CalcTest2::EqualButtonPressed(){
    double solution = 0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || multTrigger || divTrigger || powTrigger){
        if (addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if (subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if (multTrigger){
            solution = calcVal * dblDisplayVal;
        } else if (divTrigger){
            solution = calcVal / dblDisplayVal;
        } else {
            solution = qPow(calcVal, dblDisplayVal);
        }
    }
    ui->Display->setText(QString::number(solution));
}

void CalcTest2::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void CalcTest2::SquarePressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = dblDisplayVal * dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::ReciprocalPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = 1 / dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::SquareRootPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = qSqrt(dblDisplayVal);
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::ClearEntryPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (dblDisplayVal != 0){
        dblDisplayVal = 0;
        ui->Display->setText(QString::number(dblDisplayVal));
    }
}

void CalcTest2::PointPressed(){
    QString displayVal = ui->Display->text();
    if (!displayVal.contains(".")){
        ui->Display->setText(displayVal + ".");
    }
}

void CalcTest2::BackspacePressed(){
    QString displayVal = ui->Display->text();
    displayVal.chop(1);
    if (displayVal.isEmpty()){
        displayVal = "0";
    }
    ui->Display->setText(displayVal);
}

void CalcTest2::SinPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = qSin(dblDisplayVal);
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::CosPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = qCos(dblDisplayVal);
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::ExpPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = qExp(dblDisplayVal);
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::NatLogPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = qLn(dblDisplayVal);
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::CeilPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = qCeil(dblDisplayVal);
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::FloorPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = qFloor(dblDisplayVal);
    ui->Display->setText(QString::number(dblDisplayVal));
}

void CalcTest2::PercentPressed(){
    double solution = 0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (multTrigger){
        solution = (calcVal / 100) * dblDisplayVal;
    }
    ui->Display->setText(QString::number(solution));
}
