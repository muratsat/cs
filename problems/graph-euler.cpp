#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum color{
    WHITE, GREY, BLACK
};

struct graph{
    vector<vector<int>> e;
    vector<int> degree;

    graph(int n){
        e.resize(n);
        degree.resize(n);
        for(int i = 0; i < n; i++)
            degree[i] = 0;
    }

    int size(){
        return e.size();
    }

    void add(int a, int b){
        e[a-1].push_back(b-1);
        e[b-1].push_back(a-1);
        degree[a-1]++;
        degree[b-1]++;
    }

    void bfs(vector<color> &c);

    int check();
};


void graph::bfs(vector<color> &c){
    queue<int> q;

    for(int i = 0; i < size(); i++){
        if(degree[i] != 0){
            q.push(i);
            c[i] = GREY;
            break;
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();
        c[u] = BLACK;
        for(int v : e[u]){
            if(c[v] == WHITE){
                q.push(v);
                c[v] = GREY;
            }
        }
    }
}

int graph::check(){
    int components = 0;
    int n = size();
    int odd = 0;

    vector<color> c(n, WHITE);
    for(int i = 0; i < n; i++){
        if(degree[i] == 0)
            return 0;
        if(degree[i]%2 == 1)
            odd++;

        if(degree[i] > 0 && c[i] == WHITE){
            bfs(c);
            components++;
        }
    }

    if(components > 1)
        return 0;
    
    if(odd != 2 && odd != 0)
        return 0;
    
    return 1;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    graph g(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g.add(a, b);
    }

    if(g.check())
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}