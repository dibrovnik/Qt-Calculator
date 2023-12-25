#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), firstOperand(0), waitingForOperand(false)
{
    mainLayout = new QGridLayout(this);

    // Создаем кнопки цифр
    for (int i = 0; i < 10; ++i) {
        digitButtons[i] = new QPushButton(QString::number(i), this);
        connect(digitButtons[i], SIGNAL(clicked()), this, SLOT(digitClicked()));
    }
    setWindowTitle("Калькулятор");
    // Создаем кнопку "+"
    addButton = new QPushButton("+", this);
    connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));

    //Создаем новую кнопку
    clearButton = new QPushButton("Clear", this);
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));

    // Создаем кнопку "="
    equalsButton = new QPushButton("=", this);
    connect(equalsButton, SIGNAL(clicked()), this, SLOT(equalsButtonClicked()));

    // Создаем кнопку "*"
    multiplyButton = new QPushButton("*", this);
    connect(multiplyButton, SIGNAL(clicked()), this, SLOT(multiplyButtonClicked()));

    // Создаем кнопку "."
    dotButton = new QPushButton(".", this);
    connect(dotButton, SIGNAL(clicked()), this, SLOT(dotButtonClicked()));

    // Создаем кнопку "-"
    subtractButton = new QPushButton("-", this);
    connect(subtractButton, SIGNAL(clicked()), this, SLOT(subtractButtonClicked()));

    // Создаем кнопку "/"
    divisionButton = new QPushButton("/", this);
    connect(divisionButton, SIGNAL(clicked()), this, SLOT(divisionButtonClicked()));

    // Создаем кнопку "log10"
    logButton = new QPushButton("log10", this);
    connect(logButton, SIGNAL(clicked()), this, SLOT(logButtonClicked()));

    // Создаем метку для вывода чисел
    displayLabel = new QLabel("0", this);
    displayLabel->setGeometry(10, 10, 200, 30);
    displayLabel->setFrameStyle(QFrame::Box | QFrame::Raised);



    // Размещаем кнопки в сетке
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            int digit = row * 3 + col + 1;
            mainLayout->addWidget(digitButtons[digit], row + 1, col);
        }
    }

    mainLayout->addWidget(digitButtons[0], 4, 0, 1, 3); // добавляем кнопку 0

//----------------Кнопки выбора действия--------------// находятся в 3 столбце

//    1 2 3 +
//    4 5 6 -
//    7 8 9 *
//    c 0 . |


//---------------------------------------------------

    // Добавляем кнопку +
    mainLayout->addWidget(addButton, 0, 3);

    // Добавляем кнопку -
    mainLayout->addWidget(subtractButton, 1, 3);

    // Добавляем кнопку "*" в сетку
    mainLayout->addWidget(multiplyButton, 2, 3);

    // Добавляем кнопку "/" в сетку
    mainLayout->addWidget(divisionButton, 3, 3);

    mainLayout->addWidget(logButton, 4, 3);

//-----------------------------------------------------

    // Добавляем кнопку сброса
    mainLayout->addWidget(clearButton, 0, 3, 1, 1);

    // Кнопка равно посередине
    mainLayout->addWidget(equalsButton, 5, 1, 1, 1);

    // Добавляем кнопку сброса слева от равно
    mainLayout->addWidget(clearButton, 5, 0, 1, 1);

    // Добавляем кнопку "." справа от равно
    mainLayout->addWidget(dotButton, 5, 2);




    // Добавляем метку в сетку
    mainLayout->addWidget(displayLabel, 0, 0, 1, 3);
    QFont font = displayLabel->font();
    font.setPointSize(14);  // Установите желаемый размер шрифта
    displayLabel->setFont(font);
    setLayout(mainLayout);
}

void Calculator::keyPressEvent(QKeyEvent *event)
{
    QString key = event->text();

    if (key >= "0" && key <= "9") {

        keyDigitClicked(key.toInt());
    }
    else if (key == ".") {
        dotButtonClicked();
    } else if (key == "+") {
        addButtonClicked();
    } else if (key == "-") {
        subtractButtonClicked();
    } else if (key == "=" || key == Qt::Key_Enter) {
        equalsButtonClicked();
    } else if (key == "c" || key == "C") {
        clearButtonClicked();
    }
}

void Calculator::updateDisplay()
{
    displayLabel->setText(currentText);
}


// Считывание нажатий кнопок, но без точки
//void Calculator::digitClicked()
//{
//    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
//    if (clickedButton) {
//        int digit = clickedButton->text().toInt();
//        if (waitingForOperand) {
//            currentText = QString::number(digit);
//            waitingForOperand = false;
//        } else {
//            currentText += QString::number(digit);
//        }
//        updateDisplay();
//    }
//}

