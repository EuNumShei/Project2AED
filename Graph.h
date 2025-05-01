#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H


#include <cstddef>
#include <vector>
#include <queue>
#include "Companhia.h"
#include "Aeroporto.h"
#include <string>
#include <typeinfo>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Node {
    Vertex(T in);

    T aeroporto;             // contents
    vector<Edge<T>> adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex<T> *dest, Companhia w);
    bool removeEdgeTo(Vertex<T> *d);
public:
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    friend class Graph<T>;

    int getNum() const;

    void setNum(int num);

    int getLow() const;

    void setLow(int low);
};

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    Companhia companhia;         // edge weight
public:
    Edge(Vertex<T> *d, Companhia w);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    Companhia getWeight() const;
    void setWeight(Companhia weight);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // Node set
    static int i;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    int getNumEdges() const;
    int getNumedgesInVertex(const string &in) const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const string &sourc, const string &dest, Companhia w);
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    int inDegree(const T &v) const;
    vector<T> dfs() const;
    void dfsVisit(Vertex<T> *v, vector<T> & res) const;
    Vertex<Aeroporto> * findVertexWithCode(const string &in) const;

    Vertex<Aeroporto> *findVertexWithName(const string &in) const;

    vector<Vertex<Aeroporto> *> findVertexWithCity(const string &in) const;
};

/****************** Provided constructors and functions ********************/
/* 
*  Node constructor
*  Time complexity: O(1)
*/
template <class T>
Vertex<T>::Vertex(T in): aeroporto(in) {}

/* 
*  Edge constructor
*  Time complexity: O(1)
*/
template <class T>
Edge<T>::Edge(Vertex<T> *d, Companhia w): dest(d), companhia(w) {}

/* 
*  Function that returns number of nodes
*  Time complexity: O(1)
*/
template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

/* 
*  Function that returns the number of edges
*  Time complexity: O(n)
*/
template <class T>
int Graph<T>::getNumEdges() const {
    int count = 0;
    for(auto v : vertexSet) count += v->getAdj().size();
    return count;
}

/* 
*  Function that returns the number of edges in a vertex
*  Time complexity: O(n/2)
*/
template <class T>
int Graph<T>::getNumedgesInVertex(const string &in) const {
    Vertex<T> * v = findVertexWithCode(in);
    return v->getAdj().size();
}

/* 
*  Function that returns the number of total nodes
*  Time complexity: O(1)
*/
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

/* 
*  Function that returns the information of a node
*  Time complexity: O(1)
*/
template<class T>
T Vertex<T>::getInfo() const {
    return aeroporto;
}

/* 
*  Function that modifies the information of a node
*  Time complexity: O(1)
*/
template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::aeroporto = in;
}

/* 
*  Function that verifies if a node is being processed or not
*  Time complexity: O(1)
*/
template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

/* 
*  Function that modifies if a node is being processed or not
*  Time complexity: O(1)
*/
template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

/* 
*  Function that returns the order in which a node is visited in a DFS visit
*  Time complexity: O(1)
*/
template<class T>
int Vertex<T>::getNum() const {
    return num;
}

/* 
*  Function that defines the order in which a node is visited in a DFS visit
*  Time complexity: O(1)
*/
template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}

/* 
*  Function that returns the lower node a certain node can visit in a DFS visit
*  Time complexity: O(1)
*/
template<class T>
int Vertex<T>::getLow() const {
    return low;
}

/* 
*  Function that defines the order in which a node is visited in a DFS visit
*  Time complexity: O(1)
*/
template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}

/* 
*  Function that returns the destination of an edge
*  Time complexity: O(1)
*/
template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

/* 
*  Function that modifies the destination of an edge
*  Time complexity: O(1)
*/
template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

/* 
*  Function that returns the weight of an edge
*  Time complexity: O(1)
*/
template<class T>
Companhia Edge<T>::getWeight() const {
    return companhia;
}

