#pragma once


#include "HeapNode.h"

#define MAX_ELEMENT 200

class MinHeap {
    HeapNode node[MAX_ELEMENT]; // HeapNode 객체 배열
    int size;                   // 현재 힙에 들어있는 요소의 개수

public:
    MinHeap() : size(0) {}
    bool isEmpty() { return size == 0; }
    bool isFull() { return size == MAX_ELEMENT - 1; }

    // 부모 노드를 인덱스로 가져오는 보조 함수
    HeapNode getParent(int i) { return node[i / 2]; }

    // 자료 19페이지에 명시된 핵심 삽입 함수
    void insert(int key, int u, int v) {
        if (isFull()) return;
        int i = ++size;
        while (i != 1 && key < getParent(i).getKey()) {
            node[i] = getParent(i);
            i /= 2;
        }
        node[i].setKey(key, u, v);
    }

    // 최솟값(루트 노드)을 삭제하고 재정렬하여 반환하는 함수
    HeapNode remove() {
        if (isEmpty()) return HeapNode(0, 0, 0);

        HeapNode item = node[1];       // 루트 노드 백업
        HeapNode last = node[size--];  // 맨 마지막 노드
        int parent = 1;
        int child = 2;

        while (child <= size) {
            // 더 작은 자식 노드 선택
            if (child < size && node[child].getKey() > node[child + 1].getKey()) {
                child++;
            }
            // 마지막 노드가 자식 노드보다 작으면 자리 확정
            if (last.getKey() <= node[child].getKey()) {
                break;
            }

            node[parent] = node[child];
            parent = child;
            child *= 2;
        }
        node[parent] = last;
        return item;
    }
};