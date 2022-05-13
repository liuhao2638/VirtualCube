#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "cube.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QTimer>
#include <QTime>
#include <QtMath>

#include <QJsonObject>
#include <QFileDialog>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QMessageBox>
#include <QInputDialog>

class MainView : public QOpenGLWidget,public QOpenGLFunctions
{
    Q_OBJECT
signals:
    void debugSignal(QString debugMessage);   //调试信息更新信号
private slots:    
    void sendDebugMessage();                  //汇总调试信息并发送debugSignal信号
    void cubeStepBack();                      //退回一步转动
    void cubeStepBackAll();                   //退回全部
    void setCubeOrder();         //重置魔方阶数
    void resetCube();                         //重置魔方
    void upsetCube();                         //打乱魔方
    void recoverCube();                       //还原魔方
    void openCubeJson();                       //重设魔方
    void saveCubeJson();                       //获取魔方数据


public:
    MainView(QWidget *parent = 0);
    ~MainView();
protected:
    //主要绘图函数
    void initializeGL() override;           //初始化OpenGL环境
    void resizeGL(int w, int h) override;   //根据窗口大小重绘视图
    void paintGL() override;                //渲染一帧OpenGL场景
    bool event(QEvent *e) override;         //用户控制事件
private:

    QTime time;             //计时器

    //魔方动画对象
    Cube cube;

    int elapsedTime;            //程序运行时间
    int frameNumber;            //计数绘制次数
    int FPS;                    //每秒绘制次数


};
#endif // MAINVIEW_H
