#pragma once
#include <stdio.h>
#include "HeapNode.h"
#include "VertexSets.h"
#include "MinHeap.h"

#ifndef MAX_VTXS
#define MAX_VTXS 100
#endif
#define INF 9999

class AdjMatGraph {
protected:
    int    size = 0;
    char   vertices[MAX_VTXS] = { 0 };
    int    adj[MAX_VTXS][MAX_VTXS] = { 0 };
public:
    AdjMatGraph() { reset(); }
    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS; }

    // 그래프 초기화 -> 공백 상태의 그래프
    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 0);
    }
    // 정점 삽입
    void insertVertex(char name) {
        if (!isFull()) vertices[size++] = name;
        else printf("Error: 그래프 정점 개수 초과\n");
    }
    // 간선 삽입: 무방향 그래프의 경우임. (방향, 가중치 그래프에서는 수정)
    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1); // 방향 그래프에서는 삭제됨(<u,v>만 존재)
    }
    // 그래프 정보 출력 (화면이나 파일에 출력)
    void display(FILE* fp = stdout) {
        fprintf(fp, "%d\n", size);		// 정점의 개수 출력
        for (int i = 0; i < size; i++) {		// 각 행의 정보 출력
            fprintf(fp, "%c", getVertex(i));	// 정점의 이름 출력
            for (int j = 0; j < size; j++)	    // 간선 정보 출력
                fprintf(fp, "%5d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};

// 탐색 기능이 추가된 인접 행렬 기반 그래프 클래스
class SrchAMGraph : public AdjMatGraph //Ad~ : 부모 클래스, Sr~: 자식 클래스
{
    bool visited[MAX_VTXS] = { false };	 // 정점의 방문 정보
public:
    void resetVisited() {	// 모든 정점을 방문하지 않았다고 설정
        for (int i = 0; i < size; i++)
            visited[i] = false;
    }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; } //연결=true

    // 깊이 우선 탐색 함수
    void DFS(int v) {
        if (v < 0 || v >= MAX_VTXS) return;

        visited[v] = true;	 // 현재 정점을 방문함
        printf("%c ", getVertex(v)); // 정점의 이름 출력

        for (int w = 0; w < size; w++) {
            if (w >= 0 && w < MAX_VTXS) {
                if (isLinked(v, w) && visited[w] == false)
                    DFS(w);	 // 연결 + 방문X => 순환호출로 방문
            }
        }
    }
};

class WGraph : public AdjMatGraph {
public:
    WGraph() { reset(); }

    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, INF);
    }

    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
        setEdge(v, u, weight);
    }
    bool hasEdge(int i, int j) {
        return (getEdge(i, j) != 0 && getEdge(i, j) < INF);
    }
    void load(const char* filename) {
        FILE* fp = NULL;
        fopen_s(&fp, filename, "r");
        if (fp != NULL) {
            int n = 0, val = 0;
            fscanf_s(fp, "%d", &n); // 정점의 전체 개수
            for (int i = 0; i < n; i++) {
                char str[80];
                fscanf_s(fp, "%s", str, unsigned(sizeof(str))); // 정점의 이름
                insertVertex(str[0]); // 정점 삽입
                for (int j = 0; j < n; j++) {
                    fscanf_s(fp, "%d", &val); // 간선 정보
                    insertEdge(i, j, val); // 간선 삽입
                }
            }
            fclose(fp);
        }
        else {
            printf("Error: 파일을 찾을 수 없습니다. 경로 확인 -> %s\n", filename);
        }
    }
};

class WGraphMST : public WGraph {
public:
    void Kruskal() { // kruskal의 최소 비용 신장 트리 프로그램
        MinHeap heap;
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (hasEdge(i, j))
                    heap.insert(getEdge(i, j), i, j); // 모든 간선 삽입
        VertexSets set(size); // size개의 집합을 만듦
        int edgeAccepted = 0; // 선택된 간선의 수
        while (edgeAccepted < size - 1) { // 간선의 수 < (size-1)
            if (heap.isEmpty()) break;

            HeapNode e = heap.remove();
            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());
            if (uset != vset) {
                printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());
                set.unionSets(uset, vset); // 두개의 집합을 합함.
                edgeAccepted++;
            }
        }
    }
};


class WGraphPrim : public WGraph {
public:
    void Prim(int start = 0) {
        bool selected[MAX_VTXS] = { false };
        int dist[MAX_VTXS];

        if (size == 0) {
            printf("Error: 그래프가 비어 있습니다.\n");
            return;
        }

        for (int i = 0; i < size; i++)
            dist[i] = INF;

        dist[start] = 0;

        printf("MST By Prin's Algorithm\n");

        for (int i = 0; i < size; i++) {
            int minDist = INF;
            int u = -1;

            for (int j = 0; j < size; j++) {
                if (!selected[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }

            if (u == -1) return;

            selected[u] = true;
            printf("%c ", getVertex(u));

            for (int v = 0; v < size; v++) {
                if (!selected[v] && hasEdge(u, v) && getEdge(u, v) < dist[v]) {
                    dist[v] = getEdge(u, v);
                }
            }
        }

        printf("\n\n");
    }
};

class WGraphDijkstra : public WGraph {
    int dist[MAX_VTXS];
    bool found[MAX_VTXS];

public:
    int chooseVertex() {
        int min = INF;
        int minpos = -1;

        for (int i = 0; i < size; i++) {
            if (dist[i] < min && !found[i]) {
                min = dist[i];
                minpos = i;
            }
        }

        return minpos;
    }

    void printDistance() {
        for (int i = 0; i < size; i++)
            printf("%5d", dist[i]);
        printf("\n");
    }

    void ShortestPath(int start) {
        for (int i = 0; i < size; i++) {
            dist[i] = getEdge(start, i);
            found[i] = false;
        }

        found[start] = true;
        dist[start] = 0;

        for (int i = 0; i < size; i++) {
            printf("Step %d:", i + 1);
            printDistance();

            int u = chooseVertex();

            if (u == -1)
                return;

            found[u] = true;

            for (int w = 0; w < size; w++) {
                if (!found[w]) {
                    if (dist[u] + getEdge(u, w) < dist[w])
                        dist[w] = dist[u] + getEdge(u, w);
                }
            }
        }
    }
};