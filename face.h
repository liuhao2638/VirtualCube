#ifndef FACE_H
#define FACE_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include <QVector>
#include <QDebug>
#include <QApplication>

class Face : public QOpenGLFunctions
{
public:
    Face();
    void init();//初始化函数
    void setFaceColor(int face[6]);//设置表面颜色
    void draw(QMatrix4x4 mMat,QMatrix4x4 vMat,QMatrix4x4 pMat);//绘图函数
    void drawPick(QMatrix4x4 mMat,QMatrix4x4 vMat,QMatrix4x4 pMat,QVector4D pickingColor);//绘制拾取图
private:
    //6个面的颜色索引
    int faceColor[6];
    
    // 存顶点空间坐标和顶点纹理坐标和顶点索引
    QVector<float> vertices[12];
    QVector<unsigned int> indices[12];

    QOpenGLVertexArrayObject VAO[12];
    QOpenGLBuffer VBO[12];
    QOpenGLBuffer EBO[12];
    QOpenGLTexture *texture[7];

    QOpenGLShaderProgram shaderProgram;
    QOpenGLShaderProgram pickingProgram;
};

#endif // FACE_H
