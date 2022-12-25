using namespace std;
const double infinity = 1.7E+308;
#include <vector>
#include "graph.h"
#include "paintwidget.h"

vector<int> build_path(map<int, int> Parent, int start_vertex, int end_vertex) {
    if (Parent[end_vertex] == -1) return {};
    vector<int> result = { end_vertex };
    for (int i = end_vertex; Parent[i] != start_vertex; ) {
        result.insert(result.begin(), Parent[i]);
        i = Parent[i];
    }
    result.insert(result.begin(), start_vertex);
    return result;
}

auto shortest_path(const Graph &graph,int start_vertex, int vision_distance, const vector<QPoint> &vp, const QPoint& p) -> vector<int> {
    // кратчайший путь до окружности радиуса vision_distance, с центром в точке р
    vector<int> shortest{};
    vector<int> Q = graph.get_vertices();
    if (Q.size() == 0) return shortest;
    map<int, double> Distance;
    map<int, int> Parent;
    vector<pair<int, double>> adjacent_edges;
    int act_vert;
    double min_dist;
    for (int i = 0; i < Q.size(); i++) {
        Distance[Q[i]] = infinity;
        Parent[Q[i]] = -1;
    }
    Distance[start_vertex] = 0;
    while (Q.size() != 0) {
        min_dist = Distance[Q[0]];
        act_vert = 0;
        for (int i = 1; i < Q.size(); i++) {
            if (min_dist > Distance[Q[i]]) {
                min_dist = Distance[Q[i]];
                act_vert = i;
            }
        }
        if (Q[0] > 2147483646) return vector<int>();
        if (lineLen(p, vp[Q[act_vert]]) < vision_distance) {
            return build_path(Parent, start_vertex, Q[act_vert]);
        }
        else {
            adjacent_edges = graph.get_adjacent_edges(Q[act_vert]);
            for (int i = 0; i < adjacent_edges.size(); i++) {
                if (Distance[adjacent_edges[i].first] > min_dist + adjacent_edges[i].second) {
                    Distance[adjacent_edges[i].first] = min_dist + adjacent_edges[i].second;
                    Parent[adjacent_edges[i].first] = Q[act_vert];
                }
            }
        }
        Q.erase(next(Q.begin(), act_vert));
    }
    return vector<int>();
}



vector<int> shortest_path(const Graph &graph, int start_vertex, int end_vertex) {
    // обычная дейкстра для промежуточных вершин
    vector<int> shortest{};
    vector<int> Q = graph.get_vertices();
    if (Q.size() == 0) return shortest;
    map<int, double> Distance;
    map<int, int> Parent;
    vector<pair<int, double>> adjacent_edges;
    int act_vert;
    double min_dist;
    for (int i = 0; i < Q.size(); i++) {
        Distance[Q[i]] = infinity;
        Parent[Q[i]] = -1;
    }
    Distance[start_vertex] = 0;
    while (Q.size() != 0) {
        min_dist = Distance[Q[0]];
        act_vert = 0;
        for (int i = 1; i < Q.size(); i++) {
            if (min_dist > Distance[Q[i]]) {
                min_dist = Distance[Q[i]];
                act_vert = i;
            }
        }
        if (Q[act_vert] == end_vertex) {
            return build_path(Parent, start_vertex, end_vertex);
        }
        else {
            adjacent_edges = graph.get_adjacent_edges(Q[act_vert]);
            for (int i = 0; i < adjacent_edges.size(); i++) {
                if (Distance[adjacent_edges[i].first] > min_dist + adjacent_edges[i].second) {
                    Distance[adjacent_edges[i].first] = min_dist + adjacent_edges[i].second;
                    Parent[adjacent_edges[i].first] = Q[act_vert];
                }
            }
        }
        Q.erase(next(Q.begin(), act_vert));
    }
    return shortest;
}
