struct Edge{
    int a, b, v;
    bool operator< (const Edge &W) const{
        return v < W.v;
    }
};

int find(int x, vector<int>&father){
    if (father[x] != x) father[x] = find(father[x], father);
    return father[x];
}

int Kruskal(int n, int m, vector<Edge>& edge){
    vector<int> father(n);
    int cnt = 0, res = 0;
    for (int i = 0; i < n; i++ ) father[i] = i;
    sort(edge.begin(), edge.end());
    for (int i = 0; i < m; i++ ){
        int a = edge[i].a, b = edge[i].b;
        if (find(a, father) != find(b, father)){
            res += edge[i].v;
            cnt++;
            father[find(a, father)] = find(b, father);
        }
    }
    if(cnt < n-1)return -1;
    return res;
}
