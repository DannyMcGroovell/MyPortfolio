#include "handler.h"


Handler::Handler(QWidget *parent)
    : QMainWindow{parent}
{

}
QVector<QVector<QString>> Handler::SearchFiles(QString dir, QString patternV){
    QVector<QVector<QString>> res;
    QVector<QString>fileName;
    QVector <QString> filePath;
    if(pattern[0]=='.')
        patternV = '*'+patternV;
    if(patternV[patternV.size()-1]=='.')
        patternV = patternV + '*';
    QDirIterator iter(dir, QStringList() << patternV, QDir::Files);
    while(iter.hasNext()){
        iter.next();
        QString file = iter.filePath();
        filePath.emplaceBack(file);
        fileName.emplaceBack(iter.fileName());
    }
    res.emplaceBack(fileName);
    res.emplaceBack(filePath);
    return res;
}

void Handler::ReadWriteFile(QString fileName, QString filePath){
    QFile fileIn(filePath);
    textDebug = "";
    if(fileIn.isOpen()){
        textDebug+=("Error:file "+fileName+" is already open.");
        return;
    }
    fileIn.open(QIODevice::ReadOnly);
    if(!rewriteNew){
        fileName = NewFileName(fileName);
    }
    if(resultDirectroy[resultDirectroy.size()-1]!='/')
        resultDirectroy += "/";
    QFile fileOut(resultDirectroy+fileName);
    if(!fileOut.open(QIODevice::WriteOnly)){
        textDebug+=("Error: writing file "+ fileName);
    }
    while(!fileIn.atEnd()){
        QByteArray sourceByte;
        textDebug+="\nreading fileIn ";
        sourceByte = fileIn.read(8);
        textDebug+="\nRead 8 byte";
        QByteArray bValue = value.toLocal8Bit();
        bValue = bValue.toHex();
        QString sourceStr = QString::number(sourceByte.toULongLong(nullptr, 16), 2).toLocal8Bit();
        QString binValue = QString::number(bValue.toULongLong(nullptr, 16), 2).toLocal8Bit();
        QString resValue = BinaryOperationAction(sourceStr, binValue);
        QByteArray rawData = QByteArray::fromHex(QString::number(resValue.toULongLong(0,2), 16).toLocal8Bit());
        fileOut.write(rawData);
        }

    fileIn.close();
    fileOut.close();
    if(deleteEntering){
        QFile::remove(filePath);
    }
}

QString Handler::NewFileName(QString fileName){
    int lastDot = fileName.lastIndexOf(".");
    QString fName;
    QString fExt;
    fExt = "";
    if(lastDot!=-1){
        fName = fileName.mid(0, fileName.size()-(fileName.size()-lastDot));
        fExt = fileName.mid(lastDot, fileName.size()-lastDot);
    }else
        fName = fileName;
    qsizetype l;
    if(fName!='*'){

    for(l = fName.size()-1; l < fName.size(); --l){
        if(fName[l].isDigit()){
            continue;
        }
        else
            break;
    }
    fName = fName.mid(0, fName.size()-(fName.size()-l-1));
    fName;
    }
    int maxSeq = 0;
    QVector<QVector<QString>> f = SearchFiles(resultDirectroy, fName+"*"+fExt);
    for(int i = 0; i < f[0].size(); i++){
    lastDot = f[0][i].lastIndexOf(".");
    fExt = "";
    if(lastDot!=-1){
        fName = f[0][i].mid(0, f[0][i].size()-(f[0][i].size()-lastDot));
        fExt = f[0][i].mid(lastDot, f[0][i].size()-lastDot);
    }else
        fName = f[0][i];
    int sequenceNumber = 0;
    int pos = 1;
    for(l = fName.size()-1; l < fName.size(); --l){
        if(fName[l].isDigit()){
            sequenceNumber += pos * fName[l].digitValue();
            pos = pos * 10;
        }
        else
            break;
    }
    maxSeq = (maxSeq > sequenceNumber)? maxSeq:sequenceNumber;
    fName = fName.mid(0, fName.size()-(fName.size()-l-1));
    }
    maxSeq+=1;
    return QString("%1%2%3").arg(fName).arg(maxSeq, 3, 10, QChar('0')).arg(fExt);
}

QString Handler::BinaryOperationAction(QString a, QString b){
    QString result = "";
    for(qsizetype i = 0; i < a.size(); i++){
        switch(binaryOperation){
        case 1:
            if((a[i].unicode()-48)^(b[i].unicode()-48))
                result+='1';
            else
                result+='0';
            break;
        case 2:
            if((a[i].unicode()-48)&(b[i].unicode()-48))
                result+='1';
            else
                result+='0';
            break;
        case 3:
            if((a[i].unicode()-48)|(b[i].unicode()-48))
                result+='1';
            else
                result+='0';
            break;
        }
    }
    return result;
}
/*
private:
    QString pattern;
    QString baseDirectory;
    QString resultDirectroy;
    bool deleteEntering;
    bool rewriteNew;
    int binaryOperation;
    QTime timeNumber;
    QString value;
    */
