#include <iostream>
#include <vector>
#include <queue>
#include "graph.hpp"

#define INF 0x3f3f3f3f

using namespace std;

int dijkstra(Graph& grafo, int origem, int destino) 
{
    int n = grafo.getNumVertices();

    // dist[i][j] representa a distância mínima da origem a i com estado j
    // Inicializamos com INF, que significa que não há caminho entre os vértices
    vector<vector<int>> dist(n, vector<int>(2, INF));

    // Usamos uma fila de prioridade para o algoritmo de Dijkstra, que prioriza as menores distâncias
    priority_queue<pair<int, pair<int, int>>> pq;

    // Inicializamos a distância da origem para ela mesma como zero
    dist[origem][0] = 0;

    // Adicionamos a origem na fila de prioridade
    pq.push({0, {origem, 0}});

    while (!pq.empty()) 
    {
        // Removemos o vértice com menor distância da fila de prioridade
        int u = pq.top().second.first;
        int state = pq.top().second.second;
        int d = -pq.top().first; // O valor na fila de prioridade é negativo, então usamos o sinal para reverter
        pq.pop();

        // Se a distância já processada for maior que a distância mínima encontrada, pulamos para o próximo vértice
        if (d > dist[u][state]) 
        {
            continue;
        }

        // Explora cada vizinho de u
        for (auto& v : grafo.getAdjList(u)) 
        {
            int weight = v.second;

            // Verifica se o estado muda
            int new_state = state ^ 1;

            // Se a distância da origem até o vizinho for menor pela aresta atual, atualizamos a distância mínima
            if (dist[u][state] + weight < dist[v.first][new_state]) 
            {
                dist[v.first][new_state] = dist[u][state] + weight;

                // Adicionamos o vizinho na fila de prioridade com a distância mínima atualizada
                pq.push({-dist[v.first][new_state], {v.first, new_state}});
            }
        }
    }

    // Verificamos se a origem e o destino estão conectados por uma única aresta, ou seja, é número ímpar de estradas
    if (grafo.getAdjList(origem).size() == 1 && grafo.getAdjList(origem)[0].first == destino) 
    {
        return -1;
    }

    // Verificamos se o destino é alcançável a partir da origem
    if (dist[destino][0] % 2 == 0) 
    {
        // Se a distância mínima até o destino com estado 0 for par, significa que não há ciclo de tamanho ímpar
        // Retorna a distância mínima
        return dist[destino][0];
    } 
    else if (dist[destino][1] % 2 == 0) 
    {
        // Se a distância mínima até o destino com estado 1 for par, significa que há um ciclo de tamanho ímpar
        // Retorna a distância mínima com estado 1
        return dist[destino][1];
    } 
    else 
    {
        // Não há caminho válido entre a origem e o destino
        return -1;
    }
}


int main(int argc, char const *argv[]) 
{
    int N;   // número de cidades (2 ≤ N ≤ 10000)
    int A;   // número de estradas conectando pares de cidades (1 ≤ A ≤ 100000)

    cin >> N >> A;

    // inicializa o grafo com N vértices
    Graph grafo(N);

    for(int i = 0; i < A; i++) 
    {
        int X1;   // identificador de uma cidade de origem    (1 ≤ X1)
        int X2;   // identificador de uma cidade de destino   (X2 ≤ N, X1 != X2)
        int D;   // comprimento da estrada que liga diretamente as respectivas cidades   (0 < D ≤ 10000)

        cin >> X1 >> X2 >> D;

        if((D % 2) == 0) // estrada de comprimento par
        {
            grafo.add_aresta(X1 - 1, X2 - 1, D); // adiciona aresta no grafo
        }

    }

    // calcula o caminho mínimo com número par de arestas entre o vértice 1 e o vértice N
    int resultado = dijkstra(grafo, 0, N - 1);

    cout << resultado << endl;

    return 0;
}