/* 
*  Function that modifies the weight of an edge
*  Time complexity: O(1)
*/
template<class T>
void Edge<T>::setWeight(Companhia weight) {
    Edge::companhia = weight;
}

/*
 * Auxiliary function to find a node with a given content.
 * Time complexity: O(n/2)
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return NULL;
}

/*
 * Function that returns if a node has been visited or not
 * Time complexity: O(1)
 */
template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

/*
 * Function that modifies if a node has been visited or not
 * Time complexity: O(1)
 */
template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

/*
 * Function that returns the list of outgoing edges of a node
 * Time complexity: O(1)
 */
template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

/*
 * Function that modifies the list of outgoing edges of a node
 * Time complexity: O(1)
 */
template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}

template <class T> int Graph<T>::i = 0;
/*
 *  Adds a Node with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a Node with that content already exists.
 *  Time complexity: O(n/2)
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    Vertex<T>* Node = findVertex(in);
    if(Node == NULL){
        Vertex<T> * v = new Vertex<T>(in);
        v->setNum(i);
        i++;
        vertexSet.push_back(v);
        return true;
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination Node does not exist.
 * Time complexity: O(n/2)
 */
template <class T>
bool Graph<T>::addEdge(const string &sourc, const string &dest, Companhia w) {
    Vertex<T> * dest_v = findVertexWithCode(dest);
    Vertex<T> * sourc_v = findVertexWithCode(sourc);
    if(dest_v != NULL and sourc_v != NULL){
        sourc_v->addEdge(dest_v, w);
        return true;
    }
    return false;
}

/*
 * Auxiliary function to add an outgoing edge to a Node (this),
 * with a given destination Node (d) and edge weight (w).
 * Time complexity: O(1)
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, Companhia w) {
    Edge<T> new_edge = Edge<T>(d, w);
    adj.push_back(new_edge);
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 * Time complexity: O(n/2)
 */
//TODO
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> * dest_v = findVertex(dest);
    Vertex<T> * sourc_v = findVertex(sourc);
    if(dest_v != NULL and sourc_v != NULL){
        bool removed = sourc_v->removeEdgeTo(dest_v);
        return removed;
    }

    return false;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a Node (this).
 * Returns true if successful, and false if such edge does not exist.
 * Time complexity: O(n^2)
 */
//TODO
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    bool flag = false;
    auto it = adj.begin();
    while(it != adj.end()){
        if(it->getDest() == d){
            adj.erase(it);
            flag = true;
            break;
        }
        it++;
    }
    return flag;
}

/*
* Function that removes a node and its edges from the vector vertexSet
* Time complexity: O(n^2)
*/
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T> * v = findVertex(in);
    bool flag = false;
    if(v != NULL){
        auto it = vertexSet.begin();
        while(it != vertexSet.end()){
            if(*it == v){
                vertexSet.erase(it);
                flag = true;
            }
            else{
                bool f = (*it)->removeEdgeTo(v);
            }

            it++;
        }
        return flag;
    }
    return false;
}

/*
* Function that visits a graph, starting in the initial node
* and going as far along a branch as possible before backtracking, done using recursion
* Time complexity: O(n + b), being n the size of vertexSet and e the size of Adj for each node
*/
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for(auto v : vertexSet){
        v->setVisited(false);
    }
    for(int i = 0; i< vertexSet.size(); i++){
        if(!vertexSet[i]->isVisited())
            dfsVisit(vertexSet[i], res);
    }
    return res;
}

/*
 * Auxiliary function that visits a Node (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 * Time complexity : O(e)
 */
// TODO
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    res.push_back(v->getInfo());
    v->setVisited(true);
    for (Edge<T> e : v->getAdj()){
        if(!e.getDest()->isVisited()){
            dfsVisit(e.getDest(), res);
        }
    }

}

#endif //PROJETO2_GRAPH_H
