#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "handler.h"
#include <assert.h>
#include <QRegularExpression>

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
    void on_radioButtonXOR_clicked();

    void on_radioButtonAND_clicked();

    void on_radioButtonOR_clicked();

    void on_pushButtonRrocedure_clicked();

    void on_lineEditValue_textChanged(const QString &arg1);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
