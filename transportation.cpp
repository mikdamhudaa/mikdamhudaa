#include "transportation.h"
#include <queue>
#include <unordered_map>
#include <climits>

// Inisialisasi graf
void initGraph(graph &G) {
    firstVertex(G) = nil;
}

// Menambahkan vertex baru
void addVertex(graph &G, string newVertexID) {
    adrVertex newVertex = new vertex;
    idVertex(newVertex) = newVertexID;
    firstEdge(newVertex) = nil;
    nextVertex(newVertex) = firstVertex(G);
    firstVertex(G) = newVertex;
}

// Mencari vertex berdasarkan ID
adrVertex searchVertex(graph G, string IDsimpul) {
    adrVertex v = firstVertex(G);
    while (v != nil && idVertex(v) != IDsimpul) {
        v = nextVertex(v);
    }
    return v;
}

// Menambahkan edge antar vertex
void addEdge(graph &G, string IDsimpulAsal, string IDsimpulTujuan, int bobot) {
    adrVertex src = searchVertex(G, IDsimpulAsal);
    adrVertex dest = searchVertex(G, IDsimpulTujuan);

    if (src != nil && dest != nil) {
        adrEdge newEdge = new edge;
        destVertexID(newEdge) = IDsimpulTujuan;
        weight(newEdge) = bobot;
        nextEdge(newEdge) = firstEdge(src);
        firstEdge(src) = newEdge;
    }
}

// Mencetak graf
void printGraph(graph G) {
    adrVertex v = firstVertex(G);
    while (v != nil) {
        cout << "Transit " << idVertex(v) << ": ";
        adrEdge e = firstEdge(v);
        while (e != nil) {
            cout << " -> (" << destVertexID(e) << ", " << weight(e) << ")";
            e = nextEdge(e);
        }
        cout << endl;
        v = nextVertex(v);
    }
}

// Menghitung jalur terpendek (Dijkstra)
int calculateShortestPath(graph G, string start, string end) {
    unordered_map<string, int> distances;
    unordered_map<string, bool> visited;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    // Inisialisasi
    adrVertex v = firstVertex(G);
    while (v != nil) {
        distances[idVertex(v)] = INT_MAX;
        visited[idVertex(v)] = false;
        v = nextVertex(v);
    }

    distances[start] = 0;
    pq.push({0, start});

    // Proses Dijkstra
    while (!pq.empty()) {
        auto [currDist, currNode] = pq.top();
        pq.pop();

        if (visited[currNode]) continue;
        visited[currNode] = true;

        adrVertex currVertex = searchVertex(G, currNode);
        adrEdge e = firstEdge(currVertex);

        while (e != nil) {
            string neighbor = destVertexID(e);
            int weight = weight(e);
            if (!visited[neighbor] && distances[currNode] + weight < distances[neighbor]) {
                distances[neighbor] = distances[currNode] + weight;
                pq.push({distances[neighbor], neighbor});
            }
            e = nextEdge(e);
        }
    }

    return distances[end] == INT_MAX ? -1 : distances[end];
}

// Mencari jalur alternatif
void findAlternativeRoutes(graph &G, string closedVertex) {
    cout << "Transit " << closedVertex << " ditutup. Jalur alternatif:" << endl;

    adrVertex v = firstVertex(G);
    while (v != nil) {
        if (idVertex(v) != closedVertex) {
            adrEdge e = firstEdge(v);
            while (e != nil) {
                if (destVertexID(e) != closedVertex) {
                    cout << idVertex(v) << " -> " << destVertexID(e) << endl;
                }
                e = nextEdge(e);
            }
        }
        v = nextVertex(v);
    }
}

// Fungsi untuk menemukan titik transit tersibuk (yang memiliki banyak koneksi)
string findBusiestPath(graph G) {
    adrVertex v = firstVertex(G);
    string busiestPath = "";
    int maxConnections = -1;

    while (v != nil) {
        int connections = 0;
        adrEdge e = firstEdge(v);

        // Menghitung jumlah koneksi (edge keluar)
        while (e != nil) {
            connections++;
            e = nextEdge(e);
        }

        // Memperbarui titik transit tersibuk
        if (connections > maxConnections) {
            maxConnections = connections;
            busiestPath = idVertex(v);
        }

        v = nextVertex(v);
    }

    return busiestPath;
}

// Fungsi untuk menemukan alur termurah (biaya terkecil)
int findCheapestPath(graph G, string start, string end) {
    unordered_map<string, int> distances;
    unordered_map<string, bool> visited;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    // Inisialisasi jarak dan status kunjungan
    adrVertex v = firstVertex(G);
    while (v != nil) {
        distances[idVertex(v)] = INT_MAX;
        visited[idVertex(v)] = false;
        v = nextVertex(v);
    }

    distances[start] = 0;
    pq.push({0, start});

    // Proses Dijkstra
    while (!pq.empty()) {
        auto [currDist, currNode] = pq.top();
        pq.pop();

        if (visited[currNode]) continue;
        visited[currNode] = true;

        adrVertex currVertex = searchVertex(G, currNode);
        adrEdge e = firstEdge(currVertex);

        // Menelusuri semua edge keluar dari simpul
        while (e != nil) {
            string neighbor = destVertexID(e);
            int weight = weight(e);
            if (!visited[neighbor] && distances[currNode] + weight < distances[neighbor]) {
                distances[neighbor] = distances[currNode] + weight;
                pq.push({distances[neighbor], neighbor});
            }
            e = nextEdge(e);
        }
    }

    return distances[end] == INT_MAX ? -1 : distances[end];
}

