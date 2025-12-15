#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_V 20
#define INF INT_MAX

void solveDijkstra(int V, int startNode, int graph[MAX_V][MAX_V], const char *outputFile);
int minDistance(int dist[], bool sptSet[], int V);
void printSolution(int dist[], int V, FILE *fout);

int main() {
    int V, E, startNode;
    int graph[MAX_V][MAX_V];
    int u, v, w;

    FILE *fp = fopen("input_dijkstra.txt", "r");
    if (!fp) {
        printf("Error opening input file.\n");
        return 1;
    }

    fscanf(fp, "%d %d %d", &V, &E, &startNode);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }

    for (int i = 0; i < E; i++) {
        fscanf(fp, "%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; 
    }
    fclose(fp);

    printf("Graph read successfully. Calculating paths from Node %d...\n", startNode);

    solveDijkstra(V, startNode, graph, "output_dijkstra.txt");
    printf("Dijkstra's Algorithm trace saved to 'output_dijkstra.txt'\n");

    return 0;
}

int minDistance(int dist[], bool sptSet[], int V) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void solveDijkstra(int V, int startNode, int graph[MAX_V][MAX_V], const char *outputFile) {
    int dist[MAX_V]; 
    bool sptSet[MAX_V]; 
    FILE *fout = fopen(outputFile, "w");

    if (!fout) {
        printf("Error creating output file.\n");
        exit(1);
    }

    for (int i = 0; i < V; i++)
        dist[i] = INF, sptSet[i] = false;

    dist[startNode] = 0;

    fprintf(fout, "--- Trace: Dijkstra's Algorithm ---\n");
    fprintf(fout, "Start Node: %d\n", startNode);
    fprintf(fout, "Initial Distances: [0: 0] [Others: INF]\n\n");

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        fprintf(fout, "[Step %d] Selected Node %d (Current Dist: %d)\n", count + 1, u, dist[u]);

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                fprintf(fout, "  -> Checking neighbor %d (Edge Weight: %d)\n", v, graph[u][v]);
                fprintf(fout, "  -> UPDATE: New distance for Node %d is %d (was %d)\n", v, dist[u] + graph[u][v], (dist[v] == INF ? -1 : dist[v]));
                dist[v] = dist[u] + graph[u][v];
            }
        }
        fprintf(fout, "\n");
    }

    printSolution(dist, V, fout);
    fclose(fout);
}

void printSolution(int dist[], int V, FILE *fout) {
    fprintf(fout, "--- Final Shortest Paths ---\n");
    fprintf(fout, "Node\tDistance from Source\n");
    fprintf(fout, "----\t--------------------\n");
    for (int i = 0; i < V; i++)
        fprintf(fout, "%d \t\t %d\n", i, dist[i]);
}