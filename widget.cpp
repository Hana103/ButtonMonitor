#include "config.h"
#include "widget.h"
#include <QGridLayout>
#include <QDebug>
#include <QRandomGenerator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // Widget s &QTimer::timeouttructure

    setWindowTitle("ButtonMonitor");
    resize(300, 100);
    QGridLayout* grid = new QGridLayout(this);
    setLayout(grid);

    // Labels for input pins / buttons

    int column = 0;


    for (auto pin : BUTTONS)
    {
        // pin numbers

        QLabel* label = new QLabel("GPIO " + QString::number(pin), this);
        label->setAlignment(Qt::AlignCenter);
        grid->addWidget(label, 0, column); // links oben (1. Zeile / 1. - 3. Spalte)

        // pin states

        QLabel* state = new QLabel("0", this);
        state->setAlignment(Qt::AlignCenter);
        grid->addWidget(state, 1, column++); // links oben (2. Zeile / 1. - 3. Spalte)
        m_input_display.push_back(state);
    }
    // QLabel for counter

    m_countLabel= new QLabel("Counter: 0",this);
    m_countLabel->setAlignment(Qt::AlignCenter);

    grid->addWidget(m_countLabel,2,1);

    // initialize hardware

    m_gpio = new gpio();

    m_timer = new QTimer(this);

    // Connect QTimer (Signal) with GUI function (Slot) "update display"

    connect(m_timer, &QTimer::timeout, this, &Widget::updateButtonState);
    m_timer->start(T_UPDATE);
}

Widget::~Widget()
{

}

void Widget::updateButtonState()
{
    int n = 0;

    for (auto pin : BUTTONS)
    {
        int state = !m_gpio->get(pin);  // inverts the value of the button (at the beginning all the buttons are HIGH)

        if(m_gpio->edgeDetect(state,true,n))
        {
            if(n==0)
            {
                m_counter--;   // GPIO22-> cnt--
                m_number= qrand()%((6+1)-0)+0;
                qDebug() <<m_number;
                m_gpio->set(m_number);
            }
            else if(n==1)
            {
                m_counter=0;    // GPIO27-> cnt=0
                m_number= qrand()%((6+1)-0)+0;
                qDebug() <<m_number;
                m_gpio->set(m_number);
            }
            else if(n==2)
            {
                m_counter++;    // GPIO17-> cnt++
                m_number= qrand()%((6+1)-0)+0;
                qDebug() <<m_number;
                m_gpio->set(m_number);
            }
        }

        m_countLabel->setText("Counter: "+ QString::number(m_counter));
        m_input_display[n++]->setText(QString::number(state));
    }
}
