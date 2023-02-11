#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QButtonGroup>
#include <QDebug>
#include "CalculatorModel.h"

class MainWidget : public QWidget
{
    Q_OBJECT
    CalculatorModel * _calculator;
    QLineEdit * _lineEditDisplay;
    QButtonGroup * _buttonGroup;
    bool _displayBase;
public:
    explicit MainWidget(QWidget *parent = nullptr);
public slots :
    void handle(int);
    void baseChanged(int);
    void displaySuffixe(bool);
signals:

};

#endif // MAINWIDGET_H
