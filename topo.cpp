#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include "topo.h"
using namespace std;

void create_topo(string filename, int vexnum, double ratio) {

    // 输出到txt
    ofstream topofile;
    // string filename = "mytopo.txt";
    // string filename;
    // cout << "请给拓扑文件命名" << endl;
    // cin >> filename;
    topofile.open(filename, ofstream::app);

    // 二项分布
    default_random_engine e;
    bernoulli_distribution u(ratio); // 0-1分布，生成1的概率为ratio
    e.seed(time(0));
 
    for (int i=0; i<vexnum; i++) {
        for (int j = 0; j < vexnum;j++ ){
            if(i==j){
                topofile << 0 << " ";
            }
            else{
                topofile << u(e) << " ";
            }
        }
        topofile << endl;
    }
}