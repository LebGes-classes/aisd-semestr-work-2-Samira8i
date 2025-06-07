#include <iostream>
#include <vector>
#include <queue>
#include <climits> //нужен, чтобы использовать константы, связанные с пределами типов, в моем случае INT_MAX 
using namespace std;

// Функция для вывода минимального остова
//для себя: vector аналог ArrayList
void printOstov(const vector<int>& parent, const vector<vector<pair<int, int>>>& graph) {
    cout << "Ребро \tВес\n";
    for (int i = 1; i < parent.size(); ++i) {
        int weight = 0;
        // Находим вес ребра между parent[i] и i
        for (const auto& edge : graph[parent[i]]) {
            if (edge.first == i) {
                weight = edge.second;
                break;
            }
        }
        cout << parent[i] << " - " << i << "\t" << weight << "\n";
    }
}
//vector<vector<pair<int, int>>>& graph описывает ссылку на список смежности (то есть список списков [номер соседней вершины, вес до нее])
//некоторые моменты в с++ не особо знаю, поэтому будут такие вставки(для себя): greater<pair<int,int>> — это функция сравнения, которая заставляет очередь отдавать минимальный элемент.

// сам Алгоритм Прима
void primOstov(const vector<vector<pair<int, int>>>& graph) {
    int V = graph.size(); // Количество вершин
    vector<int> key(V, INT_MAX); // Минимальные веса рёбер для каждой вершины, но сначала там типо супер большой вес 
    vector<bool> inOstov(V, false); // true-вершина уже в остове
    vector<int> parent(V, -1); // Родитель каждой вершины в MST

    // использую очередь с приоритетом для выбора ребра с минимальным весом, потому что с ней удобнее и быстрее 
    // Хранит пары (минимальный вес ребра, чтобы попасть к вершине, вершина)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Начинаем с вершины 0 — ставим вес 0, чтобы она первая попала в MST
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second; // Берём вершину с минимальным ключом
        pq.pop();

        inOstov[u] = true; // Добавляем её в остов

        // Рассматриваем всех соседей u
        //edge — это текущий элемент из списка рёбер вершины u.
        for (const auto& edge : graph[u]) {
            int v = edge.first; // соседняя вершина
            int weight = edge.second; // вес ребра u-v

            // Если сосед v ещё не в остове и вес ребра меньше текущего ключа
            if (!inOstov[v] && weight < key[v]) {
                key[v] = weight; // Обновляем ключ
                parent[v] = u;   // Запоминаем, что в остов v вошла через u
                pq.push({key[v], v}); // Добавляем обновлённый ключ в очередь
            }
        }
    }

    printOstov(parent, graph); // Выводим результат остова
}

int main() {
    int V = 5;
    vector<vector<pair<int, int>>> graph(V);

    // Добавляем рёбра — неориентированный граф, поэтому с двух сторон
    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});
    graph[3].push_back({4, 9});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});
    graph[4].push_back({3, 9});

    primOstov(graph);

    return 0;
}
