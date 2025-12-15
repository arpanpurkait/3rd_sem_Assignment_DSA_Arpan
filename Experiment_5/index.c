#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_V 20
#define MAX_E 50

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

void solvePrim(int V, int graph[MAX_V][MAX_V], const char *outputFile);
void solveKruskal(int V, int E, Edge edges[], const char *outputFile);
int minKey(int key[], int mstSet[], int V);
int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);
int compareEdges(const void *a, const void *b);

int main() {
    int V, E;
    Edge edges[MAX_E];
    int adjMatrix[MAX_V][MAX_V];

    FILE *fp = fopen("input_graph.txt", "r");
    if (!fp) {
        printf("Error opening input file.\n");
        return 1;
    }
    
    fscanf(fp, "%d %d", &V, &E);

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adjMatrix[i][j] = 0;

    for (int i = 0; i < E; i++) {
        fscanf(fp, "%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        adjMatrix[edges[i].src][edges[i].dest] = edges[i].weight;
        adjMatrix[edges[i].dest][edges[i].src] = edges[i].weight;
    }
    fclose(fp);

    printf("Graph read successfully. V=%d, E=%d\n", V, E);

    solvePrim(V, adjMatrix, "output_prim.txt");
    printf("Prim's Algorithm trace saved to 'output_prim.txt'\n");

    solveKruskal(V, E, edges, "output_kruskal.txt");
    printf("Kruskal's Algorithm trace saved to 'output_kruskal.txt'\n");

    return 0;
}

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void solvePrim(int V, int graph[MAX_V][MAX_V], const char *outputFile) {
    int parent[MAX_V];
    int key[MAX_V];
    int mstSet[MAX_V];
    int totalWeight = 0;
    FILE *fout = fopen(outputFile, "w");

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    fprintf(fout, "--- Trace: Prim's Algorithm ---\n");
    fprintf(fout, "[Init] Started at Vertex 0. Keys initialized to Infinity.\n");

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;
        
        fprintf(fout, "\n[Step %d] Selected Vertex %d (Min Key: %d)\n", count + 1, u, key[u]);

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
                fprintf(fout, "  -> [Update] Neighbor %d key updated to %d (via edge %d-%d)\n", v, key[v], u, v);
            }
        }
    }

    fprintf(fout, "\n--- Final MST Structure ---\n");
    fprintf(fout, "Edge\tWeight\n");
    for (int i = 1; i < V; i++) {
        fprintf(fout, "%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    fprintf(fout, "Total MST Weight: %d\n", totalWeight);
    fclose(fout);
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void *a, const void *b) {
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight - b1->weight;
}

void solveKruskal(int V, int E, Edge edges[], const char *outputFile) {
    Subset *subsets = (Subset *)malloc(V * sizeof(Subset));
    Edge result[MAX_V];
    int e = 0;
    int i = 0;
    int totalWeight = 0;
    FILE *fout = fopen(outputFile, "w");

    fprintf(fout, "--- Trace: Kruskal's Algorithm ---\n");

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    qsort(edges, E, sizeof(edges[0]), compareEdges);
    fprintf(fout, "[Init] Edges sorted by weight.\n");

    while (e < V - 1 && i < E) {
        Edge next_edge = edges[i++];
        fprintf(fout, "\n[Check] Checking Edge %d-%d (Weight: %d)\n", next_edge.src, next_edge.dest, next_edge.weight);

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
            fprintf(fout, "  -> [Action] No cycle detected. Edge added to MST.\n");
            totalWeight += next_edge.weight;
        } else {
            fprintf(fout, "  -> [Discard] Cycle detected (Roots %d and %d are same). Edge discarded.\n", x, y);
        }
    }

    fprintf(fout, "\n--- Final MST Structure ---\n");
    fprintf(fout, "Edge\tWeight\n");
    for (i = 0; i < e; ++i)
        fprintf(fout, "%d - %d\t%d\n", result[i].src, result[i].dest, result[i].weight);
    
    fprintf(fout, "Total MST Weight: %d\n", totalWeight);
    fclose(fout);
    free(subsets);
}