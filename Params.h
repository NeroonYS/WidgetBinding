#ifndef PARAMS_H
#define PARAMS_H

#include <QString>

template<typename T>
class ParamDescription
{
public:
    QString nameEN;
    QString nameRU;
    QString descriptionRU;
    QString descriptionEN;

    T defValue;
    T value;
    T min;
    T max;

    QString typewidget;
};

#endif // PARAMS_H
