#ifndef CALCTEST2_H
#define CALCTEST2_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CalcTest2; }
QT_END_NAMESPACE

class CalcTest2 : public QMainWindow
{
    Q_OBJECT

public:
    CalcTest2(QWidget *parent = nullptr);
    ~CalcTest2();

private:
    Ui::CalcTest2 *ui;

private slots:
    void NumPressed();         // цифра
    void PointPressed();       // десятичный разделитель
    void MathButtonPressed();  // бинарная функция (+, -, *, / и x^y)
    void EqualButtonPressed(); // вывод результата
    void ChangeNumberSign();   // смена знака
    void BackspacePressed();   // отмена
    void ClearEntryPressed();  // очистка
    void SquarePressed();      // возведение в квадрат
    void ReciprocalPressed();  // дробь (1/x)
    void SquareRootPressed();  // извлечение квадр. корня
    void SinPressed();         // синус
    void CosPressed();         // косинус
    void ExpPressed();         // экспонен. функция
    void NatLogPressed();      // натур. логарифм
    void CeilPressed();        // округление в большую сторону
    void FloorPressed();       // округление в меньшую сторону
    void PercentPressed();     // проценты
};
#endif // CALCTEST2_H
