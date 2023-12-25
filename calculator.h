#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QGroupBox>
#include <QEvent>
#include <QKeyEvent>
#include <cmath>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGridLayout *mainLayout;

    QPushButton *digitButtons[10];
    QPushButton *addButton;
    QPushButton *clearButton;
    QPushButton *equalsButton; // Кнопка "="
    QPushButton *multiplyButton; // Кнопка "*"
    QPushButton *dotButton; // Кнопка "/"
    QPushButton *subtractButton; // Кнопка "-"
    QPushButton *divisionButton; // Кнопка "-"
    QPushButton *logButton;

    QLabel *displayLabel; // Метка для вывода чисел
    QString currentText; // Текущий введенный текст

    double firstOperand; // Первое слагаемое
    double secondOperand; // Первое слагаемое
    double result; // Первое слагаемое
    bool waitingForOperand; // Флаг ожидания второго слагаемого после операции


    enum class Operation {
        None,
        Add,
        Multiply,
        Subtract,
        Division,
        Log
    };

    Operation currentOperation;

//
private slots:
    void digitClicked();
    void keyDigitClicked(int digit);
    void addButtonClicked();
    void multiplyButtonClicked();
    void subtractButtonClicked();
    void divisionButtonClicked();
    void dotButtonClicked();
    void clearButtonClicked();
    void logButtonClicked();
    void equalsButtonClicked(); // Новый слот для кнопки "="
    void updateDisplay();
};

#endif // CALCULATOR_H
