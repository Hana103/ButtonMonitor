#ifndef GPIO_H
#define GPIO_H

#include <QObject>

class gpio : public QObject
{
    Q_OBJECT
public:
    explicit gpio(QObject *parent = nullptr); // constructor
    ~gpio(); // destructor for clean-up
    void set(int pin, bool value);
    void set(unsigned int pattern);
    bool get(int pin);

    bool edgeDetect(int state, bool edge, int nr); // falling || rising


private:
    int m_handle;

    QList<bool> m_oldstates={true, true, true}; // buttons=H



};

#endif // GPIO_H
