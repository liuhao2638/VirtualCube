#include "cube.h"

Cube::Cube()
{
    cameraPos = QVector3D(0.0f,0.0f,5.0f);
    objectPos = QVector3D(0.0f,0.0f,0.0f);

    scale = 1.0f;
    rotY = -37.0f;
    rotXZ = 24.0f;

    mouseX = 0;                 //鼠标坐标
    mouseY = 0;

    pMat.setToIdentity();
    vMat.setToIdentity();
    mMat.setToIdentity();
    vMat.translate(-cameraPos);
    mMat.translate(objectPos);

    //设置魔方旋转速度
    rotateSpeed = 5;
    //默认绘制原图
    shouldPick = false;
    //初始化状态
    status = NotPress;
    
    //设置魔方阶数默认为3
    setOrder(3);


}
void Cube::setOrder(int cubeOrder)
{
    this->cubeOrder = cubeOrder;
    /*------------------初始化绘制数据faceData---------------------*/
    faceData.resize(cubeOrder);
    for (int i = 0; i < cubeOrder; i++) {
        faceData[i].resize(cubeOrder);
        for (int j = 0; j < cubeOrder; j++) {
            faceData[i][j].resize(cubeOrder);
            for (int k = 0; k < cubeOrder; k++) {
                faceData[i][j][k].resize(6);
                for (int l = 0; l < 6; l++)
                    faceData[i][j][k][l] = 6;
            }
        }
    }
    /*------------------初始化旋转数据rotateData---------------------*/
    rotateData.resize(cubeOrder);
    for (int i = 0; i < cubeOrder; i++) {
        rotateData[i].resize(cubeOrder);
        for (int j = 0; j < cubeOrder; j++) {
            rotateData[i][j].resize(cubeOrder);
            for (int k = 0; k < cubeOrder; k++) {
                rotateData[i][j][k].resize(3);
                for (int l = 0; l < 3; l++)
                    rotateData[i][j][k][l] = 0;
            }
        }
    }


    //更新视角
    updateView();

    //重设魔方数据集的阶数
    cubeData.setCubeOrder(cubeOrder);
    //以魔方基本数据集重新赋值
    cubeData.toRenderData(faceData);

    status = NotPress;
    //清空转动步骤
    while(!rotateSteps.empty())
       rotateSteps.pop();
    //清空退回栈
    while(!rotateStack.empty())
       rotateStack.pop();
    notBack = false;

    pickFirst.isPick = false;
    pickFirst.i = 255;
    pickFirst.j = 255;
    pickFirst.k = 255;
    pickFirst.l = 255;
    pickSecond.isPick = false;
    pickSecond.i = 255;
    pickSecond.j = 255;
    pickSecond.k = 255;
    pickSecond.l = 255;

    notBack = 0;
}
void Cube::handle(QEvent *e)
{
    if(e->type()==QEvent::MouseMove){
        QMouseEvent *event=static_cast<QMouseEvent*>(e);
        int x = event->x();
        int y = event->y();
        if(status == MoveView){
            rotXZ -= (float)(mouseY - y) / 3;
            rotY -= (float)(mouseX - x) / 3;
            if (rotXZ > 90.0f) {//xz轴转动角度不得超过360度
                rotXZ = 90.0f;
            }
            else if (rotXZ < -90.0f) {
                rotXZ = -90.0f;
            }

            if (rotY > 360.0f) {//xz轴转动角度不得超过360度
                rotY -= 360.0f;
            }
            else if (rotY < -360.0f) {
                rotY += 360.0f;
            }
            updateView();
        }else if(status == Selected){
            shouldPick = true;
        }
        mouseX = x;
        mouseY = y;
    }
    else if(e->type()==QEvent::MouseButtonPress){
        shouldPick = true;
    }
    else if(e->type()==QEvent::MouseButtonRelease){         
        judgePick();
        shouldPick = false;
        status = NotPress;
    }
    else if(e->type()==QEvent::Wheel){
        QWheelEvent *event=static_cast<QWheelEvent*>(e);
        scale -= event->delta()/(float)20000*cubeOrder;
        if(scale<0.70)scale=0.70;
        updateView();
    }
    else if(e->type()==QEvent::Resize){
        QResizeEvent *event=static_cast<QResizeEvent*>(e);
        width = event->size().width();
        height = event->size().height();
        pMat.setToIdentity();
        pMat.perspective(45.0f, width/(float)height, 0.1f, 1000.0f);
    }
}
void Cube::init()
{
    initializeOpenGLFunctions();    //为当前上下文初始化提供OpenGL函数解析
    frame.init();
    face.init();
}
void Cube::draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //清屏
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);



    if(!rotateSteps.empty()){
        //执行转动任务
        rotate();
    }

    //如果拾取标志位有效而且没有转动任务
    if(shouldPick)
        //绘制拾取图
        drawPick();
    //绘制
    drawCube();
}
QString Cube::getDebugMessage()
{
   QString debugMessage;
   debugMessage =
       "鼠标坐标: <"+QString::number(mouseX)+","+QString::number(mouseY)+">\n"+
       "屏幕宽高: <"+QString::number(width)+","+QString::number(height)+">\n"+
       "status: "+status+"\n"+
       "rotXZ: "+QString::number(rotXZ)+"\n"+
       "rotY: "+QString::number(rotY)+"\n"+
       "scale: "+QString::number(scale)+"\n"+
       "第一拾取点:\n"+
           "<"+
           QString::number(pickFirst.i)+","+
           QString::number(pickFirst.j)+","+
           QString::number(pickFirst.k)+","+
           QString::number(pickFirst.l)+
           ">\n"
       "第二拾取点:\n"+
           "<"+
           QString::number(pickSecond.i)+","+
           QString::number(pickSecond.j)+","+
           QString::number(pickSecond.k)+","+
           QString::number(pickSecond.l)+
           ">\n"+
       "转动队列大小: "+QString::number(rotateSteps.size())+"\n"+
       "退回栈大小: "+QString::number(rotateStack.size())+"\n"+
       "转动速度: "+QString::number(rotateSpeed+((rotateSteps.size()==0)?0:rotateSteps.size()-1))+"\n"+
       " ";

   return debugMessage;
}
void Cube::stepBack(){
    //如果栈非空且转动队列为空
    if(!rotateStack.empty()&&rotateSteps.empty()){
        CubeRotate step = rotateStack.top();
        //将转动步骤设置为反向
        if(step.angle==1)
            step.angle=3;
        else if(step.angle==3)
            step.angle=1;
        else if(step.angle==2)
            step.angle=2;
        //此步骤加入转动队列
        rotateSteps.push(step);
        //出栈
        rotateStack.pop();
        //防止反复入栈
        notBack++;
    }
}
void Cube::stepBackAll()
{
    rotateSpeed = 2;

    notBack = rotateStack.size();
    while(!rotateStack.empty()){
        CubeRotate step = rotateStack.top();
        //将转动步骤设置为反向
        if(step.angle==1)
            step.angle=3;
        else if(step.angle==3)
            step.angle=1;
        else if(step.angle==2)
            step.angle=2;
        //此步骤加入转动队列
        rotateSteps.push(step);
        //出栈
        rotateStack.pop();
    }
}
void Cube::reset()
{
    setOrder(cubeOrder);
}
void Cube::upset()
{
    rotateSpeed = 2;
    //随机数设置
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 0; i < 50; i++) {
        CubeRotate temp = { qrand() % 3,qrand() % cubeOrder,(qrand() % 2)*2+1  };
        rotateSteps.push(temp);
    }
}
bool Cube::recover()
{
    if(cubeOrder==2){
        rotateSpeed = 2;
        if(rotateSteps.empty())
            rotateSteps = cubeData.recovery();
        return true;
    }else{
        return false;
    }
}
bool Cube::setJson(QJsonObject cubeJson)
{
    //查看格式是否正确
    //rotY
    if(cubeJson.contains("rotY")){
        float rotY = cubeJson.value("rotY").toDouble();
        if(rotY<-360.0f||rotY>360.0f){
            return false;
        }
    }
    else return false;
    //rotXZ
    if(cubeJson.contains("rotXZ")){
        float rotXZ = cubeJson.value("rotXZ").toDouble();
        if(rotXZ<-90.0f||rotXZ>90.0f){
            return false;
        }
    }
    else return false;
    //scale
    if(cubeJson.contains("scale")){
        float scale = cubeJson.value("scale").toDouble();
        if(scale<0.7f){
            return false;
        }
    }
    else return false;
    //cubeOrder和cubeData和rotateStack
    if(cubeJson.contains("cubeOrder")){
        int cubeOrder = cubeJson.value("cubeOrder").toInt();
        if(cubeOrder<=0){
            return false;
        }
        if(cubeJson.contains("cubeData")){
            QJsonArray cubeDataArray = cubeJson.value("cubeData").toArray();
            if(cubeDataArray.size()!=cubeOrder*cubeOrder*6)return false;
            for(int i=cubeDataArray.size()-1;i>=0;i--){
                int face = cubeDataArray.at(i).toInt();
                if(face<0||face>5)return false;
            }
        }else return false;
        //rotateStack
        if(cubeJson.contains("rotateStack")){
            QJsonArray rotateStackArray = cubeJson.value("rotateStack").toArray();
            for(int i=rotateStackArray.size()-1;i>=0;i--){
                QJsonObject cubeRotateStep = rotateStackArray.at(i).toObject();
                if(
                    cubeRotateStep.contains("axle")&&
                    cubeRotateStep.contains("layer")&&
                    cubeRotateStep.contains("angle")
                    ){
                    int axle = cubeRotateStep.value("axle").toInt();
                    int layer = cubeRotateStep.value("layer").toInt();
                    int angle = cubeRotateStep.value("angle").toInt();
                    if(axle<0||axle>2)return false;
                    if(layer<0||layer>=cubeOrder)return false;
                    if(angle<1||angle>3)return false;
                }else return false;
            }
        }
        else return false;
    }
    else return false;

    rotY = cubeJson.value("rotY").toDouble();
    rotXZ = cubeJson.value("rotXZ").toDouble();
    scale = cubeJson.value("scale").toDouble();
    cubeOrder = cubeJson.value("cubeOrder").toInt();
    //重设魔方阶数
    setOrder(cubeOrder);
    QJsonArray rotateStackArray = cubeJson.value("rotateStack").toArray();
    for(int i=rotateStackArray.size()-1;i>=0;i--){
        QJsonObject cubeRotateStep = rotateStackArray.at(i).toObject();
        CubeRotate step;
        step.axle = cubeRotateStep.value("axle").toInt();
        step.layer = cubeRotateStep.value("layer").toInt();
        step.angle = cubeRotateStep.value("angle").toInt();

        rotateStack.push(step);
    }

    QJsonArray cubeDataArray = cubeJson.value("cubeData").toArray();
    vector<vector<int>> data[6];
    for(int i=0;i<6;i++){
        data[i].resize(cubeOrder);
        for(int j=0;j<cubeOrder;j++){
            data[i][j].resize(cubeOrder);
            for(int k=0;k<cubeOrder;k++){
                data[i][j][k] = cubeDataArray.at(i*(cubeOrder*cubeOrder)+j*cubeOrder+k).toInt();
            }
        }
    }
    //设置cubeData
    cubeData.setData(data);
    cubeData.toRenderData(faceData);
    return true;
}
QJsonObject Cube::getJson()
{
    //将cube所有参数写入cubeJson作为存档
    QJsonObject cubeJson;

    cubeJson.insert("rotY",QJsonValue(rotY));
    cubeJson.insert("rotXZ",QJsonValue(rotXZ));
    cubeJson.insert("scale",QJsonValue(scale));
    cubeJson.insert("cubeOrder",QJsonValue(cubeOrder));
    QJsonArray rotateStackArray;

    stack<CubeRotate>temp = rotateStack;
    while(!temp.empty()){
        CubeRotate step = temp.top();
        temp.pop();
        QJsonObject cubeRotateStep;
        cubeRotateStep.insert("axle",step.axle);
        cubeRotateStep.insert("layer",step.layer);
        cubeRotateStep.insert("angle",step.angle);
        rotateStackArray.append(QJsonValue(cubeRotateStep));
    }
    cubeJson.insert("rotateStack",QJsonValue(rotateStackArray));
    QJsonArray cubeDataArray;
    vector<vector<int>> *data = cubeData.getData();
    for(int i=0;i<6;i++){
        for(int j=0;j<cubeOrder;j++){
            for(int k=0;k<cubeOrder;k++){
                cubeDataArray.append(data[i][j][k]);
            }
        }
    }
    cubeJson.insert("cubeData",QJsonValue(cubeDataArray));

    //qDebug()<<"在cube"<<cubeJson<<endl;
    return cubeJson;
}


