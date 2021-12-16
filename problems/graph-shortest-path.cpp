#include <iostream>
#include <vector>
using namespace std;

struct Edge{
    int from;
    int to;
    int weight;
    Edge(int f, int t, int w): from(f), to(t), weight(w){}
};

struct Graph{
    const int inf = 99999999;
    int n;
    vector<Edge> edges;
    Graph(int n): n(n){}

    void add(int from, int to, int weight){
        Edge e(from, to, weight);
        edges.push_back(e);
    }

    vector<int> ford_bellman(int s);
};

vector<int> Graph::ford_bellman(int s){
    vector<int> d(n, inf);
    d[s] = 0;

    for(int i = 0; i < n-1; i++){
        for(Edge e : edges){
            if(d[e.from] != inf && d[e.from] + e.weight < d[e.to]){
                d[e.to] = d[e.from] + e.weight;
            }
        }
    }
    
    for(Edge e : edges){
        if(d[e.from] != inf && d[e.from] + e.weight < d[e.to]){
            d.clear();
            break;
        }
    }

    return d;
}

int main(){
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    Graph g(n);

    for(int i = 0; i < m; i++){
        int from, to, weight;
        scanf("%d%d%d", &from, &to, &weight);
        g.add(from, to, weight);
    }

    vector<int> dist = g.ford_bellman(s);
    if(dist.size() == 0){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    for(int d : dist){
        if(d == g.inf) printf("UNREACHABLE ");
        else printf("%d ", d);
    }

    printf("\n");
    return 0;
}