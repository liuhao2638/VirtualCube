#ifndef FRAME_H
#define FRAME_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <QVector>
#include <QDebug>
#include <QApplication>

class Frame : public QOpenGLFunctions
{
public:
    Frame();
    void init();//初始化函数
    void draw(QMatrix4x4 mMat,QMatrix4x4 vMat,QMatrix4x4 pMat);//绘图函数
    void drawSelectd(QMatrix4x4 mMat,QMatrix4x4 vMat,QMatrix4x4 pMat);//绘图函数
private:
    // 加载模型
    void loadModel(const QString &filepath);
    void processNode(aiNode *node, const aiScene *scene);
    void processMesh(aiMesh *mesh, const aiScene *scene);


    // 存顶点空间坐标和顶点纹理坐标和顶点索引
    QVector<float> vertices;
    QVector<unsigned int> indices;

    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLBuffer EBO;
    QOpenGLTexture *texture[2];
    QOpenGLShaderProgram shaderProgram;
};

#endif // FRAME_H