//void Calculator::digitClicked() // Поддержка ввода точки, но без ввода отрицательных чисел
//{
//    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

//    if (clickedButton) {
//        QString digit = clickedButton->text();

//        if (digit == "0" && currentText == "0") {
//            return; // Избегаем ведущих нулей
//        }

//        if (waitingForOperand) {
//            currentText = digit;
//            waitingForOperand = false;
//        } else {
//            currentText += digit;
//        }

//        updateDisplay();
//    }
//}

void Calculator::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    if (clickedButton) {
        QString digit = clickedButton->text();

        if (digit == "0" && currentText == "0") {
            return; // Избегаем ведущих нулей
        }

        if (waitingForOperand || currentText.isEmpty()) {
            if (digit == "-") {
                currentText = "-";
            } else {
                currentText = digit;
            }
            waitingForOperand = false;
        } else {
            currentText += digit;
        }

        updateDisplay();
    }
}

void Calculator::keyDigitClicked(int digit)
{
    if (waitingForOperand || currentText.isEmpty()) {
        currentText = QString::number(digit);
        waitingForOperand = false;
    } else {
        currentText += QString::number(digit);
    }

    updateDisplay();
}

void Calculator::subtractButtonClicked()
{

   if (currentText.isEmpty())
   {
        currentText = "-";
        updateDisplay();

   }
   else
   {
       if (!waitingForOperand) {
           if (!currentText.isEmpty()) {
               firstOperand = currentText.toDouble();
               waitingForOperand = true;
               currentText.clear();
               updateDisplay();
               currentOperation = Operation::Subtract;
           }
       }
   }
}



void Calculator::dotButtonClicked()
{
    if (!currentText.contains('.')) {
        currentText += '.';
        updateDisplay();
        waitingForOperand = false;
    }
}


void Calculator::addButtonClicked()
{
    if (!waitingForOperand) {
        if (!currentText.isEmpty()) {
            firstOperand = currentText.toDouble();
            waitingForOperand = true;
            currentText.clear();
            updateDisplay();
            currentOperation = Operation::Add;
        }
    }
}


void Calculator::divisionButtonClicked()
{
    if (!waitingForOperand) {
        if (!currentText.isEmpty()) {
            firstOperand = currentText.toDouble();
            waitingForOperand = true;
            currentText.clear();
            updateDisplay();
            currentOperation = Operation::Division;
        }
    }
}

void Calculator::multiplyButtonClicked()
{
    if (!waitingForOperand) {
        if (!currentText.isEmpty()) {
            firstOperand = currentText.toDouble();
            waitingForOperand = true;
            currentText.clear();
            updateDisplay();
            currentOperation = Operation::Multiply;
        }
    }
}

void Calculator::logButtonClicked()
{
    if (!waitingForOperand) {
        if (!currentText.isEmpty()) {
            firstOperand = currentText.toDouble();
            waitingForOperand = true;
            currentText.clear();
            updateDisplay();
            currentOperation = Operation::Log;
        }
    }
}

void Calculator::clearButtonClicked()
{
    currentText.clear();
    firstOperand = 0;
    secondOperand = 0;
    result = 0;
    updateDisplay();
    waitingForOperand = false;
}

void Calculator::equalsButtonClicked()
{
    qDebug() << "equalsButtonClicked. waitingForOperand = " << waitingForOperand;

    if (currentText.isEmpty() == false) {

        secondOperand = currentText.toDouble();
        qDebug() << "Second operand:" << secondOperand;
        switch (currentOperation) {
            case Operation::Add:
                result = firstOperand + secondOperand;
                currentText = QString::number(result);
                qDebug() << result;
                break;
            case Operation::Multiply:
                result = firstOperand * secondOperand;
                currentText = QString::number(result);
                qDebug() << result;
                break;
            case Operation::Subtract:
                result = firstOperand - secondOperand;
                currentText = QString::number(result);
                qDebug() << result;
                break;
            case Operation::Log:
                result = log(firstOperand) / log(secondOperand);
                currentText = QString::number(result);
                qDebug() << result;
                break;
            case Operation::Division:
                if (secondOperand != 0)
                {
                    result = firstOperand / secondOperand;
                    currentText = QString::number(result);
                    qDebug() << result;
                }
                else
                    currentText = "Делить на ноль нельзя!";
                break;

            default:
                break;
        }
        updateDisplay();
        waitingForOperand = false;
        currentOperation = Operation::None;
    }




}



