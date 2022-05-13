#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>

#include <QDesktopServices>
#include <QUrl>

#include "mainwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void getTutorial();
    void about();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    MainWidget *mainWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QAction *aboutAction;
    QAction *getTutorialAction;
};

#endif // MAINWINDOW_H
