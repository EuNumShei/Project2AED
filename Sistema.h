#ifndef PROJETO2_SISTEMA_H
#define PROJETO2_SISTEMA_H

#include "Graph.h"
#include "Aeroporto.h"
#include "Companhia.h"
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Sistema {
private:
    Graph<Aeroporto> g;
    vector<Companhia> vetor_de_companhias;
    vector<vector<int>> distMatrix;
    void ler_ficheiro_aeroportos();
    void ler_ficheiro_companhias();
    void ler_ficheiro_voos();
public:
    Sistema(){
        ler_ficheiro_companhias();
        ler_ficheiro_aeroportos();
        ler_ficheiro_voos();
        distMatrix = minimum();
    }

    void numero_de_companhias();

    void numero_de_aeroportos();

    void numero_de_voos();

    void consultar_numero_de_voos_de_aeroporto_companhias();

    void numero_de_viagens_cidade();

    void consultar_numero_voos_de_aeroporto();

    void codigo_das_companhias();

    void codigo_dos_aeroportos();

    void n_destinos_aeroportos(string codigo);

    void n_destinos_cidades(string codigo);

    void n_destinos_paises(string codigo);

    void n_destinos_aeroportos_alcansaveis(string codigo, int escalas);

    void aeroportos_alcansaveis(Vertex<Aeroporto> *v, int &soma, int escalas);

    void n_destinos_cidades_alcansaveis(string codigo, int escalas);

    void cidades_alcansaveis(Vertex<Aeroporto> *v, int &soma, set<string> &set_de_cidades, int escalas);

    void n_destinos_paises_alcansaveis(string codigo, int escalas);

    void paises_alcansaveis(Vertex<Aeroporto> *v, int &soma, set<string> &set_de_paises, int escalas);

    void trafego_aereo();

    void trafego_maior();

    void trafego_aereo_2(int n);

    void aeroportos_essenciais();

    vector<Aeroporto> articulation_points();

    void viajemMaisLonga();

    vector<vector<int>> minimum();

    void bfs(Vertex<Aeroporto> *source, vector<vector<int>> &distMatrix);

    Vertex<Aeroporto>* procura_aeroporto(string aeroportoID);

    vector<Vertex<Aeroporto> *> procura_aeroporto_cidade(string cidade);

    void melhorViagemPossivel(Vertex<Aeroporto> *vertexInicial, Vertex<Aeroporto> *vertexFinal);

    void procuraCaminhoDFS(Vertex<Aeroporto> *vertexInicial, Vertex<Aeroporto> *vertexFinal, string companhia,
                           int distancia, vector<vector<pair<Aeroporto, string>>> &res,
                           vector<pair<Aeroporto, string>> temp);

    void melhorViagem(const vector<Vertex<Aeroporto> *> &vetorAeroportosIniciais,
                      const vector<Vertex<Aeroporto> *> &vetorAeroportosFinais);
};



#endif //PROJETO2_SISTEMA_H
