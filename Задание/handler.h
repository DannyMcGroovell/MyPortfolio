#ifndef HANDLER_H
#define HANDLER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTime>
#include <QString>
#include <QFile>
#include <QFileSystemModel>
#include <QDirIterator>
#include <bitset>
#include <QByteArray>
#include <QLocale>
#include <assert.h>

class Handler : public QMainWindow
{
    Q_OBJECT
public:
    explicit Handler(QWidget *parent = nullptr);
public:
    QString pattern;
    QString baseDirectory;
    QString resultDirectroy;
    bool deleteEntering;
    bool rewriteNew;
    int binaryOperation;
    QString textDebug;
    QTime timeNumber;
    QString value;
    void binaryOperationFunc(int binOp){
        binaryOperation = binOp;
    }
   QVector<QVector<QString>> SearchFiles(QString dir, QString patternV);
   void ReadWriteFile(QString fileName, QString filePath);
   QString NewFileName(QString fileName);
   std::string strToBin(std::string str);
   QString BinaryOperationAction(QString a, QString b);
signals:

};

#endif // HANDLER_H
