#include "cubedata.h"

CubeData::CubeData()
{
    //设置魔方阶数默认为3
    setCubeOrder(3);
}
CubeData::CubeData(int cubeOrder)
{
    //设置魔方阶数
    setCubeOrder(cubeOrder);
}
CubeData::CubeData(const CubeData& cubeData)
{
    cubeOrder = cubeData.cubeOrder;
    setCubeOrder(cubeOrder);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < cubeOrder; j++) {
            for (int k = 0; k < cubeOrder; k++) {
                data[i][j][k] = cubeData.data[i][j][k];
            }
        }
    }
    recoverPath = cubeData.recoverPath;
}


//相等比较函数
bool CubeData::operator == (const CubeData& cubeData)
{
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < cubeOrder; j++) {
            for (int k = 0; k < cubeOrder; k++) {
                if(data[i][j][k] != cubeData.data[i][j][k]){
                    return false;
                }
            }
        }
    }
    return true;
}
bool CubeData::operator < (const CubeData& cubeData)
{
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < cubeOrder; j++) {
            for (int k = 0; k < cubeOrder; k++) {
                if(data[i][j][k] < cubeData.data[i][j][k]){
                    return true;
                }else if(data[i][j][k] > cubeData.data[i][j][k]){
                    return false;
                }
            }
        }
    }
    return false;
}


