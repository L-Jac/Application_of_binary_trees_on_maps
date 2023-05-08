import numpy as np
from tkinter import *
from PyQt5 import QtWidgets
from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QApplication, QMainWindow
import sys

# 存储最短路径值
ShortestPathValue = np.zeros((14, 14))
# 存储具体路径
ShortestPathMatrix = np.zeros((14, 14), dtype=int)
# 地点信息
M_mapName = ["四十九中", "小灵童幼儿园", "兰州面馆", "犇犇面", "钱柜快捷宾馆", "大鹏食杂店",
             "华泰大药房", "中医药图书馆", "鸿瑞小宾馆", "招生就业处", "基础医学院", "南京小笼包",
             "明明旅店", "天意超市"]
# 距离信息，D_distance[0][1] = 50;代表从下标为0到下表为1地点距离为50
D_distance = np.zeros((14, 14), dtype=int)


# 边表结点
class EdgeNode:
    def __init__(self, adjvex, weight):
        # 顶点对应的下标
        self.adjvex = adjvex
        # 权值
        self.weight = weight
        # 指向下一个邻接点
        self.next = None


# 顶点表结点
class VertexNode:
    def __init__(self, data):
        # 顶点数据
        self.data = data
        # 边表头指针
        self.firstedge = None


# 集合
class GraphadjList:
    def __init__(self):
        self.adjList = [VertexNode(data) for data in M_mapName]
        # 顶点数和边数
        self.numVertexes = len(self.adjList)
        self.numEdges = 0


def ShowShortestResult(originPos, endPos):
    temp = ShortestPathMatrix[originPos][endPos]
    words = [f"地点{M_mapName[originPos]}到地点{M_mapName[endPos]}最短距离为{ShortestPathMatrix[originPos][endPos]}\n",
             f"具体路径为：\n{M_mapName[originPos]}——>"]
    while temp != endPos:
        words.append(f"{M_mapName[temp]}——>")
        temp = ShortestPathMatrix[temp][endPos]
    words.append(M_mapName[endPos])
    app = QApplication(sys.argv)
    win = QMainWindow()
    win.setGeometry(200, 200, 1600, 700)
    win.setWindowTitle("My PyQt5 Window")

    sentence = ""
    for word in words:
        sentence += word

    label = QtWidgets.QLabel(win)
    label.setText(sentence)
    label.move(50, 50)
    label.resize(1400, 500)

    # 设置字体
    font = QFont()
    font.setPointSize(20)  # 设置字体大小为20像素
    label.setFont(font)

    # 启用自动换行
    label.setWordWrap(True)

    win.show()
    sys.exit(app.exec_())


def CreateGraph(G):
    # 读入顶点信息，建立顶点表
    for i in range(G.numVertexes):
        # 读入顶点信息
        G.adjList[i].data = M_mapName[i]
        # 将边表置为空表
        G.adjList[i].firstedge = None
    # 头插法建立边表
    for i in range(G.numVertexes):
        for j in range(i):
            if D_distance[i][j] != 0 or D_distance[j][i] != 0:
                if D_distance[i][j] != 0:
                    temp = D_distance[i][j]
                    D_distance[j][i] = D_distance[i][j]
                else:
                    temp = D_distance[j][i]
                    D_distance[i][j] = D_distance[j][i]
                sjs = EdgeNode(j, temp)
                sjs.next = G.adjList[i].firstedge
                G.adjList[i].firstedge = sjs

                sjs = EdgeNode(i, temp)
                sjs.next = G.adjList[j].firstedge
                G.adjList[j].firstedge = sjs


def Test():
    print("ALL IS OK.")


def InitMap(G):
    # 输入顶点数和边数
    G.numVertexes = 14
    G.numEdges = 23
    D_distance[0][1] = 200
    D_distance[0][6] = 300
    D_distance[0][9] = 500

    D_distance[1][2] = 100
    D_distance[1][6] = 150

    D_distance[2][7] = 80
    D_distance[2][3] = 220

    D_distance[3][4] = 260
    D_distance[3][5] = 250

    D_distance[4][5] = 80
    D_distance[4][13] = 350

    D_distance[5][7] = 300
    D_distance[5][8] = 140

    D_distance[6][7] = 200
    D_distance[6][9] = 220
    D_distance[6][11] = 400

    D_distance[7][8] = 250

    D_distance[8][10] = 100

    D_distance[9][11] = 400

    D_distance[10][11] = 200
    D_distance[10][12] = 140

    D_distance[11][12] = 160

    D_distance[12][13] = 150


def ShowGraph(G):
    for i in range(G.numVertexes):
        print(f"顶点{i}: {G.adjList[i].data}--firstedge--", end="")
        p = G.adjList[i].firstedge
        while p:
            print(f"{p.adjvex}--Weight: {p.weight}--Next--", end="")
            p = p.next
        print("--NULL")


def ShortestPath_Floyd(G, P, D):
    for v in range(G.numVertexes):
        for w in range(G.numVertexes):
            if D_distance[v][w] == 0 and v != w:
                D_distance[v][w] = 10000
            D[v][w] = D_distance[v][w]
            P[v][w] = w
    for k in range(G.numVertexes):
        for v in range(G.numVertexes):
            for w in range(G.numVertexes):
                if D[v][w] > D[v][k] + D[k][w]:
                    D[v][w] = D[v][k] + D[k][w]
                    P[v][w] = P[v][k]


def get_input(a, b):
    root = Tk()

    text1 = StringVar()
    text1.set(a)
    entry1 = Entry(root, textvariable=text1, width=120)
    entry1.pack()

    text2 = StringVar()
    text2.set(b)
    entry2 = Entry(root, textvariable=text2, width=120)
    entry2.pack()
    lin1 = a
    lin2 = b

    # 加载图片
    image1 = PhotoImage(file="text1.png")
    image2 = PhotoImage(file="image1.png")

    # 在Label控件中显示图片
    label1 = Label(root, image=image1)
    label1.pack(side=LEFT)
    label2 = Label(root, image=image2)
    label2.pack(side=LEFT)

    def callback():
        nonlocal lin1, lin2
        lin1 = text1.get()
        lin2 = text2.get()
        root.destroy()

    b = Button(root, text="OK", width=10, command=callback)
    b.pack(side=BOTTOM, anchor=W)
    root.mainloop()
    return lin1, lin2


def main():
    GA = GraphadjList()
    Test()
    InitMap(GA)
    CreateGraph(GA)
    ShortestPath_Floyd(GA, ShortestPathMatrix, ShortestPathValue)
    print("地图所有数据已经初始化完成,地图图像已显示")
    print("请按照图片选择你想去的地方，输入起始点和目的地的序号")
    origin_pos, end_pos = get_input("出发点", "目的地")
    origin_pos = ord(origin_pos) - 65
    end_pos = ord(end_pos) - 65
    ShowShortestResult(origin_pos, end_pos)


if __name__ == "__main__":
    main()
