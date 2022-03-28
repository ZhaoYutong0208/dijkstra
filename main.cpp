#include"dijkstra.h"

//检验输入边数和顶点数的值是否有效，可以自己推算为啥：
//顶点数和边数的关系是：((Vexnum*(Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge) {
    if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
        return false;
    return true;
}
int main() {
    int vexnum;

    string file;
    cout << "输入读取的文件名称:" << endl;
    cin >> file;

    cout << "输入图的顶点个数:" << endl;
    cin >> vexnum;// 待改成读取形式而非输入
    
    Graph_DG graph(vexnum);
    graph.createGraph(file);
    graph.print();

    int start;
    cout << "输入路径起点卫星的序号:" << endl;
    cin >> start;
    graph.Dijkstra(start);
    graph.print_path(start);
    system("pause");
    return 0;
}