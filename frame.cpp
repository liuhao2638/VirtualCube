#include "frame.h"

Frame::Frame()
{

}
void Frame::init()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);//开启深度测试
    //glEnable(GL_CULL_FACE);//开启背面剔除
    glEnable(GL_SMOOTH);//设置阴影平滑模式
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正

    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "frame/frame.vert")) //添加并编译顶点着色器
        qDebug() << "编译ERROR:" << shaderProgram.log();    //如果编译出错,打印报错信息
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "frame/frame.frag"))//添加并编译片段着色器
        qDebug() << "编译ERROR:" << shaderProgram.log();    //如果编译出错,打印报错信息
    if (!shaderProgram.link())                       //链接着色器
        qDebug() << "链接ERROR:" << shaderProgram.log();    //如果链接出错,打印报错信息
    //载入模型
    loadModel("frame/frame1.obj");

    //定义顶点缓冲区数据读取方式
    VAO.create();
    VAO.bind();
    shaderProgram.bind();

    VBO = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    VBO.create();
    VBO.bind();
    VBO.allocate(vertices.data(), vertices.size() * sizeof(float)); //顶点数据

    EBO = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    EBO.create();
    EBO.bind();
    EBO.allocate(indices.data(), indices.size() * sizeof(unsigned int)); //索引数据

    //设置顶点解析格式，并启用顶点
    shaderProgram.setAttributeBuffer("aPosition", GL_FLOAT, 0, 3, sizeof(GLfloat) * 8);
    shaderProgram.enableAttributeArray("aPosition");
    shaderProgram.setAttributeBuffer("aNormal", GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 8);
    shaderProgram.enableAttributeArray("aNormal");
    shaderProgram.setAttributeBuffer("aTexCoord", GL_FLOAT, sizeof(GLfloat) * 6, 2, sizeof(GLfloat) * 8);
    shaderProgram.enableAttributeArray("aTexCoord");

    VAO.release();
    VBO.release();
    EBO.release();
    shaderProgram.release();

    //纹理初始化
    texture[0] = new QOpenGLTexture(QImage("frame/frame1.png").mirrored());
    texture[1] = new QOpenGLTexture(QImage("frame/frame2.png").mirrored());

    texture[0]->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
    texture[0]->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture[0]->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);

    texture[1]->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear,QOpenGLTexture::Linear);
    texture[1]->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture[1]->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);
}
void Frame::draw(QMatrix4x4 mMat,QMatrix4x4 vMat,QMatrix4x4 pMat)
{
    VAO.bind();
    shaderProgram.bind();
    texture[0]->bind(0);                                    //将texture绑定到纹理单元0

    QVector3D lightColor(1.0f,1.0f,1.0f);
    //QVector3D lightPos(-4.0f,0.0f,0.5f);
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
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    VAO.release();
    shaderProgram.release();
    texture[0]->release(0);
}
void Frame::drawSelectd(QMatrix4x4 mMat,QMatrix4x4 vMat,QMatrix4x4 pMat)
{
    VAO.bind();
    shaderProgram.bind();
    texture[1]->bind(0);                                    //将texture绑定到纹理单元0

    QVector3D lightColor(1.0f,1.0f,1.0f);
    //QVector3D lightPos(-4.0f,0.0f,0.5f);
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
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    VAO.release();
    shaderProgram.release();
    texture[1]->release(0);
}
void Frame::loadModel(const QString &filepath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath.toUtf8(),
                                             aiProcess_Triangulate |
                                             aiProcess_FlipUVs |
                                             aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
            !scene->mRootNode) {
        qDebug()<<__FUNCTION__<<importer.GetErrorString();
        return;
    }else{
        // 以递归方式处理ASSIMP的根节点
        processNode(scene->mRootNode, scene);
    }
}
void Frame::processNode(aiNode *node, const aiScene *scene)
{
    //qDebug()<<__FUNCTION__<<"mNumMeshes"<<node->mNumMeshes<<"mNumChildren"<<node->mNumChildren;
    // 处理位于当前节点的每个网格
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // 节点对象仅包含索引用来索引场景中的实际对象。
        // 场景包含所有数据，节点只是为了有组织的保存东西（如节点之间的关系）。
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }
    // 在我们处理完所有网格（如果有的话）后，我们会递归处理每个子节点
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
void Frame::processMesh(aiMesh *mesh, const aiScene *scene)
{
    //Q_UNUSED(scene)
    //qDebug()<<__FUNCTION__<<"mNumVertices"<<mesh->mNumVertices<<"mNumFaces"<<mesh->mNumFaces;
    vertices.clear();
    indices.clear();

    // 遍历每个网格的顶点
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertices<< mesh->mVertices[i].x//顶点坐标
                << mesh->mVertices[i].y
                << mesh->mVertices[i].z
                << mesh->mNormals[i].x//法向量
                << mesh->mNormals[i].y
                << mesh->mNormals[i].z
                << mesh->mTextureCoords[0][i].x//纹理坐标
                << -mesh->mTextureCoords[0][i].y;
    }
    // 现在遍历每个网格面（一个面是一个三角形的网格）并检索相应的顶点索引。
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        //if(i == 0) qDebug()<<"mNumFaces"<<face.mNumIndices;
        // 检索面的所有索引并将它们存储在索引向量中
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
}

