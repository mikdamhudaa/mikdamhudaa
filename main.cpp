
#include "transportation.h" // Header file sesuai dengan struktur graf yang Anda gunakan


int main() {
    graph G;

    // Inisialisasi graf
    initGraph(G);

    // Menambahkan simpul (stasiun MRT Jakarta) dengan nama stasiun
    addVertex(G, "Lebak Bulus");   // Stasiun Lebak Bulus
    addVertex(G, "Fatmawati");     // Stasiun Fatmawati
    addVertex(G, "Cipete Raya");   // Stasiun Cipete Raya
    addVertex(G, "Blok M");        // Stasiun Blok M
    addVertex(G, "Dukuh Atas");    // Stasiun Dukuh Atas

    // Menambahkan edge (jalur dengan biaya dalam ribu rupiah)
    addEdge(G, "Lebak Bulus", "Fatmawati", 5); // Lebak Bulus -> Fatmawati (5k)
    addEdge(G, "Fatmawati", "Cipete Raya", 4); // Fatmawati -> Cipete Raya (4k)
    addEdge(G, "Cipete Raya", "Blok M", 6);   // Cipete Raya -> Blok M (6k)
    addEdge(G, "Blok M", "Dukuh Atas", 7);    // Blok M -> Dukuh Atas (7k)

    // Menampilkan graf dalam bentuk tabel
    cout << "Graf Jaringan MRT Jakarta (Tabel Adjacency):" << endl;
    printGraph(G);
    cout << endl;
    // Menemukan jalur terpendek menggunakan algoritma Dijkstra
    string source = "Lebak Bulus", destination = "Dukuh Atas";
    int shortestPathCost = calculateShortestPath(G, source, destination);
    if (shortestPathCost != -1) {
        cout << "Jalur terpendek dari " << source << " ke " << destination
             << " memiliki biaya " << shortestPathCost << "k" << endl;
    } else {
        cout << "Tidak ada jalur dari " << source << " ke " << destination << endl;
    }
    cout << endl;

    // Menentukan titik transit tersibuk
    string busiestPath = findBusiestPath(G);
    cout << "Alur tersibuk adalah: " << busiestPath << endl;
    cout << endl;

    // Menemukan jalur termurah
    int cheapestPathCost = findCheapestPath(G, "Lebak Bulus", "Dukuh Atas");
    if (cheapestPathCost != -1) {
        cout << "Alur termurah dari Lebak Bulus ke Dukuh Atas adalah "
             << cheapestPathCost << "k" << endl;
    } else {
        cout << "Tidak ada jalur termurah dari Lebak Bulus ke Dukuh Atas" << endl;
    }

    return 0;
}
