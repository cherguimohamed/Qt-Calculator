#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    _calculator = new CalculatorModel();
    _displayBase = false;

    QVBoxLayout * vboxLayout = new QVBoxLayout(this);
    setLayout(vboxLayout);

    QLabel * labelNom = new QLabel(this);
    labelNom->setText("Calculatrice");
    vboxLayout->addWidget(labelNom);

    _lineEditDisplay = new QLineEdit(this);
    _lineEditDisplay->setAlignment(Qt::AlignRight);
    _lineEditDisplay->setReadOnly(true);
    vboxLayout->addWidget(_lineEditDisplay);

    QGridLayout * gridLayout = new QGridLayout(this);
    vboxLayout->addItem(gridLayout);
    gridLayout->setVerticalSpacing(5);
    gridLayout->setHorizontalSpacing(5);

    _buttonGroup = new QButtonGroup(this);

    QString buttonsText = "0123456789ABCDEF.+-/*=";
    Qt::Key shortcuts[22] = {Qt::Key_0, Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4, Qt::Key_5, Qt::Key_6, Qt::Key_7, Qt::Key_8, Qt::Key_9, Qt::Key_A, Qt::Key_B, Qt::Key_C, Qt::Key_D, Qt::Key_E, Qt::Key_F, Qt::Key_Period, Qt::Key_Plus, Qt::Key_Minus, Qt::Key_Slash, Qt::Key_Asterisk, Qt::Key_Equal};
    int buttonsPosition[22][2] = {{5,0}, {4,0}, {4,1}, {4,2}, {3,0}, {3,1}, {3,2}, {2,0}, {2,1}, {2,2}, {1,0}, {1,1}, {1,2}, {1,3}, {0,0}, {0,1}, {5,1}, {2,3}, {3,3}, {4,3}, {5,3}, {5,2}};
    for (int i = 0; i<22; i++) {
        QPushButton * button = new QPushButton(this);
        button->setText(buttonsText.at(i));
        button->setShortcut(QKeySequence(shortcuts[i]));
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        gridLayout->addWidget(button, buttonsPosition[i][0], buttonsPosition[i][1]);
        _buttonGroup->addButton(button);
    }

    QLabel * labelBase = new QLabel("Base", this);
    labelBase->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    gridLayout->addWidget(labelBase, 0, 2);

    QComboBox * comboBoxBase = new QComboBox(this);
    comboBoxBase->addItems({"Dec", "Hex", "Bin"});
    comboBoxBase->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    gridLayout->addWidget(comboBoxBase, 0, 3);
    connect(comboBoxBase, SIGNAL(currentIndexChanged(int)), this, SLOT(baseChanged(int)));


    QPushButton * clearButton = new QPushButton(this);
    clearButton->setText("C");
    clearButton->setShortcut(QKeySequence(Qt::Key_Delete));
    vboxLayout->addWidget(clearButton);
    _buttonGroup->addButton(clearButton);

    connect(_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(handle(int)));

    QPushButton * quitButton = new QPushButton(this);
    quitButton->setText("Quit");
    vboxLayout->addWidget(quitButton);
    connect(quitButton, SIGNAL(clicked()), parent, SLOT(quitApp()));
    baseChanged(0);
}

void MainWidget::handle(int id)
{
    _calculator->command(CalculatorModel::ButtonID((abs(id)-2)));
    if(_displayBase) {
        if(_calculator->base() == _calculator->Bin) {
            _lineEditDisplay->setText(_calculator->getText() + "b");
        } else if (_calculator->base() == _calculator->Hex) {
            _lineEditDisplay->setText(_calculator->getText() + "h");
        } else {
            _lineEditDisplay->setText(_calculator->getText());
        }
    } else {
        _lineEditDisplay->setText(_calculator->getText());
    }
}

void MainWidget::baseChanged(int index)
{
    int buttonEnabled[22][3] = {{1,1,1},{1,1,1},{1,1,0},{1,1,0},{1,1,0},{1,1,0},{1,1,0},{1,1,0},{1,1,0},{1,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{1,0,0},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}};
    for (int i=0; i< 22; i++) {
        _buttonGroup->buttons()[i]->setEnabled(buttonEnabled[i][index]);
    }
    switch(index) {
    case 0 :
        _calculator->setBase(CalculatorModel::Dec);
        break;
    case 1 :
        _calculator->setBase(CalculatorModel::Hex);
        break;
    case 2 :
        _calculator->setBase(CalculatorModel::Bin);
        break;
    }
}

void MainWidget::displaySuffixe(bool checked)
{
    _displayBase = checked;
    if(checked && _calculator->base() == _calculator->Bin) {
        _lineEditDisplay->setText(_calculator->getText() + "b");
    } else if(!checked && _calculator->base() == _calculator->Bin) {
        _lineEditDisplay->setText(_calculator->getText());
    } else if(checked && _calculator->base() == _calculator->Hex) {
        _lineEditDisplay->setText(_calculator->getText() + "h");
    } else if(!checked && _calculator->base() == _calculator->Hex) {
        _lineEditDisplay->setText(_calculator->getText());
    }
}
