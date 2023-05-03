#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct Data{
    int v;
    int num;
    Data(int _v, int _num){v = _v; num = _num;}
};

vector<vector<Data>> graph;
bool isVisited[100000];
int order[100000];
int n, m;
int mustBeDestroyed[100000];

void bfs(int start){
    queue<int> q;
    int index = 0;
    q.push(start);
    isVisited[start] = true;
    order[start] = ++index;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for (Data i : graph[v]){
            if (!isVisited[i.v]){
                isVisited[i.v] = true;
                order[i.v] = ++index;
                q.push(i.v);
            }
        }
    }
}

void remove(int temp){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            if (graph[i][j].num == temp) {
                graph[i].erase(graph[i].begin() + j);
                break;
            }
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int q;
    fin >> n >> m >> q;
    graph.resize(n);
    memset(isVisited, false, sizeof(isVisited));
    memset(order, 0, sizeof(order));
    memset(mustBeDestroyed, 0, sizeof(mustBeDestroyed));
    for (int i = 0; i < m; i++){
        int x, y;
        fin >> x >> y;
        graph[x - 1].push_back(Data(y - 1, i + 1));
        graph[y - 1].push_back(Data(x - 1, i + 1));
    }
    for (int i = 0; i < q; i++){
        fin >> mustBeDestroyed[i];
    }
    bool comp = true;
    for (int l = 0; l < q; l++){
        int temp = mustBeDestroyed[l];
        if (comp){
            remove(temp);
            memset(isVisited, false, sizeof(isVisited));
            bfs(0);
            for (int i = 0; i < n; i++){
                if (!isVisited[i]){
                    comp = false;
                    break;
                }
            }
            if (comp)
                fout << 1;
            else fout << 0;
        }
        else
            fout << 0;
    }
    fout.flush();
    return 0;
}