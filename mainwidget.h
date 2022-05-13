#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "mainview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:
private slots:
    //调试信号槽
    void debugSlots(QString debugMessage);

private:
    QHBoxLayout *mainLayout;//主布局
        QVBoxLayout *controlLayout;//控制器布局
            QPushButton *resetButton;//重置按钮
            QPushButton *upsetButton;//打乱按钮
            QPushButton *backButton;//退回按钮
            QPushButton *backAllButton;//退回全部按钮
            QPushButton *recoverButton;//还原按钮
            QPushButton *chooseCubeOrderButton;//修改魔方阶数按钮
            QPushButton *openCubeButton;//打开存档按钮
            QPushButton *saveCubeButton;//保存存档按钮
        QVBoxLayout *viewLayout;//图形布局
            MainView *mainView;//图形窗口
        QVBoxLayout *debugLayout;//调试状态栏布局
            QTextEdit *debugTextEdit;//调试文本框
};

#endif // MAINWIDGET_H
