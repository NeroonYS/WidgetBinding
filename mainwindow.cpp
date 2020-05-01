#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QStringList>
#include <QHBoxLayout>
#include <QLineEdit>

#include "Params.h"

void MainWindow::onBtnClicked() {
//    if( QPushButton* btn = qobject_cast< QPushButton* >( sender() ) ) {
//        if (QTreeWidgetItem *trItem = qobject_cast<QTreeWidgetItem*>(btn->parent()))
//        {
//            QVariant qparam = trItem->data(1, Qt::UserRole);
//            if(qparam.canConvert<ParamDescription<int> *>())
//                if( QSpinBox* sb = btn->parent()->findChild< QSpinBox* >() ) {
//                    sb->setValue(qparam.value<ParamDescription<int> *>()->defValue );
//        }


//        }
//    }
}

template<typename T>
QWidget *CreateEditWidget(ParamDescription<T> &param)
{
    return new QLabel("UNKNOWN");
}

QWidget *CreateEditWidget(ParamDescription<int> &param)
{
    if(param.typewidget == "a")
    {
        QSpinBox *sb = new QSpinBox();
        sb->setRange(param.min, param.max);
        sb->setValue(param.value);

        return sb;
    }
    else
    {
        return new QLabel(QString::number(param.defValue));
    }
}

QWidget *CreateEditWidget(ParamDescription<double> &param)
{
    QWidget *tmpW1 = new QWidget();
    QHBoxLayout *tmpH1 = new QHBoxLayout();
    QLabel *tmpLabel = new QLabel(QString::number(param.defValue));

    QSlider *tmpSlider = new QSlider(Qt::Horizontal);
    tmpSlider->setMinimum(param.min);
    tmpSlider->setMaximum(param.max);
    tmpSlider->setValue(param.value);

    tmpH1->addWidget(tmpSlider);
    tmpH1->addWidget(tmpLabel);
    tmpW1->setLayout(tmpH1);

    //??? сконектить для изменений
//    QObject::connect(tmpSlider, &QSlider::valueChanged, this, [=] () {
//        tmpLabel->setText(QString::number(tmpSlider->value()));

    return tmpW1;
}

QWidget *CreateEditWidget(ParamDescription<QString> &param)
{
    QLineEdit *led = new QLineEdit(param.value);

    return led;
}


template<typename T>
void MainWindow::AddParamToView(ParamDescription<T> &param)
{      
    QStringList itemValues;
    itemValues << param.nameEN << ""<< "";

    EditTreeWidgetItem<T> *trItem = new EditTreeWidgetItem<T>((QTreeWidget*)NULL,itemValues);
    ui->treeWidget->addTopLevelItem(trItem);

    trItem->AddParamToView(param);

    return;

}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    ui->setupUi(this);

    ParamDescription<int> descrInt;
    descrInt.nameEN = "Int val";
    descrInt.min = 0;
    descrInt.max = 100;
    descrInt.value = 1;
    descrInt.defValue = 1;
    descrInt.typewidget = "a";

    ParamDescription<int> descrInt2;
    descrInt2.nameEN = "Int unk widget";
    descrInt2.min = 0;
    descrInt2.max = 100;
    descrInt2.value = 5;
    descrInt2.defValue = 5;
    descrInt2.typewidget = "sss";

    ParamDescription<double> descrD;
    descrD.nameEN = "Double val";
    descrD.min = -50;
    descrD.max = 50;
    descrD.value = 0.01;
    descrD.defValue = 0.01;
    descrD.typewidget = "b";

    ParamDescription<QString> descrS;
    descrS.nameEN = "String val";
    descrS.min = "";
    descrS.max = "";
    descrS.value = "PATH";
    descrS.defValue = "PATH";
    descrS.typewidget = "c";

    AddParamToView(descrInt);
    AddParamToView(descrInt2);
    AddParamToView(descrD);
    AddParamToView(descrS);

}

MainWindow::~MainWindow()
{
    delete ui;
}

template<class T>
void EditTreeWidgetItem<T>::AddParamToView(ParamDescription<T> &param)
{
    QWidget *edWdg = CreateEditWidget(param);
    QPushButton *btn = new QPushButton("Reset");

    this->param = &param;
    //connect( btn, SIGNAL( clicked() ), SLOT( onBtnClicked() ) );

    if(treeWidget())
    {
        treeWidget()->setItemWidget(this,1,edWdg);
        treeWidget()->setItemWidget(this,2,btn);
    }
}


