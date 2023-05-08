#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;
//存储最短路径值
int ShortestPathValue[14][14] = { 0 };
//存储具体路径
int ShortestPathMatrix[14][14] = { 0 };
//地点信息
char M_mapName[14][23] = { "四十九中", "小灵童幼儿园","兰州面馆", "犇犇面", "钱柜快捷宾馆", "大鹏食杂店",
                          "华泰大药房", "中医药图书馆", "鸿瑞小宾馆", "招生就业处", "基础医学院", "南京小笼包",
                          "明明旅店","天意超市"
                        };
//距离信息,_distance[0][1] = 50;代表从下标为0到下表为1地点距离为50
int D_distance[14][14] = { 0 };
//边表结点
typedef struct EdgeNode {
    //顶点对应的下标
    int adjvex;
    //权值
    int weight;
    //指向下一个邻接点
    struct EdgeNode* next;
} edgeNode;

//顶点表结点
typedef struct VertexNode {
    //顶点数据
    char data[50];
    //边表头指针
    edgeNode* firstedge;
} VertexNode, AdjList[100];

//集合
typedef struct {
    AdjList adjList;
    //顶点数和边数
    int numVertexes, numEdges;
} GraphadjList;

class AdjacencyList {
public:


    void ShowGraph(GraphadjList* G);

    void Test();

    //初始化地图
    void InitMap(GraphadjList* G);

    //创建地图
    void CreateGraph(GraphadjList* G);

    //计算各个顶点之间最短路径
    void ShortestPath_Floyd(GraphadjList* G, int P[14][14], int D[14][14]);

    //输出路径长度和具体路径
    void ShowShortestResult(int originPos, int endPos);
};

//创建地图
void AdjacencyList::CreateGraph(GraphadjList* G) {
    edgeNode* sjs;
    //读入顶点信息，建立顶点表
    for (int i = 0; i < G->numVertexes; i++)
    {
        //读入顶点信息
        strcpy(G->adjList[i].data, M_mapName[i]);
        //将边表置为空表
        G->adjList[i].firstedge = NULL;
    }
    //头插法建立边表
    for (int i = 0; i < G->numVertexes; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int temp;
            if (D_distance[i][j] != 0 || D_distance[j][i] != 0)
            {
                if (D_distance[i][j] != 0)
                {
                    temp = D_distance[i][j];
                    D_distance[j][i] = D_distance[i][j];
                }
                else
                {
                    temp = D_distance[j][i];
                    D_distance[i][j] = D_distance[j][i];
                }
                sjs = new EdgeNode;
                sjs->adjvex = j;
                sjs->next = G->adjList[i].firstedge;
                sjs->weight = temp;
                G->adjList[i].firstedge = sjs;

                sjs = new EdgeNode;

                sjs->adjvex = i;
                sjs->next = G->adjList[j].firstedge;
                sjs->weight = temp;
                G->adjList[j].firstedge = sjs;
            }
        }
    }
}

void AdjacencyList::Test() {
    cout << "ALL IS OK." << endl;
}

//初始化地图基本数据
void AdjacencyList::InitMap(GraphadjList* G) {
    //输入顶点数和边数
    G->numVertexes = 14;
    G->numEdges = 23;
    D_distance[0][1] = 200;
    D_distance[0][6] = 300;
    D_distance[0][9] = 500;

    D_distance[1][2] = 100;
    D_distance[1][6] = 150;

    D_distance[2][7] = 80;
    D_distance[2][3] = 220;

    D_distance[3][4] = 260;
    D_distance[3][5] = 250;

    D_distance[4][5] = 80;
    D_distance[4][13] = 350;

    D_distance[5][7] = 300;
    D_distance[5][8] = 140;

    D_distance[6][7] = 200; 
    D_distance[6][9] = 220;
    D_distance[6][11] = 400;

    D_distance[7][8] = 250;

    D_distance[8][10] = 100;

    D_distance[9][11] = 400;

    D_distance[10][11] = 200;
    D_distance[10][12] = 140;

    D_distance[11][12] = 160;

    D_distance[12][13] = 150;

}

void AdjacencyList::ShortestPath_Floyd(GraphadjList* G, int P[14][14], int D[14][14]) {
    
    for (int v = 0; v < G->numVertexes; ++v)
    {
        for (int w = 0; w < G->numVertexes; ++w)
        {
            if (D_distance[v][w] == 0 && v != w) {
                D_distance[v][w] = 10000;
            }
            D[v][w] = D_distance[v][w];
            P[v][w] = w;
        }
    }
    for (int k = 0; k < G->numVertexes; ++k)
    {
        for (int v = 0; v < G->numVertexes; ++v)
        {
            for (int w = 0; w < G->numVertexes; ++w)
            {
                if (D[v][w] > D[v][k] + D[k][w])
                {
                    D[v][w] = D[v][k] + D[k][w];
                    P[v][w] = P[v][k];
                }
            }
        }
    }
}

void AdjacencyList::ShowShortestResult(int originPos, int endPos) {
    int temp;
    cout << "地点" << M_mapName[originPos] << "到地点" << M_mapName[endPos] << "最短距离为" << ShortestPathValue[originPos][endPos] << endl;
    temp = ShortestPathMatrix[originPos][endPos];
    cout << "具体路径为：" << M_mapName[originPos] << "——>";
    while (temp != endPos) {
        cout << M_mapName[temp] << "——>";
        temp = ShortestPathMatrix[temp][endPos];
    }
    cout << M_mapName[endPos] << endl;
}


int main() {
    AdjacencyList adjacencyList;
    int originPos, endPos;
    GraphadjList* GA = new GraphadjList;
    adjacencyList.Test();
    adjacencyList.InitMap(GA);
    adjacencyList.CreateGraph(GA);
    adjacencyList.ShortestPath_Floyd(GA, ShortestPathMatrix, ShortestPathValue);
    cout << "地图所有数据已经初始化完成,地图图像已显示" << endl;
    while (1) {
        cout << "请按照图片选择你想去的地方，输入起始点和目的地的序号，以空格间隔。" << endl;
        cout << "标准格式 ：起点 终点 关闭图片，回车" << endl;
        cout << "若输入已完成，请关闭图片。按下回车键，即可显示路径。" << endl;
        system("image1.png");
        cin >> originPos >> endPos;
        adjacencyList.ShowShortestResult(originPos, endPos);
    }

    return 0;
}
