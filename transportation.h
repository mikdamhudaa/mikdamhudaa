#ifndef TRANSPORTATION_H_INCLUDED
#define TRANSPORTATION_H_INCLUDED

#include <iostream>
using namespace std;

#define firstVertex(G) G.firstVertex
#define firstEdge(v) v->firstEdge
#define nextVertex(v) v->nextVertex
#define nextEdge(e) e->nextEdge
#define weight(e) e->weight
#define idVertex(v) v->idVertex
#define destVertexID(e) e->destVertexID
#define nil NULL

typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;

struct vertex {
    string idVertex;         // Representasi nama transit
    adrVertex nextVertex;    // Node berikutnya
    adrEdge firstEdge;       // Pointer ke edge pertama
};

struct edge {
    string destVertexID;     // Transit tujuan
    int weight;              // Waktu atau biaya perjalanan
    adrEdge nextEdge;        // Edge berikutnya
};

struct graph {
    adrVertex firstVertex;   // Pointer ke vertex pertama
};

// Fungsi dasar
void initGraph(graph &G);
void addVertex(graph &G, string newVertexID);
void addEdge(graph &G, string IDsimpulAsal, string IDsimpulTujuan, int bobot);
adrVertex searchVertex(graph G, string IDsimpul);
void printGraph(graph G);

// Fungsi tambahan
int calculateShortestPath(graph G, string start, string end);
void findAlternativeRoutes(graph &G, string closedVertex);
                           // Fungsi untuk menemukan alur tersibuk (vertex dengan jumlah koneksi terbanyak)
string findBusiestPath(graph G);

// Fungsi untuk menemukan alur termurah
int findCheapestPath(graph G, string start, string end);

#endif // TRANSPORTATION_H_INCLUDED
