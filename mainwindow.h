#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "Params.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

template<class T>
class EditTreeWidgetItem : public QTreeWidgetItem
{
public:
    EditTreeWidgetItem(QTreeWidget *tree) : QTreeWidgetItem(tree), param(NULL)  {}
    EditTreeWidgetItem(QTreeWidget * parent, const QStringList & strings)
                   : QTreeWidgetItem (parent,strings), param(NULL) {}

    void AddParamToView(ParamDescription<T> &param);
private:
    ParamDescription<T> *param;
};



class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void onBtnClicked();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;

    template<typename T>
    void AddParamToView(ParamDescription<T> &param);
};



#endif // MAINWINDOW_H
