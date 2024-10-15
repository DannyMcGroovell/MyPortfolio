#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handler.h"


Handler * settings;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    settings = new Handler();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButtonXOR_clicked()
{
        ui->radioButtonAND->setChecked(false);
        ui->radioButtonOR->setChecked(false);
        settings->binaryOperationFunc(1);
}


void MainWindow::on_radioButtonAND_clicked()
{
        ui->radioButtonXOR->setChecked(false);
        ui->radioButtonOR->setChecked(false);
        settings->binaryOperationFunc(2);
}


void MainWindow::on_radioButtonOR_clicked()
{
        ui->radioButtonAND->setChecked(false);
        ui->radioButtonXOR->setChecked(false);
        settings->binaryOperationFunc(3);
}



void MainWindow::on_pushButtonRrocedure_clicked()
{
    settings->pattern = ui->lineEditPattern->text();
    settings->baseDirectory = ui->lineEditDirectory->text();
    settings->resultDirectroy = ui->lineEditResultDirectroy->text();
    settings->deleteEntering = ui->checkBoxDeleteEntering->isChecked();
    settings->rewriteNew = ui->checkBoxRewrite->isChecked();
    settings->value = ui->lineEditValue->text();
    settings->timeNumber = ui->timeEdit->time();

ui->textEditDebug->append("Process...");
QVector<QVector<QString>> fData = settings->SearchFiles(settings->baseDirectory, settings->pattern);
for(int i = 0; i < fData[0].size(); i++){
    ui->textEditDebug->append("Pending " + fData[0][i] + " " + fData[1][i]);
    settings->ReadWriteFile(fData[0][i], fData[1][i]);
    ui->textEditDebug->append(settings->textDebug);
}
}


void MainWindow::on_lineEditValue_textChanged(const QString &arg1)
{
    QRegularExpression re ("^[A-Za-z0-9]+$");
    QValidator *validator = new QRegularExpressionValidator(re, this);
    ui->lineEditValue->setValidator(validator);
}

