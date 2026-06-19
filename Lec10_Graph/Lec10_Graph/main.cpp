#include <stdio.h>
#include "AdjMatGraph.h"

int main()
{
    // =========================
    // 1. 기존 인접 행렬 그래프 + DFS 실습
    // =========================
    SrchAMGraph g;

    for (int i = 0; i < 4; i++)
        g.insertVertex('A' + i);

    g.insertEdge(0, 1);
    g.insertEdge(0, 3);
    g.insertEdge(1, 2);
    g.insertEdge(1, 3);
    g.insertEdge(2, 3);

    printf("인접 행렬로 표현한 그래프\n");
    g.display();

    // 파일 출력
    FILE* fp = NULL;
    fopen_s(&fp, "../text_out.txt", "w");
    if (fp != NULL) {
        g.display(fp);
        fclose(fp);
    }

    // DFS 탐색
    printf("DFS ==> ");
    g.resetVisited();
    g.DFS(0);
    printf("\n\n");


    // =========================
    // 2. 가중치 그래프 테스트 + Kruskal
    // =========================
    printf("weighted Graph 테스트\n");

    WGraphMST kg;
    kg.load("../graph.txt");
    kg.display();

    printf("\nMST By Kruskal's Algorithm\n");
    kg.Kruskal();
    printf("\n");


    // =========================
    // 3. Prim MST
    // =========================
    WGraphPrim pg;
    pg.load("../graph.txt");

    printf("Prim MST 실행 결과\n");
    pg.Prim(0);

    printf("\nShortest Path By Dijkstra Algorithm\n");

    WGraphDijkstra dg;
    dg.load("../graph.txt");
    dg.ShortestPath(0);

    return 0;
}
