#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QColor>
#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTime>

#include "frame.h"
#include "face.h"
#include "cubedata.h"

#include <vector>
#include <queue>
#include <stack>

#include <QJsonObject>
#include <QJsonArray>

using namespace std;

//拾取面结构体
struct Pick {
    //保存是否拾取到实体
    bool isPick;
    //ijk方块位置，l面位置
	int i, j, k, l;
};

class Cube : public QOpenGLFunctions
{
public:
    Cube();                          //初始化函数
    void handle(QEvent *e);          //处理窗口事件
    void setOrder(int cubeOrder);//重设魔方阶数
    void init();                     //初始化openGL相关
    void draw();                     //绘图函数
    QString getDebugMessage();       //获取cube的调试信息   
    void stepBack();                 //退回一步
    void stepBackAll();              //退回全部
    void reset();                    //重置状态
    void upset();                    //打乱魔方
    bool recover();                  //还原魔方
    bool setJson(QJsonObject cubeJson);//重设魔方
    QJsonObject getJson();           //获取魔方数据

private:
    void rotate();               //执行转动任务
    float toRadians(float degrees);  //角度转弧度
    void updateView();               //更新mvp矩阵
    void drawCube();                 //绘制原图
    void drawPick();                 //绘制拾取图
    void judgePick();                //根据两次拾取点判断魔方转动并加入转动队列
private:
    //状态参数
    const QString NotPress = "NotPress";
    const QString MoveView = "MoveView";
    const QString Selected = "Selected";

    QString status;             //魔方状态

    QVector3D cameraPos;        //相机坐标
    QVector3D objectPos;        //物体坐标

    float rotY;                 //物体Y轴旋转系数
    float rotXZ;                //物体XZ轴旋转系数
    float scale;                //缩小系数
    int width;                  //屏幕宽
    int height;                 //屏幕高

    int mouseX;                 //鼠标坐标
    int mouseY;

    QMatrix4x4 pMat;            //透视矩阵
    QMatrix4x4 vMat;            //视图矩阵
    QMatrix4x4 mMat;            //模型矩阵

    //框架绘制对象
    Frame frame;
    //魔方面绘制对象
    Face face;

    //魔方阶数
    int cubeOrder;
    //用于绘制面的数据
    vector<vector<vector<vector<int>>>> faceData;
    //用于绘制角度的数据
    vector<vector<vector<vector<int>>>> rotateData;
    //控制旋转速度
    int rotateSpeed;

    //notBack不为0时不能打入栈(防止重复入栈)
    int notBack;
    //魔方转动队列
    queue<CubeRotate> rotateSteps;
    //魔方步骤存放栈
    stack<CubeRotate> rotateStack;

    CubeData cubeData;          //魔方数据集
    
    bool shouldPick;            //控制绘制方式
    Pick pickFirst;             //拾取的第一个面
    Pick pickSecond;            //拾取的第二个面
};

#endif // CUBE_H
