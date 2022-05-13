#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    //启用鼠标跟踪
    setMouseTracking(true);

    resetButton = new QPushButton(tr("重置魔方"));
    resetButton->setMinimumSize(0,0);
    resetButton->setMaximumSize(100,1000);

    upsetButton = new QPushButton(tr("打乱魔方"));
    upsetButton->setMinimumSize(0,0);
    upsetButton->setMaximumSize(100,1000);

    chooseCubeOrderButton = new QPushButton("选择阶数");
    chooseCubeOrderButton->setMinimumSize(0,0);
    chooseCubeOrderButton->setMaximumSize(100,1000);

    backButton = new QPushButton(tr("单步后退"));
    backButton->setMinimumSize(0,0);
    backButton->setMaximumSize(100,1000);

    backAllButton = new QPushButton(tr("全部后退"));
    backAllButton->setMinimumSize(0,0);
    backAllButton->setMaximumSize(100,1000);

    recoverButton = new QPushButton(tr("还原魔方"));
    recoverButton->setMinimumSize(0,0);
    recoverButton->setMaximumSize(100,1000);

    openCubeButton = new QPushButton(tr("打开存档"));
    openCubeButton->setMinimumSize(0,0);
    openCubeButton->setMaximumSize(100,1000);

    saveCubeButton = new QPushButton(tr("保存存档"));
    saveCubeButton->setMinimumSize(0,0);
    saveCubeButton->setMaximumSize(100,1000);

    controlLayout = new QVBoxLayout;
    controlLayout->addWidget(resetButton);
    controlLayout->addWidget(upsetButton);
    controlLayout->addWidget(backButton);
    controlLayout->addWidget(backAllButton);
    controlLayout->addWidget(recoverButton);
    controlLayout->addWidget(chooseCubeOrderButton);
    controlLayout->addWidget(openCubeButton);
    controlLayout->addWidget(saveCubeButton);
    controlLayout->addStretch();

    mainView = new MainView();
    mainView->setMinimumSize(200,200);
    mainView->setMaximumSize(10000,10000);

    viewLayout = new QVBoxLayout;
    viewLayout->addWidget(mainView);

    debugTextEdit = new QTextEdit();
    debugTextEdit->setMinimumSize(0,0);
    debugTextEdit->setMaximumSize(200,1000);

    debugLayout = new QVBoxLayout;
    debugLayout->addWidget(debugTextEdit);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(controlLayout);
    mainLayout->addLayout(viewLayout);
    mainLayout->addLayout(debugLayout);

    setLayout(mainLayout);


    //连接debugSignal信号和debugSlots槽
    connect(mainView,SIGNAL(debugSignal(QString)),this,SLOT(debugSlots(QString)));

    connect(resetButton,SIGNAL(clicked()),mainView,SLOT(resetCube()));
    connect(upsetButton,SIGNAL(clicked()),mainView,SLOT(upsetCube()));
    connect(chooseCubeOrderButton,SIGNAL(clicked()),mainView,SLOT(setCubeOrder()));
    connect(backButton,SIGNAL(clicked()),mainView,SLOT(cubeStepBack()));
    connect(backAllButton,SIGNAL(clicked()),mainView,SLOT(cubeStepBackAll()));
    connect(recoverButton,SIGNAL(clicked()),mainView,SLOT(recoverCube()));
    connect(openCubeButton,SIGNAL(clicked()),mainView,SLOT(openCubeJson()));
    connect(saveCubeButton,SIGNAL(clicked()),mainView,SLOT(saveCubeJson()));


}

void MainWidget::debugSlots(QString debugMessage)
{
    debugTextEdit->setPlainText(debugMessage);
}




