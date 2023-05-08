#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;
//�洢���·��ֵ
int ShortestPathValue[14][14] = { 0 };
//�洢����·��
int ShortestPathMatrix[14][14] = { 0 };
//�ص���Ϣ
char M_mapName[14][23] = { "��ʮ����", "С��ͯ�׶�԰","�������", "�Ġ���", "Ǯ���ݱ���", "����ʳ�ӵ�",
                          "��̩��ҩ��", "��ҽҩͼ���", "����С����", "������ҵ��", "����ҽѧԺ", "�Ͼ�С����",
                          "�����õ�","���ⳬ��"
                        };
//������Ϣ,_distance[0][1] = 50;������±�Ϊ0���±�Ϊ1�ص����Ϊ50
int D_distance[14][14] = { 0 };
//�߱���
typedef struct EdgeNode {
    //�����Ӧ���±�
    int adjvex;
    //Ȩֵ
    int weight;
    //ָ����һ���ڽӵ�
    struct EdgeNode* next;
} edgeNode;

//�������
typedef struct VertexNode {
    //��������
    char data[50];
    //�߱�ͷָ��
    edgeNode* firstedge;
} VertexNode, AdjList[100];

//����
typedef struct {
    AdjList adjList;
    //�������ͱ���
    int numVertexes, numEdges;
} GraphadjList;

class AdjacencyList {
public:


    void ShowGraph(GraphadjList* G);

    void Test();

    //��ʼ����ͼ
    void InitMap(GraphadjList* G);

    //������ͼ
    void CreateGraph(GraphadjList* G);

    //�����������֮�����·��
    void ShortestPath_Floyd(GraphadjList* G, int P[14][14], int D[14][14]);

    //���·�����Ⱥ;���·��
    void ShowShortestResult(int originPos, int endPos);
};

//������ͼ
void AdjacencyList::CreateGraph(GraphadjList* G) {
    edgeNode* sjs;
    //���붥����Ϣ�����������
    for (int i = 0; i < G->numVertexes; i++)
    {
        //���붥����Ϣ
        strcpy(G->adjList[i].data, M_mapName[i]);
        //���߱���Ϊ�ձ�
        G->adjList[i].firstedge = NULL;
    }
    //ͷ�巨�����߱�
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

//��ʼ����ͼ��������
void AdjacencyList::InitMap(GraphadjList* G) {
    //���붥�����ͱ���
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
    cout << "�ص�" << M_mapName[originPos] << "���ص�" << M_mapName[endPos] << "��̾���Ϊ" << ShortestPathValue[originPos][endPos] << endl;
    temp = ShortestPathMatrix[originPos][endPos];
    cout << "����·��Ϊ��" << M_mapName[originPos] << "����>";
    while (temp != endPos) {
        cout << M_mapName[temp] << "����>";
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
    cout << "��ͼ���������Ѿ���ʼ�����,��ͼͼ������ʾ" << endl;
    while (1) {
        cout << "�밴��ͼƬѡ������ȥ�ĵط���������ʼ���Ŀ�ĵص���ţ��Կո�����" << endl;
        cout << "��׼��ʽ ����� �յ� �ر�ͼƬ���س�" << endl;
        cout << "����������ɣ���ر�ͼƬ�����»س�����������ʾ·����" << endl;
        system("image1.png");
        cin >> originPos >> endPos;
        adjacencyList.ShowShortestResult(originPos, endPos);
    }

    return 0;
}
