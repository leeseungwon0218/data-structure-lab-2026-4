#pragma once

#ifndef MAX_VTXS
#define MAX_VTXS 100
#endif

class VertexSets {
    int parent[MAX_VTXS];   // 부모 정점의 id
    int nSets;              // 집합의 개수

public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < nSets; i++)
            parent[i] = -1; // 모든 정점이 고유의 집합에 속함
    }

  
        bool isRoot(int i) {
        return parent[i] < 0;
    }

    int findSet(int v) {
        while (!isRoot(v))
            v = parent[v];
        return v;
    }

    void unionSets(int s1, int s2) {
        parent[s1] = s2;
        nSets--;
    }
  

};
