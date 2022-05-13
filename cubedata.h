#ifndef CUBEDATA_H
#define CUBEDATA_H

#include <queue>
#include <stack>
#include <vector>
#include <set>

using namespace std;

//描述魔方转动
struct CubeRotate {
    int axle;//转动轴
    int layer;//围绕转动轴的层数
    int angle;//旋转角度：angle*90为实际转动角度
};

class CubeData
{
public:
    CubeData();
    CubeData(int cubeOrder);
    CubeData(const CubeData& cubedata);     //复制构造函数
    //相等比较函数
    bool operator == (const CubeData& cubedata);
    bool operator < (const CubeData& cubedata);

    void setCubeOrder(int cubeOrder);       //设置魔方阶数   
    //从魔方数据集更新魔方渲染数据集到faceData
    void toRenderData(vector<vector<vector<vector<int>>>> &faceData);
    void rotateCube(CubeRotate cubeRotate); //转动魔方，改变魔方状态
    queue<CubeRotate> recovery();           //还原魔方算法
    vector<vector<int>>*getData();          //获取cube数据
    void setData(vector<vector<int>>*data); //设置cube数据
private:   
    bool isRecovery();                      //检查是否还原
    queue<CubeRotate> reverseSteps();       //翻转路径

    vector<vector<int>> data[6];            //6个面的数据
    int cubeOrder;                          //魔方阶数
    queue<CubeRotate> recoverPath;          //魔方还原队列

};

class CubeDataCmp
{
public:
    bool operator() (CubeData* cubedataA,CubeData* cubedataB);
};



#endif // CUBEDATA_H










