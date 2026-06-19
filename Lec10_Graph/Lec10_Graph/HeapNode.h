#pragma once


class HeapNode {
	int key; // Key 값: 간선의 가중치
	int v1; // 정점 1
	int v2; // 정점 2
public:
	HeapNode() : key(0), v1(0), v2(0) {}
	HeapNode(int k, int u, int v) : key(k), v1(u), v2(v) {}
	void setKey(int k, int u, int v) {
		key = k;
		v1 = u;
		v2 = v;
	}
	int getKey() { return key; }
	int getV1() { return v1; }
	int getV2() { return v2; }
};
