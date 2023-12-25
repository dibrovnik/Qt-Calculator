//#include "widget.h"


//Widget::Widget(QWidget *parent)
//    : QWidget(parent)
//{
//    btn1 = new QPushButton("Constructor", this);
//            btn1->setGeometry(5,5,120,40);
//    btn2 = new QPushButton("Destructor", this);
//            btn2->setGeometry(130,5,120,40);

//    connect(btn1, SIGNAL(clicked()), this, SLOT(slot_createLabel()), Qt::DirectConnection);
//    connect(btn2, SIGNAL(clicked()), this, SLOT(slot_destroyLabel()), Qt::DirectConnection);
//}

//Widget::~Widget()
//{
//}

//void Widget::slot_createLable()
//{
//    if (lbl1 == nullptr)
//    {
//        lbl1 = new QLabel("Label 1", this);
//            lbl1->setGeometry(5, 50, 60, 30);
//            lbl1 ->show();
//    }
//}

//void Widget::slot_destroyLable()
//{
//    if ( lbl1!=nullptr)
//    {
//        delete lbl1;
//        lbl1 = nullptr;
//    }
//}


#include "widget.h"
#include "QDebug"
#include "QObject"
#include "QWidget"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);

    // Создаем кнопки
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QPushButton *button = new QPushButton(QString("Button %1").arg(row * 3 + col + 1), this);
            connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
            layout->addWidget(button, row, col);
        }
    }

    setLayout(layout);
}

void Widget::buttonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton)
        qDebug() << "Button clicked:" << clickedButton->text();
}