void Cube::rotate()
{
    //获取当前转动步骤
    CubeRotate step = rotateSteps.front();


    //当前转动角度
    static int angle = 0;

    //角度增加
    angle += rotateSpeed+((rotateSteps.size()==0)?0:rotateSteps.size()-1);
    //角度超过90度则转动动作完成
    if (angle >= 90) {
        //重置角度
        angle = 0;
        //魔方基本数据转动
        cubeData.rotateCube(step);
        //更新绘制数据
        cubeData.toRenderData(faceData);
        rotateSteps.pop();

        //notBack==0不能退回
        if(notBack!=0){
            notBack--;
        }else{
            //转动步骤存入栈
            rotateStack.push(step);
        }

        if(rotateSteps.empty()){
            rotateSpeed = 5;
        }
    }
    //为所有小方块的转动角度赋值
    for (int i = 0; i < cubeOrder; i++) {
            for (int j = 0; j < cubeOrder; j++) {
                if (step.angle == 1) {//顺时针转动
                    if (step.axle == 0)
                        rotateData[cubeOrder - step.layer - 1][i][j][0] = angle;
                    else if (step.axle == 1)
                        rotateData[i][cubeOrder - step.layer - 1][j][1] = angle;
                    else if (step.axle == 2)
                        rotateData[i][j][cubeOrder - step.layer - 1][2] = angle;
                }
                else if(step.angle == 2){//180度转动
                    if (step.axle == 0)
                        rotateData[cubeOrder - step.layer - 1][i][j][0] = 2*angle;
                    else if (step.axle == 1)
                        rotateData[i][cubeOrder - step.layer - 1][j][1] = 2*angle;
                    else if (step.axle == 2)
                        rotateData[i][j][cubeOrder - step.layer - 1][2] = 2*angle;
                }
                else if(step.angle == 3){//逆时针转动
                    if (step.axle == 0)
                        rotateData[cubeOrder - step.layer - 1][i][j][0] = -angle;
                    else if (step.axle == 1)
                        rotateData[i][cubeOrder - step.layer - 1][j][1] = -angle;
                    else if (step.axle == 2)
                        rotateData[i][j][cubeOrder - step.layer - 1][2] = -angle;
                }


            }
        }
}
float Cube::toRadians(float degrees)
{
    return (degrees * 2.0f * 3.14159f) / 360.0f;
}
void Cube::updateView()
{
    mMat.setToIdentity();
    mMat.translate(objectPos);
    //vMat旋转变换
    mMat.rotate(rotY,0.0f, 1.0f, 0.0f);
    mMat.rotate(rotXZ, cos(toRadians(rotY)), 0.0f, sin(toRadians(rotY)));
    //mMat缩放变换
    mMat.scale(1 / (scale*1.00*cubeOrder), 1 / (scale*1.00*cubeOrder), 1 / (scale*1.00*cubeOrder));
}
void Cube::drawCube()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //模型矩阵变换栈
    stack<QMatrix4x4> mStack;
    mStack.push(mMat);
    //遍历每个方块绘制
    for (int i = 0; i < cubeOrder; i++)
        for (int j = 0; j < cubeOrder; j++)
            for (int k = 0; k < cubeOrder; k++) {
                //只绘制在外表面的方块减小开销
                if (i==0||j==0||k==0||i==cubeOrder-1||j==cubeOrder-1||k==cubeOrder-1) {
                    //设置小方块6个面颜色
                    int faceColor[6];
                    for (int l = 0; l < 6; l++) {
                        faceColor[l] = faceData[i][j][k][l];
                    }
                    face.setFaceColor(faceColor);
                    //偏移量叠加
                    mStack.push(mStack.top());
                    //偏移
                    mStack.top().rotate(rotateData[i][j][k][0],1.0f, 0.0f, 0.0f);
                    mStack.top().rotate(rotateData[i][j][k][1],0.0f, 1.0f, 0.0f);
                    mStack.top().rotate(rotateData[i][j][k][2],0.0f, 0.0f, 1.0f);
                    mStack.top().translate(
                                    ((i - (float)faceData.size() / 2) * 2 + 1),
                                    ((j - (float)faceData.size() / 2) * 2 + 1),
                                    ((k - (float)faceData.size() / 2) * 2 + 1)
                                );

                    //绘制框架
                    //如果被选定，绘制被选中的框架样式,否则绘制原样式
                    if(
                          (
                                pickFirst.isPick==true&&
                                pickFirst.i==i&&
                                pickFirst.j==j&&
                                pickFirst.k==k
                           )||(
                                pickSecond.isPick==true&&
                                pickSecond.i==i&&
                                pickSecond.j==j&&
                                pickSecond.k==k
                           )
                       ){
                       frame.drawSelectd(mStack.top(),vMat,pMat);
                    }else{
                       frame.draw(mStack.top(),vMat,pMat);
                    }
                    //绘制表面
                    face.draw(mStack.top(),vMat,pMat);

                    //退回一个变换系
                    mStack.pop();
                }
            }
    //退回一个变换系
    mStack.pop();
}
void Cube::drawPick()
{
    shouldPick = false;
    if(status == MoveView){
        status = NotPress;
        return;
    }

    //利用fbo暂存
    QOpenGLFramebufferObject fbo(width,height, QOpenGLFramebufferObject::Depth);
    fbo.bind();

    /************ drawPick ***********/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //模型矩阵变换栈
    stack<QMatrix4x4> mStack;
    mStack.push(mMat);
    //遍历每个方块绘制
    for (int i = 0; i < cubeOrder; i++)
        for (int j = 0; j < cubeOrder; j++)
            for (int k = 0; k < cubeOrder; k++) {
                if (i==0||j==0||k==0||i==cubeOrder-1||j==cubeOrder-1||k==cubeOrder-1) {
                    //偏移量叠加
                    mStack.push(mStack.top());
                    //偏移
                    mStack.top().translate(
                                    ((i - (float)faceData.size() / 2) * 2 + 1),
                                    ((j - (float)faceData.size() / 2) * 2 + 1),
                                    ((k - (float)faceData.size() / 2) * 2 + 1)
                                );

                    QVector4D pickingColor = QVector4D(
                                (6*i)/255.0f,
                                (6*j)/255.0f,
                                (6*k)/255.0f,
                                1.0f);
                    face.drawPick(mStack.top(),vMat,pMat,pickingColor);

                    //退回一个变换系
                    mStack.pop();
                }
            }
    //退回一个变换系
    mStack.pop();

    QImage image = fbo.toImage(); //fbo is the QOpenGLFramebufferObject
    QRgb rgb = image.pixel(mouseX, mouseY);
    QColor color = QColor(rgb);
    fbo.release();

    if(status == Selected){
        if(color.red()==255&&color.green()==255&&color.blue()==255){
            pickSecond.isPick = false;
            pickSecond.i = 255;
            pickSecond.j = 255;
            pickSecond.k = 255;
            pickSecond.l = 255;
        }else{
            pickSecond.isPick = true;
            pickSecond.i = color.red() / 6;
            pickSecond.j = color.green() / 6;
            pickSecond.k = color.blue() / 6;
            pickSecond.l = color.red() % 6;
        }
    }else if(status == NotPress){
        if(color.red()==255&&color.green()==255&&color.blue()==255){
            pickFirst.isPick = false;
            pickFirst.i = 255;
            pickFirst.j = 255;
            pickFirst.k = 255;
            pickFirst.l = 255;
            status = MoveView;
        }else{
            pickFirst.isPick = true;
            pickFirst.i = color.red() / 6;
            pickFirst.j = color.green() / 6;
            pickFirst.k = color.blue() / 6;
            pickFirst.l = color.red() % 6;
            status = Selected;
        }
    }

}
void Cube::judgePick()
{
    //判断拾取是否有效
    if( status == NotPress||
        status == MoveView||
        pickFirst.isPick==false||
        pickSecond.isPick==false){
    }else{//拾取数据有效
        CubeRotate step;
        if (pickFirst.l == pickSecond.l) {//两次点击了同一个平面
            if (pickFirst.l == 0) {
                if (pickFirst.j == pickSecond.j && pickFirst.k != pickSecond.k) {
                    step.axle = 1;
                    step.layer = cubeOrder - pickFirst.j - 1;
                    if (pickFirst.k - pickSecond.k > 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
                else if (pickFirst.j != pickSecond.j && pickFirst.k == pickSecond.k) {
                    step.axle = 2;
                    step.layer = cubeOrder - pickFirst.k - 1;
                    if (pickFirst.j - pickSecond.j < 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
            }
            else if (pickFirst.l == 1) {
                if (pickFirst.j == pickSecond.j && pickFirst.k != pickSecond.k) {
                    step.axle = 1;
                    step.layer = cubeOrder - pickFirst.j - 1;
                    if (pickFirst.k - pickSecond.k < 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
                else if (pickFirst.j != pickSecond.j && pickFirst.k == pickSecond.k) {
                    step.axle = 2;
                    step.layer = cubeOrder - pickFirst.k - 1;
                    if (pickFirst.j - pickSecond.j > 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
            }
            else if (pickFirst.l == 2) {
                if (pickFirst.i == pickSecond.i && pickFirst.k != pickSecond.k) {
                    step.axle = 0;
                    step.layer = cubeOrder - pickFirst.i - 1;
                    if (pickFirst.k - pickSecond.k < 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
                else if (pickFirst.i != pickSecond.i && pickFirst.k == pickSecond.k) {
                    step.axle = 2;
                    step.layer = cubeOrder - pickFirst.k - 1;
                    if (pickFirst.i - pickSecond.i > 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
            }
            else if (pickFirst.l == 3) {
                if (pickFirst.i == pickSecond.i && pickFirst.k != pickSecond.k) {
                    step.axle = 0;
                    step.layer = cubeOrder - pickFirst.i - 1;
                    if (pickFirst.k - pickSecond.k > 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
                else if (pickFirst.i != pickSecond.i && pickFirst.k == pickSecond.k) {
                    step.axle = 2;
                    step.layer = cubeOrder - pickFirst.k - 1;
                    if (pickFirst.i - pickSecond.i < 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
            }
            else if (pickFirst.l == 4) {
                if (pickFirst.i == pickSecond.i && pickFirst.j != pickSecond.j) {
                    step.axle = 0;
                    step.layer = cubeOrder - pickFirst.i - 1;
                    if (pickFirst.j - pickSecond.j > 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
                else if (pickFirst.i != pickSecond.i && pickFirst.j == pickSecond.j) {
                    step.axle = 1;
                    step.layer = cubeOrder - pickFirst.j - 1;
                    if (pickFirst.i - pickSecond.i < 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
            }
            else if (pickFirst.l == 5) {
                if (pickFirst.i == pickSecond.i && pickFirst.j != pickSecond.j) {
                    step.axle = 0;
                    step.layer = cubeOrder - pickFirst.i - 1;
                    if (pickFirst.j - pickSecond.j < 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
                else if (pickFirst.i != pickSecond.i && pickFirst.j == pickSecond.j) {
                    step.axle = 1;
                    step.layer = cubeOrder - pickFirst.j - 1;
                    if (pickFirst.i - pickSecond.i > 0)
                        step.angle = 1;
                    else
                        step.angle = 3;
                    rotateSteps.push(step);
                }
            }
        }else{
            if (pickFirst.l == 0||pickFirst.l == 1) {
                if(pickSecond.l == 2||pickSecond.l == 3){
                    if(pickFirst.k == pickSecond.k){
                        step.axle = 2;
                        step.layer = cubeOrder - pickFirst.k - 1;
                        step.angle = 2;
                        rotateSteps.push(step);
                    }
                }
                else if(pickSecond.l == 4||pickSecond.l == 5){
                    if(pickFirst.j == pickSecond.j){
                        step.axle = 1;
                        step.layer = cubeOrder - pickFirst.j - 1;
                        step.angle = 2;
                        rotateSteps.push(step);
                    }
                }
            }
            else if (pickFirst.l == 2||pickFirst.l == 3) {
                if(pickSecond.l == 0||pickSecond.l == 1){
                    if(pickFirst.k == pickSecond.k){
                        step.axle = 2;
                        step.layer = cubeOrder - pickFirst.k - 1;
                        step.angle = 2;
                        rotateSteps.push(step);
                    }
                }
                else if(pickSecond.l == 4||pickSecond.l == 5){
                    if(pickFirst.i == pickSecond.i){
                        step.axle = 0;
                        step.layer = cubeOrder - pickFirst.i - 1;
                        step.angle = 2;
                        rotateSteps.push(step);
                    }
                }
            }
            else if (pickFirst.l == 4||pickFirst.l == 5) {
                if(pickSecond.l == 0||pickSecond.l == 1){
                    if(pickFirst.j == pickSecond.j){
                        step.axle = 1;
                        step.layer = cubeOrder - pickFirst.j - 1;
                        step.angle = 2;
                        rotateSteps.push(step);
                    }
                }
                else if(pickSecond.l == 2||pickSecond.l == 3){
                    if(pickFirst.i == pickSecond.i){
                        step.axle = 0;
                        step.layer = cubeOrder - pickFirst.i - 1;
                        step.angle = 2;
                        rotateSteps.push(step);
                    }
                }
            }
        }
    }
    //重置拾取数据
    pickFirst.isPick = false;
    pickFirst.i = 255;
    pickFirst.j = 255;
    pickFirst.k = 255;
    pickFirst.l = 255;
    pickSecond.isPick = false;
    pickSecond.i = 255;
    pickSecond.j = 255;
    pickSecond.k = 255;
    pickSecond.l = 255;
}












