// 25.4 에디터 전쟁 문제를 해결하는 ack() 와 dis() 의 구현

#include <vector>
using namespace std;

struct BipartiteUnionFind {
    vector<int> parent, rank, enemy, size;
    BipartiteUnionFind(int n): parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
        for(int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int u) {
        if(parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    int merge(int u, int v) {
        if(u == -1 || v == -1) return max(u, v);
        u = find(u); v = find(v);
        if(u == v) return u;
        if(rank[u] > rank[v]) swap(u, v);
        if(rank[u] == rank[v]) rank[v]++;
        parent[u] = v;
        size[v] += size[u];
        return v;
    }

    bool dis(int u, int v) {
        u = find(u); v = find(v);
        if(u == v) return false;
        int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
        enemy[a] = b; enemy[b] = a;
        return true;
    }
    bool ack(int u, int v) {
        u = find(u), v = find(v);
        if(enemy[u] == v) return false;
        int a = merge(u, v), b = merge(enemy[u], enemy[v]);
        enemy[a] = b;
        if(b != -1) enemy[b] = a;
        return true;
    }
};