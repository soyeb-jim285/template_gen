#include <bits/extc++.h>
using T = int;
const T kInf = numeric_limits<T>::max() / 4;
struct mcf_graph {
  struct Edge {
    int to, from, nxt;
    T flow, cap, cost;
  };
  vector<Edge> edges;

  int n;
  vector<T> dist, pi;
  vector<int> par, graph;

  mcf_graph(int _n) : n(_n), dist(n), pi(n, 0), par(n), graph(n, -1) {}
  void _addEdge(int from, int to, T cap, T cost) {
    edges.push_back(Edge{to, from, graph[from], 0, cap, cost});
    graph[from] = edges.size() - 1;
  }
  void add_edge(int from, int to, T cap, T cost) {
    _addEdge(from, to, cap, cost);
    _addEdge(to, from, 0, -cost);
  }
  bool dijkstra(int s, int t) {
    fill(dist.begin(), dist.end(), kInf);
    fill(par.begin(), par.end(), -1);

    __gnu_pbds::priority_queue<pair<T, int>> q;
    vector<decltype(q)::point_iterator> its(n);

    dist[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
      int node;
      T d;
      tie(d, node) = q.top();
      q.pop();
      if (dist[node] != -d)
        continue;
      for (int i = graph[node]; i >= 0;) {
        const auto &e = edges[i];
        T now = dist[node] + pi[node] - pi[e.to] + e.cost;
        if (e.flow < e.cap && now < dist[e.to]) {
          dist[e.to] = now;
          par[e.to] = i;
          if (its[e.to] == q.end()) {
            its[e.to] = q.push({-dist[e.to], e.to});
          } else
            q.modify(its[e.to], {-dist[e.to], e.to});
        }
        i = e.nxt;
      }
    }
    for (int i = 0; i < n; i++)
      pi[i] = min(pi[i] + dist[i], kInf);
    return par[t] != -1;
  }
  pair<T, T> flow(int s, int t) {
    T flow = 0, cost = 0;
    while (dijkstra(s, t)) {
      T now = kInf;
      for (int node = t; node != s;) {
        int ei = par[node];
        now = min(now, edges[ei].cap - edges[ei].flow);
        node = edges[ei ^ 1].to;
      }
      for (int node = t; node != s;) {
        int ei = par[node];
        edges[ei].flow += now;
        edges[ei ^ 1].flow -= now;
        cost += edges[ei].cost * now;
        node = edges[ei ^ 1].to;
      }
      flow += now;
    }
    return {flow, cost};
  }
};

// use add_edge(from,to,cap,cost) for adding edge
// use flow(s,t) for finding max flow and minimum cost
