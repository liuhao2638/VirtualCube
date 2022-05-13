#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //启用鼠标跟踪
    setMouseTracking(true);

    //设置菜单栏，一个菜单列，两个菜单项。
    menuBar = new QMenuBar;
    menu = menuBar->addMenu(tr("菜单"));
    aboutAction = new QAction(menu);
    aboutAction->setText(tr("关于我们"));
    menu->addAction(aboutAction);

    getTutorialAction = new QAction(menu);
    getTutorialAction->setText(tr("获取教程"));
    menu->addAction(getTutorialAction);

    setMenuBar(menuBar);

    setWindowTitle(tr("虚拟魔方"));
    resize( QSize( 900, 600 ));
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);

    connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));
    connect(getTutorialAction,SIGNAL(triggered()),this,SLOT(getTutorial()));
}

MainWindow::~MainWindow()
{

}
void MainWindow::getTutorial()
{
     QDesktopServices::openUrl(QUrl("https://rubiks.com/", QUrl::TolerantMode));
}
void MainWindow::about()
{
     QDesktopServices::openUrl(QUrl("https://github.com/liuhao2638/VirtualCube", QUrl::TolerantMode));
}
