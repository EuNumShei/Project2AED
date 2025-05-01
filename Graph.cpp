#include "Graph.h"
/* Time complexity: O(n/2)
*/
template<>
Vertex<Aeroporto> * Graph<Aeroporto>::findVertexWithCode(const string &in) const {
    for (auto v : vertexSet)
        if (v->getInfo().get_codigo() == in)
            return v;
    return NULL;
}

/* Time complexity: O(n/2)
*/
template<>
Vertex<Aeroporto> * Graph<Aeroporto>::findVertexWithName(const string &in) const {
    for (auto v : vertexSet)
        if (v->getInfo().get_nome() == in)
            return v;
    return NULL;
}

/* Time complexity: O(n)
*/
template<>
vector<Vertex<Aeroporto>*> Graph<Aeroporto>::findVertexWithCity(const string &in) const {
    vector<Vertex<Aeroporto>*> res;
    for (auto v : vertexSet)
        if (v->getInfo().get_cidade() == in)
            res.push_back(v);
    return res;
}
