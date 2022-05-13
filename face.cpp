#include "face.h"

Face::Face()
{
    for(int i=0;i<6;i++){
        faceColor[i]=i;
    }
    //初始化每个面顶点
    vertices[0] = {
         1.0f, 0.8f,-0.8f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         1.0f,-0.8f,-0.8f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         1.0f, 0.8f, 0.8f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         1.0f,-0.8f, 0.8f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    };
    indices[0] = {
        0,1,2,3,
    };
    vertices[1] = {
        -1.0f, 0.8f,-0.8f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -1.0f,-0.8f,-0.8f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -1.0f, 0.8f, 0.8f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -1.0f,-0.8f, 0.8f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    };
    indices[1] = {
        0,1,2,3,
    };
    vertices[2] = {
         0.8f, 1.0f,-0.8f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.8f, 1.0f,-0.8f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         0.8f, 1.0f, 0.8f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        -0.8f, 1.0f, 0.8f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    };
    indices[2] = {
        0,1,2,3,
    };
    vertices[3] = {
         0.8f,-1.0f,-0.8f,  0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
        -0.8f,-1.0f,-0.8f,  0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
         0.8f,-1.0f, 0.8f,  0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
        -0.8f,-1.0f, 0.8f,  0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
    };
    indices[3] = {
        0,1,2,3,
    };
    vertices[4] = {
         0.8f, 0.8f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
         0.8f,-0.8f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.8f, 0.8f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.8f,-0.8f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    };
    indices[4] = {
        0,1,2,3,
    };
    vertices[5] = {
        0.8f, 0.8f,-1.0f,  0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
        0.8f,-0.8f,-1.0f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
       -0.8f, 0.8f,-1.0f,  0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
       -0.8f,-0.8f,-1.0f,  0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
    };
    indices[5] = {
        0,1,2,3,
    };
    vertices[6] = {
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
    };
    indices[6] = {
        0,1,2,3,
    };
    vertices[7] = {
        -1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
    };
    indices[7] = {
        0,1,2,3,
    };
    vertices[8] = {
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
    };
    indices[8] = {
        0,1,2,3,
    };
    vertices[9] = {
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
    };
    indices[9] = {
        0,1,2,3,
    };
    vertices[10] = {
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
    };
    indices[10] = {
        0,1,2,3,
    };
    vertices[11] = {
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
       -1.0f, 1.0f,-1.0f,
       -1.0f,-1.0f,-1.0f,
    };
    indices[11] = {
        0,1,2,3,
    };


}
void Face::init()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);//开启深度测试
    //glEnable(GL_CULL_FACE);//开启背面剔除
    glEnable(GL_SMOOTH);//设置阴影平滑模式
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正


    /*------------------------渲染程序初始化---------------------------*/
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "face/face.vert")) //添加并编译顶点着色器
        qDebug() << "编译ERROR:" << shaderProgram.log();    //如果编译出错,打印报错信息
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "face/face.frag"))//添加并编译片段着色器
        qDebug() << "编译ERROR:" << shaderProgram.log();    //如果编译出错,打印报错信息
    if (!shaderProgram.link())                       //链接着色器
        qDebug() << "链接ERROR:" << shaderProgram.log();    //如果链接出错,打印报错信息
 
    shaderProgram.bind();
    for(int i=0;i<6;i++){
        //定义顶点缓冲区数据读取方式
        VAO[i].create();
        VAO[i].bind();
        
    
        VBO[i] = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        VBO[i].create();
        VBO[i].bind();
        VBO[i].allocate(vertices[i].data(), vertices[i].size() * sizeof(float)); //顶点数据
    
        EBO[i] = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        EBO[i].create();
        EBO[i].bind();
        EBO[i].allocate(indices[i].data(), indices[i].size() * sizeof(unsigned int)); //索引数据
    
        //顶点组内偏移offset
        quintptr offset = 0;
    
        //设置顶点解析格式，并启用顶点
        shaderProgram.setAttributeBuffer("aPosition", GL_FLOAT, 0, 3, sizeof(GLfloat) * 8);
        shaderProgram.enableAttributeArray("aPosition");
        shaderProgram.setAttributeBuffer("aNormal", GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8);
        shaderProgram.enableAttributeArray("aNormal");
        shaderProgram.setAttributeBuffer("aTexCoord", GL_FLOAT, sizeof(GLfloat) * 6, 2, sizeof(GLfloat) * 8);
        shaderProgram.enableAttributeArray("aTexCoord");
    
        VAO[i].release();
        VBO[i].release();
        EBO[i].release();
    }
    shaderProgram.release();
    /*------------------------拾取渲染程序初始化---------------------------*/
    if (!pickingProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "face/pick.vert")) //添加并编译顶点着色器
        qDebug() << "编译ERROR:" << pickingProgram.log();    //如果编译出错,打印报错信息
    if (!pickingProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "face/pick.frag"))//添加并编译片段着色器
        qDebug() << "编译ERROR:" << pickingProgram.log();    //如果编译出错,打印报错信息
    if (!pickingProgram.link())                       //链接着色器
        qDebug() << "链接ERROR:" << pickingProgram.log();    //如果链接出错,打印报错信息

    pickingProgram.bind();
    for(int i=6;i<12;i++){
        //定义顶点缓冲区数据读取方式
        VAO[i].create();
        VAO[i].bind();


        VBO[i] = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        VBO[i].create();
        VBO[i].bind();
        VBO[i].allocate(vertices[i].data(), vertices[i].size() * sizeof(float)); //顶点数据

        EBO[i] = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        EBO[i].create();
        EBO[i].bind();
        EBO[i].allocate(indices[i].data(), indices[i].size() * sizeof(unsigned int)); //索引数据

        //设置顶点解析格式，并启用顶点
        pickingProgram.setAttributeBuffer("aPosition", GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
        pickingProgram.enableAttributeArray("aPosition");

        VAO[i].release();
        VBO[i].release();
        EBO[i].release();
    }
    pickingProgram.release();


    //纹理初始化
    texture[0] = new QOpenGLTexture(QImage("face/white.png").mirrored());
    texture[1] = new QOpenGLTexture(QImage("face/yellow.png").mirrored());
    texture[2] = new QOpenGLTexture(QImage("face/red.png").mirrored());
    texture[3] = new QOpenGLTexture(QImage("face/orange.png").mirrored());
    texture[4] = new QOpenGLTexture(QImage("face/blue.png").mirrored());
    texture[5] = new QOpenGLTexture(QImage("face/green.png").mirrored());
    texture[6] = new QOpenGLTexture(QImage("face/gray.png").mirrored());
    for(int i=0;i<7;i++){
        texture[i]->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
        texture[i]->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
        texture[i]->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);
    }



}
void Face::setFaceColor(int face[6])
{
    for(int i=0;i<6;i++){
        faceColor[i] = face[i]; 
    }
}
void Face::draw(QMatrix4x4 mMat,QMatrix4x4 vMat,QMatrix4x4 pMat)
{
    shaderProgram.bind();
    for(int i=0;i<6;i++){
        VAO[i].bind();
        
        texture[faceColor[i]]->bind(0);                                    //将texture绑定到纹理单元0
    
        QVector3D lightColor(1.0f,1.0f,1.0f);
        //QVector3D objectColor(1.0f,0.5f,0.31f);//QVector3D lightPos(-4.0f,0.0f,0.5f);
        QVector3D lightPos(0.0f,0.0f,5.0f);
        QVector3D viewPos(0.0f,0.0f,5.0f);
    
        shaderProgram.setUniformValue("lightColor",lightColor);
        shaderProgram.setUniformValue("lightPos", lightPos);
        shaderProgram.setUniformValue("viewPos", viewPos);
    
        shaderProgram.setUniformValue("mMat",mMat);
        shaderProgram.setUniformValue("vMat",vMat);
        shaderProgram.setUniformValue("pMat",pMat);
        //让着色采样器ourTexture从纹理单元0中获取纹理数据
        shaderProgram.setUniformValue("texture",0);
    
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawElements(GL_TRIANGLE_STRIP, indices[i].size(), GL_UNSIGNED_INT, 0);
    
        VAO[i].release();
        texture[faceColor[i]]->release(0);
    }
    shaderProgram.release();
}
void Face::drawPick(QMatrix4x4 mMat,QMatrix4x4 vMat,QMatrix4x4 pMat,QVector4D pickingColor)
{
    pickingProgram.bind();
    for(int i=0;i<6;i++){
        VAO[i+6].bind();
        pickingProgram.setUniformValue("mMat",mMat);
        pickingProgram.setUniformValue("vMat",vMat);
        pickingProgram.setUniformValue("pMat",pMat);
        pickingProgram.setUniformValue("pickingColor",pickingColor);
        pickingColor+=QVector4D(1.0f/255.0f,1.0f/255.0f,1.0f/255.0f,1.0f);
        glDrawElements(GL_TRIANGLE_STRIP, indices[i].size(), GL_UNSIGNED_INT, 0);
        VAO[i+6].release();
    }
    pickingProgram.release();
}


























