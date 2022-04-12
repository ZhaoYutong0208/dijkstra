#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

#include"Dijkstra.h"

//构造函数
Graph_DG::Graph_DG(int vexnum) {
// Graph_DG::Graph_DG(int vexnum, int edge) {
    //初始化顶点数和边数
    this->vexnum = vexnum;
    // this->edge = edge;
    //为邻接矩阵开辟空间和赋初值
    arc = new int*[this->vexnum];
    dist_d= new Dist[this->vexnum];
    dist_d_f= new Dist[this->vexnum];
    dist_s= new Dist[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) {
        //二维数组，vexnum*vexnum
        arc[i] = new int[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            //邻接矩阵初始化为无穷大
                arc[i][k] = INT_MAX;
        }
    }
}
//析构函数
Graph_DG::~Graph_DG() {
    delete[] dist_d;
    delete[] dist_d_f;
    delete[] dist_s;
    for (int i = 0; i < this->vexnum; i++) {
        delete this->arc[i];
    }
    delete arc;
}

// 判断我们每次输入的的边的信息是否合法
//顶点从1开始编号
bool Graph_DG::check_edge_value(int start, int end, int weight) {
    if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

void Graph_DG::createGraph(string file) {
    cout << "开始读取文件" << endl;
    int  n = 0;
    ifstream in( file , ios::in);
    if (!in.is_open())
    {
        cout <<  "Error: opening file fail"  << endl;
        exit (1);
    }
    int start = 0;
    while (!in.eof()) {
        for (int end = 0; end < vexnum; end++){
            in >> arc[start][end];
        }
        start++;
    }
    for (int i = 0; i < vexnum; i++){
        for (int j = 0; j < vexnum; j++){
            if(arc[i][j] == 0){
                arc[i][j] = INT_MAX;
            }
            else{
                arc[i][j] = 1 + (int)(10.0 * rand() / (RAND_MAX + 1.0));
            }
        }
    }
}


void Graph_DG::print_graph() {
    cout << "图的邻接矩阵为：" << endl;
    int count_row = 0; //打印行的标签
    int count_col = 0; //打印列的标签
    //开始打印
    while (count_row != this->vexnum) {
        count_col = 0;
        while (count_col != this->vexnum) {
            if (arc[count_row][count_col] == INT_MAX)
                cout << "∞" << " ";
            else
            cout << arc[count_row][count_col] << " ";
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}
void Graph_DG::Dijkstra(int begin, Dist *dist){
    //begin从1开始
    //首先初始化我们的dist数组
    int i;
    for (i = 0; i < this->vexnum; i++) {
        //设置当前的路径
        // dist[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
        // dist[i].path[0] = begin;
        // dist[i].path[1] = i + 1;
        dist[i].head = new ListNode(begin);
        // dist[i].head->val = begin;
        dist[i].tail = new ListNode(i + 1);
        // dist[i].head->next->val = i + 1;
        // dist[i].head->next->next = nullptr;
        dist[i].head->next = dist[i].tail;
        dist[i].value = arc[begin - 1][i];
    }
    //设置起点的到起点的路径为0
    dist[begin - 1].value = 0;
    dist[begin - 1].visit = true;

    int count = 1;
    //计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
    while (count != this->vexnum) {
        //temp用于保存当前dist数组中最小的那个下标
        //min记录的当前的最小值
        int temp=0;//temp从0开始
        int min = INT_MAX;
        for (i = 0; i < this->vexnum; i++) {
            if (!dist[i].visit && dist[i].value<min) {
                if(i+1 != begin){
                    min = dist[i].value;
                    temp = i;
                }
            }
        }
        // cout << temp + 1 << "  "<<min << endl;
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dist[temp].visit = true;
        ++count;
        for (i = 0; i < this->vexnum; i++) {
            //注意这里的条件arc[temp][i]!=INT_MAX必须加，不然会出现溢出，从而造成程序异常
            if (!dist[i].visit && arc[temp][i]!=INT_MAX && (dist[temp].value + arc[temp][i]) < dist[i].value) {
                //如果新得到的边可以影响其他为访问的顶点，那就进行合法性的判断
                bool flag = true;
                // dijkstra省去合法性判断
                // for (int j = 0; dist[temp].path[j] != temp +1;j++){
                //     // cout << dist[temp].path[j] << " pay attention ";
                //     // cout << j << " " << i << " " << arc[j][i] << endl;
                //     if(arc[j][i] != INT_MAX){
                //          flag = false;
                //         // break;
                //     }
                // }
                // cout << "another round" << endl;
                if(flag){
                    //合法，更新它的最短路径和长度
                    dist[i].value = dist[temp].value + arc[temp][i];
                    // dist[i].path = dist[temp].path + "-->v" + to_string(i + 1);
                    // int k = 0;
                    // for (k = 0; dist[temp].path[k] != 0;k++){
                    //     dist[i].path[k] = dist[temp].path[k];
                    // }
                    // dist[i].path[k] = i + 1;
                    // 把dist[temp].path链表内容拷贝到dist[i].path
                    ListNode *p = dist[temp].head;
                    ListNode *q = dist[i].head;
                    while(p->next != nullptr){
                        p = p->next;
                        ListNode *tempNode = new ListNode(p->val);
                        q->next = tempNode;
                        q = tempNode;
                    }
                    q->next = dist[i].tail;
                }
            }
        }
    }
}

void Graph_DG::stsr(int begin, Dist *dist){
    //begin从1开始
    //首先初始化我们的dist数组
    int i;
    for (i = 0; i < this->vexnum; i++) {
        //设置当前的路径
        // dist[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
        // dist[i].path[0] = begin;
        // dist[i].path[1] = i + 1;
        dist[i].head = new ListNode(begin);
        // dist[i].head->val = begin;
        dist[i].tail = new ListNode(i + 1);
        // dist[i].head->next->val = i + 1;
        // dist[i].head->next->next = nullptr;
        dist[i].head->next = dist[i].tail;
        dist[i].value = arc[begin - 1][i];
    }
    //设置起点的到起点的路径为0
    dist[begin - 1].value = 0;
    dist[begin - 1].visit = true;

    int count = 1;
    //计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
    while (count != this->vexnum) {
        //temp用于保存当前dist数组中最小的那个下标
        //min记录的当前的最小值
        int temp=0;//temp从0开始
        int min = INT_MAX;
        for (i = 0; i < this->vexnum; i++) {
            if (!dist[i].visit && dist[i].value<min) {
                if(i+1 != begin){
                    min = dist[i].value;
                    temp = i;
                }
            }
        }
        // cout << temp + 1 << "  "<<min << endl;
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dist[temp].visit = true;
        ++count;
        for (i = 0; i < this->vexnum; i++) {
            //注意这里的条件arc[temp][i]!=INT_MAX必须加，不然会出现溢出，从而造成程序异常
            if (!dist[i].visit && arc[temp][i]!=INT_MAX && (dist[temp].value + arc[temp][i]) < dist[i].value) {
                //如果新得到的边可以影响其他为访问的顶点，那就进行合法性的判断
                bool flag = true;
                // for (int j = 0; dist[temp].path[j] != temp +1;j++){
                //     // cout << dist[temp].path[j] << " pay attention ";
                //     // cout << j << " " << i << " " << arc[j][i] << endl;
                //     if(arc[j][i] != INT_MAX){
                //         flag = false;
                //         // break;
                //     }
                // }
                ListNode *p = dist[temp].head;
                while(p->next != nullptr){
                    int j = (p->val) - 1;
                    if(arc[j][i] != INT_MAX){
                        flag = false;
                        // break;
                    }
                    p = p->next;
                }
                
                // cout << "another round" << endl;
                if(flag){
                    //合法，更新它的最短路径和长度
                    dist[i].value = dist[temp].value + arc[temp][i];
                    // dist[i].path = dist[temp].path + "-->v" + to_string(i + 1);
                    // int k = 0;
                    // for (k = 0; dist[temp].path[k] != 0;k++){
                    //     dist[i].path[k] = dist[temp].path[k];
                    // }
                    // dist[i].path[k] = i + 1;
                    // 把dist[temp].path链表内容拷贝到dist[i].path
                    ListNode *p = dist[temp].head;
                    ListNode *q = dist[i].head;
                    while(p->next != nullptr){
                        p = p->next;
                        ListNode *tempNode = new ListNode(p->val);
                        q->next = tempNode;
                        q = tempNode;
                    }
                    q->next = dist[i].tail;
                }
            }
        }
    }
}


void Graph_DG::fix_d(Dist *dist_d, Dist *dist_d_f){
    int begin = dist_d[1].head->val;
    cout << begin << endl;
    for (int i = 0; i < this->vexnum; i++) {
        cout << i << endl;
        //设置当前的路径
        // dist[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
        // dist[i].path[0] = begin;
        // dist[i].path[1] = i + 1;
        dist_d_f[i].head = new ListNode(begin);
        // dist[i].head->val = begin;
        dist_d_f[i].tail = new ListNode(i + 1);
        // dist[i].head->next->val = i + 1;
        // dist[i].head->next->next = nullptr;
        dist_d_f[i].head->next = dist_d_f[i].tail;
        dist_d_f[i].value = arc[begin - 1][i];
    }
    //设置起点的到起点的路径为0
    dist_d_f[begin - 1].value = 0;

    for(int i = 0; i < this->vexnum; i++){// i表示第i个卫星节点
        // if((dist_s[i].value == INT_MAX) && (dist_d[i].value != INT_MAX)){
        if(dist_d[i].value != INT_MAX){
            // 对到i的卫星路线进行修正,从dist_d到dist_d_f的部分copy
            ListNode *p = dist_d[i].head;
            ListNode *q = dist_d_f[i].head;
            dist_d_f[i].value = 0;
            while(p->next != nullptr){
                if(i == 1)cout << p->val<<endl;
                int m = (p->val) - 1;
                ListNode *tempNode = new ListNode(p->next->val);// 新节点，用于加在q后面
                // 处理有可能成环的情况
                ListNode *loop_des = nullptr;
                if(p->next->next != nullptr){
                    ListNode *r = p->next->next;// 用于依次后移和p比较
                    while(r != nullptr){
                        // cout << "test282";
                        int n = (r->val) - 1;
                        if(arc[m][n] != INT_MAX){
                            tempNode->val = n + 1;
                            loop_des = r;
                        }
                        r = r->next;
                    }
                }
                q->next = tempNode;
                q = tempNode;
                dist_d_f[i].value += arc[(p->val) - 1][(tempNode->val) - 1];
                if(loop_des != nullptr){
                    p = loop_des;
                }else{
                    p = p->next;
                }
            }
        }
    }
}

void Graph_DG::fix_stsr(Dist *dist_d, Dist *dist_s){
    for(int i = 0; i < this->vexnum; i++){// i表示第i个卫星节点
        if((dist_s[i].value == INT_MAX) && (dist_d[i].value != INT_MAX)){
        // if(dist_d[i].value != INT_MAX){
            // 对到i的卫星路线进行修正,从dist_d到dist_s的部分copy
            ListNode *p = dist_d[i].head;
            ListNode *q = dist_s[i].head;
            dist_s[i].value = 0;
            while(p->next != nullptr){
                if(i == 1)cout << p->val<<endl;
                int m = (p->val) - 1;
                ListNode *tempNode = new ListNode(p->next->val);// 新节点，用于加在q后面
                // 处理有可能成环的情况
                ListNode *loop_des = nullptr;
                if(p->next->next != nullptr){
                    ListNode *r = p->next->next;// 用于依次后移和p比较
                    while(r != nullptr){
                        int n = (r->val) - 1;
                        if(arc[m][n] != INT_MAX){
                            tempNode->val = n + 1;
                            loop_des = r;
                        }
                        r = r->next;
                    }
                }
                q->next = tempNode;
                q = tempNode;
                dist_s[i].value += arc[(p->val) - 1][(tempNode->val) - 1];
                if(loop_des != nullptr){
                    p = loop_des;
                }else{
                    p = p->next;
                }
            }
        }
    }
}



void Graph_DG::print_path(int begin, Dist* dist) {
    string str;
    str = "v" + to_string(begin);
    cout << "以"<<str<<"为起点的图的最短路径为:" << endl;
    for (int i = 0; i != this->vexnum; i++) {
        if(dist[i].value!=INT_MAX){
            // for (int j = 0; dist[i].path[j] != 0;j++)
            // {
            //     cout << "v" << dist[i].path[j] << "->";
            // }
            ListNode *p = dist[i].head;
            while(p != nullptr){
                cout << "v" << p->val << "->";
                p = p->next;
            }

            cout<< "=" << dist[i].value << endl;
        }
        // cout << dist[i].path << "=" << dist[i].value << endl;
        else {
            // cout << dist[i].path << "是无最短路径的" << endl;
            cout << "v" << begin <<"->v" << i+1 << "是无最短路径的" << endl;
        }
    }
}