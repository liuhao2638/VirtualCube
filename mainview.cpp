#include "mainview.h"

MainView::MainView(QWidget *parent)
    : QOpenGLWidget(parent)
{   
    //启用鼠标跟踪,
    setMouseTracking(true);
    //初始化绘制次数
    frameNumber=0;
    //计时器开始计时
    time.start();
    //初始化FPS
    FPS = 0;

    //设置抗锯齿
    QSurfaceFormat surfaceFormat;
    surfaceFormat.setSamples(4);//多重采样
    setFormat(surfaceFormat); //setFormat是QOpenGLWidget的函数
}
MainView::~MainView()
{
}

void MainView::initializeGL()
{
    initializeOpenGLFunctions();    //为当前上下文初始化提供OpenGL函数解析
    cube.init();
    //cube.setCubeOrder(10);
}
void MainView::resizeGL(int w,int h)
{
    glViewport(0,0,w,h);                  //定义视口区域
}
void MainView::paintGL()
{


    //cube.drawPick();
    cube.draw();

    //记录绘制帧数
    frameNumber++;

    //再次绘制,这只是个信号,不会导致卡死
    update();
    //发出调试信息
    sendDebugMessage();
}
bool MainView::event(QEvent *e)
{
    cube.handle(e);
    return QWidget::event(e);   //调用父类的事件分发函数
}

void MainView::sendDebugMessage()
{

    //currentTime为最新时间
    int currentTime = time.elapsed();
    //如果时间更新了一秒,计算
    if(currentTime/1000 - elapsedTime/1000 == 1){
        FPS=frameNumber;
        frameNumber=0;
    }
    //更新时间
    elapsedTime = currentTime;

    QString debugMessage;
    debugMessage =
        "运行时间:"+ QString::number(elapsedTime/1000)+"."+QString::number(elapsedTime%1000)+"s\n"+
        "FPS:"+QString::number(FPS)+"\n"+
        cube.getDebugMessage()+"\n"+
        " ";
    //发射调试信号
    emit debugSignal(debugMessage);

}
void MainView::cubeStepBack()
{
    cube.stepBack();
}
void MainView::cubeStepBackAll()
{
    cube.stepBackAll();
}
void MainView::setCubeOrder()
{
    bool ok;
    // 获取整数
    int cubeOrder = QInputDialog::getInt(this, tr("输入魔方阶数"), tr("请输入1到1000之间的数值"), 3, 0, 1000, 1, &ok);
    if(ok){
        cube.setOrder(cubeOrder);
    }
}
void MainView::resetCube()
{
    cube.reset();
}
void MainView::upsetCube()
{
    cube.upset();
}
void MainView::recoverCube()
{

    if(!cube.recover()){
        QMessageBox::about(NULL, "提示", "功能未实现！");
        return;
    }
}
void MainView::openCubeJson()
{
    //打开文件对话框，将文件路径赋给fileName
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("请选择存档"),
                "./saves",
                tr("File(*.cube)"));
    //qDebug()<<fileName<<endl;
    //如果未选择文件名则返回
    if(fileName.isEmpty()){
        return;
    }
    //读取文件
    QFile file(fileName);//创建文件对象file
    file.open(QIODevice::ReadOnly | QIODevice::Text);//打开文件
    QString cubeJsonString = file.readAll();//读取json文件内容为字符串
    file.close();//关闭文件

    //查看json格式错误
    QJsonParseError parseJsonErr;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(cubeJsonString.toUtf8(), &parseJsonErr);
    if(!(parseJsonErr.error==QJsonParseError::NoError)) {
        QMessageBox::about(NULL, "提示", "存档格式错误！");
        return;
    }
    //将jsonObject解析为jsonObject
    QJsonObject cubeJson = jsonDocument.object();
    //将读取的jsonObject传递给cube
    if(!cube.setJson(cubeJson)){
        QMessageBox::about(NULL, "提示", "存档数据错误！");
        return;
    }
}
void MainView::saveCubeJson()
{
    //打开文件对话框，将文件路径赋给fileName
    QString fileName;
    fileName = QFileDialog::getSaveFileName(
                this,
                tr("请选择存档"),
                tr("./saves/undefind.cube"),
                tr("File(*.cube)"));
    //如果未选择文件名则返回
    if(fileName.isEmpty()){
        return;
    }
    //获取魔方json文件
    QJsonObject cubeJson=cube.getJson();
    QJsonDocument jsonDocument(cubeJson);
    //qDebug()<<"在widget"<<cubeJson<<endl;
    //打开文件并写入文件
    QFile file(fileName);//创建文件对象file
    file.open(QIODevice::ReadWrite|QFile::Truncate);//打开文件
    file.write(jsonDocument.toJson());//写入文件
    file.close();//关闭文件


}
