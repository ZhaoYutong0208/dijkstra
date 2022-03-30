#include"dijkstra.h"
#include"topo.h"

//检验输入边数和顶点数的值是否有效，可以自己推算为啥：
//顶点数和边数的关系是：((Vexnum*(Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge) {
    if (Vexnum <= 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
        return false;
    return true;
}

// void creat_topo(int Vexnum,int ratio){

// }

int main() {
    int vexnum;
    double ratio;

    string filename =  "mytopo.txt";
    // string filename;
    // cout << "输入读取的文件名称:" << endl;
    // cin >> filename;

    vexnum = 40;
    // cout << "输入图的顶点个数:" << endl;
    // cin >> vexnum;

    // cout << "输入拓扑中1的比例" << endl;
    // cin >> ratio;

    // create_topo(filename, vexnum, ratio);

    Graph_DG graph(vexnum);
    graph.createGraph(filename);
    graph.print();

    int start;
    cout << "输入路径起点卫星的序号:" << endl;
    cin >> start;
    graph.Dijkstra(start, graph.dist_d);
    graph.stsr(start, graph.dist_s);
    graph.print_path(start, graph.dist_d);
    graph.print_path(start, graph.dist_s);
    system("pause");
    return 0;
}