void CubeData::setCubeOrder(int cubeOrder)
{
    this->cubeOrder = cubeOrder;
    for (int i = 0; i < 6; i++) {
        data[i].resize(cubeOrder);
        for (int j = 0; j < cubeOrder; j++) {
            data[i][j].resize(cubeOrder);
            for (int k = 0; k < cubeOrder; k++) {
                data[i][j][k] = i;
            }
        }
    }
}
void CubeData::toRenderData(vector<vector<vector<vector<int>>>> &faceData)
{
    for (int i = 0; i < cubeOrder; i++) {
        for (int j = 0; j < cubeOrder; j++) {
            faceData[cubeOrder - 1][i][j][0] = data[0][i][j];
            faceData[0][i][j][1] = data[1][i][j];
            faceData[i][cubeOrder - 1][j][2] = data[2][i][j];
            faceData[i][0][j][3] = data[3][i][j];
            faceData[i][j][cubeOrder - 1][4] = data[4][i][j];
            faceData[i][j][0][5] = data[5][i][j];
        }
    }
}
void CubeData::rotateCube(CubeRotate cubeRotate)
{
    int axle = cubeRotate.axle;
    int layer = cubeRotate.layer;
    int angle= cubeRotate.angle;
    /*----------------------------------------边缘块的转动--------------------------------------*/
    for (int i = 0; i < cubeOrder; i++) {
        int temp;//临时变量
        if (axle == 0) {//x轴转动
            temp = data[2][cubeOrder - layer - 1][cubeOrder - i - 1];
            if (angle == 1) {
                data[2][cubeOrder - layer - 1][cubeOrder - i - 1] = data[5][cubeOrder - layer - 1][cubeOrder - i - 1];
                data[5][cubeOrder - layer - 1][cubeOrder - i - 1] = data[3][cubeOrder - layer - 1][i];
                data[3][cubeOrder - layer - 1][i] = data[4][cubeOrder - layer - 1][i];
                data[4][cubeOrder - layer - 1][i] = temp;
            }
            else if(angle == 2){
                temp = data[2][cubeOrder - layer - 1][cubeOrder - i - 1];
                data[2][cubeOrder - layer - 1][cubeOrder - i - 1] = data[3][cubeOrder - layer - 1][i];
                data[3][cubeOrder - layer - 1][i] = temp;
                temp = data[4][cubeOrder - layer - 1][i];
                data[4][cubeOrder - layer - 1][i] = data[5][cubeOrder - layer - 1][cubeOrder - i - 1];
                data[5][cubeOrder - layer - 1][cubeOrder - i - 1] = temp;
            }
            else if(angle == 3){
                data[2][cubeOrder - layer - 1][cubeOrder - i - 1] = data[4][cubeOrder - layer - 1][i];
                data[4][cubeOrder - layer - 1][i] = data[3][cubeOrder - layer - 1][i];
                data[3][cubeOrder - layer - 1][i] = data[5][cubeOrder - layer - 1][cubeOrder - i - 1];
                data[5][cubeOrder - layer - 1][cubeOrder - i - 1] = temp;
            }
        }
        else if (axle == 1) {//y轴转动
            temp = data[0][cubeOrder - layer - 1][cubeOrder - i - 1];
            if (angle == 1) {
                data[0][cubeOrder - layer - 1][cubeOrder - i - 1] = data[4][i][cubeOrder - layer - 1];
                data[4][i][cubeOrder - layer - 1] = data[1][cubeOrder - layer - 1][i];
                data[1][cubeOrder - layer - 1][i] = data[5][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[5][cubeOrder - i - 1][cubeOrder - layer - 1] = temp;
            }
            else if(angle == 2){
                temp = data[0][cubeOrder - layer - 1][cubeOrder - i - 1];
                data[0][cubeOrder - layer - 1][cubeOrder - i - 1] = data[1][cubeOrder - layer - 1][i];
                data[1][cubeOrder - layer - 1][i] = temp;
                temp = data[4][i][cubeOrder - layer - 1];
                data[4][i][cubeOrder - layer - 1] = data[5][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[5][cubeOrder - i - 1][cubeOrder - layer - 1] = temp;
            }
            else if(angle == 3){
                data[0][cubeOrder - layer - 1][cubeOrder - i - 1] = data[5][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[5][cubeOrder - i - 1][cubeOrder - layer - 1] = data[1][cubeOrder - layer - 1][i];
                data[1][cubeOrder - layer - 1][i] = data[4][i][cubeOrder - layer - 1];
                data[4][i][cubeOrder - layer - 1] = temp;
            }
        }
        else if (axle == 2) {//z轴转动
            temp = data[2][i][cubeOrder - layer - 1];
            if (angle == 1) {
                data[2][i][cubeOrder - layer - 1] = data[0][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[0][cubeOrder - i - 1][cubeOrder - layer - 1] = data[3][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[3][cubeOrder - i - 1][cubeOrder - layer - 1] = data[1][i][cubeOrder - layer - 1];
                data[1][i][cubeOrder - layer - 1] = temp;
            }
            else if(angle == 2){
                temp = data[0][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[0][cubeOrder - i - 1][cubeOrder - layer - 1] = data[1][i][cubeOrder - layer - 1];
                data[1][i][cubeOrder - layer - 1] = temp;
                temp = data[2][i][cubeOrder - layer - 1];
                data[2][i][cubeOrder - layer - 1] = data[3][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[3][cubeOrder - i - 1][cubeOrder - layer - 1] = temp;
            }
            else if(angle == 3){
                data[2][i][cubeOrder - layer - 1] = data[1][i][cubeOrder - layer - 1];
                data[1][i][cubeOrder - layer - 1] = data[3][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[3][cubeOrder - i - 1][cubeOrder - layer - 1] = data[0][cubeOrder - i - 1][cubeOrder - layer - 1];
                data[0][cubeOrder - i - 1][cubeOrder - layer - 1] = temp;
            }
        }
    }
    /*----------------------------------------外围面颜色的转动--------------------------------------*/
    //如果转动最表层需要更新表层面的信息
    if (layer == 0 || layer == cubeOrder - 1) {
        int face;//决定要变化那个面的数据
        if (layer == 0) {
            if (axle == 0)
                face = 0;
            else if (axle == 1)
                face = 2;
            else if (axle == 2)
                face = 4;
        }
        else if (layer == cubeOrder - 1){
            if (axle == 0)
                face = 1;
            else if (axle == 1)
                face = 3;
            else if (axle == 2)
                face = 5;
        }
        /*---------------二次置换法----------------*/
        if(angle == 1||angle == 3){
            //先执行转置操作
            for (int i = 0; i < cubeOrder; i++) {
                for (int j = 0; j < i; j++) {
                    int temp = data[face][i][j];
                    data[face][i][j] = data[face][j][i];
                    data[face][j][i] = temp;
                }
            }
            //后执行交换操作
            for (int i = 0; i < cubeOrder; i++) {
                for (int j = 0; j < cubeOrder / 2; j++) {
                    int temp;
                    if ((angle == 1 && (axle == 0 || axle == 2)) || (angle == 3 && axle == 1)) {//逆时针旋转
                        temp = data[face][j][i];
                        data[face][j][i] = data[face][cubeOrder - j - 1][i];
                        data[face][cubeOrder - j - 1][i] = temp;
                    }
                    else if((angle == 3 && (axle == 0 || axle == 2)) || (angle == 1 && axle == 1)) {//顺时针旋转
                        temp = data[face][i][j];
                        data[face][i][j] = data[face][i][cubeOrder - j - 1];
                        data[face][i][cubeOrder - j - 1] = temp;
                    }
                }
            }
        }
        else if(angle == 2){
            //后执行交换操作
            for (int i = 0; i < cubeOrder; i++) {
                for (int j = 0; j < cubeOrder / 2; j++) {
                    int temp;
                    temp = data[face][j][i];
                    data[face][j][i] = data[face][cubeOrder - j - 1][i];
                    data[face][cubeOrder - j - 1][i] = temp;
                }
            }
            for (int i = 0; i < cubeOrder; i++) {
                for (int j = 0; j < cubeOrder / 2; j++) {
                    int temp;
                    temp = data[face][i][j];
                    data[face][i][j] = data[face][i][cubeOrder - j - 1];
                    data[face][i][cubeOrder - j - 1] = temp;
                }
            }
        }
    }


}
queue<CubeRotate> CubeData::recovery()
{
    //清空队列
    recoverPath = queue<CubeRotate>();
    //保存所有可能的变换步骤
    vector<CubeRotate> eachPossiable = {
        {0,0,1},
        {0,0,2},
        {0,0,3},
        {1,0,1},
        {1,0,2},
        {1,0,3},
        {2,0,1},
        {2,0,2},
        {2,0,3},
    };
    //正向查找队列
    queue<CubeData*> shouldHandleLeft;
    //逆向查找队列
    queue<CubeData*> shouldHandleRight;
    //正向状态集合，保存正向查找产生的所有状态
    set<CubeData*,CubeDataCmp>statusGatherLeft;
    //逆向状态集合，保存逆向查找产生的所有状态
    set<CubeData*,CubeDataCmp>statusGatherRight;

    //初始化
    CubeData *temp;
    //原状态进入正向查找队列
    temp = new CubeData(*this);
    statusGatherLeft.insert(temp);
    shouldHandleLeft.push(temp);

    //目的状态进入逆向查找队列
    temp = new CubeData(cubeOrder);
    //初始化目的状态
    for(int i=0;i<cubeOrder;i++){
        for(int j=0;j<cubeOrder;j++){
            if(data[1][0][0]==0)
                temp->data[0][i][j]=1;
            else if(data[1][0][0]==1)
                temp->data[0][i][j]=0;
            else if(data[1][0][0]==2)
                temp->data[0][i][j]=3;
            else if(data[1][0][0]==3)
                temp->data[0][i][j]=2;
            else if(data[1][0][0]==4)
                temp->data[0][i][j]=5;
            else if(data[1][0][0]==5)
                temp->data[0][i][j]=4;

            if(data[3][0][0]==0)
                temp->data[2][i][j]=1;
            else if(data[3][0][0]==1)
                temp->data[2][i][j]=0;
            else if(data[3][0][0]==2)
                temp->data[2][i][j]=3;
            else if(data[3][0][0]==3)
                temp->data[2][i][j]=2;
            else if(data[3][0][0]==4)
                temp->data[2][i][j]=5;
            else if(data[3][0][0]==5)
                temp->data[2][i][j]=4;

            if(data[5][0][0]==0)
                temp->data[4][i][j]=1;
            else if(data[5][0][0]==1)
                temp->data[4][i][j]=0;
            else if(data[5][0][0]==2)
                temp->data[4][i][j]=3;
            else if(data[5][0][0]==3)
                temp->data[4][i][j]=2;
            else if(data[5][0][0]==4)
                temp->data[4][i][j]=5;
            else if(data[5][0][0]==5)
                temp->data[4][i][j]=4;
            temp->data[1][i][j]=data[1][0][0];
            temp->data[3][i][j]=data[3][0][0];
            temp->data[5][i][j]=data[5][0][0];
        }
    }
    statusGatherRight.insert(temp);
    shouldHandleRight.push(temp);

    //是否break关键字
    bool shouldBreak = false;
    while(!shouldBreak){
        int size;
        size = shouldHandleLeft.size();
        for(int i=0;i<size;i++){
            //取出待处理项
            CubeData* handleLeft = shouldHandleLeft.front();
            shouldHandleLeft.pop();
            //检查逆向状态集合中是否存在此状态
            if(statusGatherRight.find(handleLeft) != statusGatherRight.end()){
                //取出当前状态
                CubeData *temp = *statusGatherRight.find(handleLeft);
                recoverPath = handleLeft->recoverPath;
                //获取翻转后的步骤
                queue<CubeRotate>steps = temp->reverseSteps();

                while(!steps.empty()){
                    recoverPath.push(steps.front());
                    steps.pop();
                }
                shouldBreak = true;
                break;
            }

            //遍历产生所有可能结果
            for(int j=0;j<eachPossiable.size();j++){
                CubeData *newStatus = new CubeData(*handleLeft);
                //转动到新状态
                newStatus->rotateCube(eachPossiable[j]);
                newStatus->recoverPath.push(eachPossiable[j]);

                //如果集合中没有此状态，则插入成功，将其加入待处理队列
                if(statusGatherLeft.insert(newStatus).second == true){
                    shouldHandleLeft.push(newStatus);
                }
                //如果集合中有此状态，则插入失败
                else{
                    //删除此状态
                    delete newStatus;
                    newStatus = nullptr;
                }
            }
        }
        size = shouldHandleRight.size();
        for(int i=0;i<size;i++){
            CubeData* handleRight = shouldHandleRight.front();
            shouldHandleRight.pop();
            //检查逆向状态集合中是否存在此状态
            if(statusGatherLeft.find(handleRight) != statusGatherLeft.end()){
                //取出当前状态
                CubeData *temp = *statusGatherLeft.find(handleRight);
                recoverPath = temp->recoverPath;
                //获取翻转后的步骤
                queue<CubeRotate>steps = handleRight->reverseSteps();

                while(!steps.empty()){
                    recoverPath.push(steps.front());
                    steps.pop();
                }
                shouldBreak = true;
                break;
            }

            //遍历产生所有可能结果
            for(int j=0;j<eachPossiable.size();j++){
                CubeData *newStatus = new CubeData(*handleRight);
                //转动到新状态
                newStatus->rotateCube(eachPossiable[j]);
                newStatus->recoverPath.push(eachPossiable[j]);


                //如果集合中没有此状态，则插入成功，将其加入待处理队列
                if(statusGatherRight.insert(newStatus).second == true){
                    shouldHandleRight.push(newStatus);
                }
                //如果集合中有此状态，则插入失败
                else{
                    //删除此状态
                    delete newStatus;
                    newStatus = nullptr;
                }
            }
        }
    }

    //遍历关联容器释放内存
    for(auto i=statusGatherLeft.begin();i!=statusGatherLeft.end();i++){
        delete (*i);
    }
    for(auto i=statusGatherRight.begin();i!=statusGatherRight.end();i++){
        delete (*i);
    }

    return recoverPath;
}
vector<vector<int>>* CubeData::getData(){
    return data;
}
void CubeData::setData(vector<vector<int>>*data){
    if(data[0].size()<0)return;
    for(int i=0;i<6;i++){
        for(int j=0;j<cubeOrder;j++){
            for(int k=0;k<cubeOrder;k++){
                this->data[i][j][k]=data[i][j][k];
            }
        }
    }

}


bool CubeData::isRecovery()
{
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < cubeOrder; j++) {
            for (int k = 0; k < cubeOrder; k++) {
                if(data[i][j][k] != data[i][0][0]){
                    return false;
                }
            }
        }
    }
    return true;
}
queue<CubeRotate> CubeData::reverseSteps()
{
    queue<CubeRotate> steps;
    stack<CubeRotate> stepsStack;
    for(int i=0;i<recoverPath.size();i++){
        CubeRotate step = recoverPath.front();
        recoverPath.push(recoverPath.front());
        recoverPath.pop();
        //将转动步骤设置为反向
        if(step.angle==1)
            step.angle=3;
        else if(step.angle==3)
            step.angle=1;
        else if(step.angle==2)
            step.angle=2;
        stepsStack.push(step);
    }
    while(!stepsStack.empty()){
        steps.push(stepsStack.top());
        stepsStack.pop();
    }
    return steps;
}


bool CubeDataCmp::operator() (CubeData* cubedataA,CubeData* cubedataB)
{
    return (*cubedataA)<(*cubedataB);
}
