#include "Sistema.h"
#include <algorithm>
#include <stack>

/*
* Function that reads the airlines.csv file and stores every airline
* Time complexity: O(l*w), being l the number of lines and w the number of words
*/
void Sistema::ler_ficheiro_companhias() {
    ifstream in("../airlines.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        //string palavra;
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string codigo;
            string nome;
            string alcunha;
            string pais;
            int count = 0;

            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        codigo = palavra;
                        break;
                    case 1:
                        nome = palavra;
                        break;
                    case 2:
                        alcunha = palavra;
                        break;
                    case 3:
                        pais = palavra;
                }
                count++;
            }
            Companhia nova_companhia = Companhia(codigo, nome, alcunha, pais);
            vetor_de_companhias.push_back(nova_companhia);
        }
    }
}

/*
* Function that reads the airports.csv file and stores every airport
* Time complexity: O(l*w), being l the number of lines and w the number of words
*/
void Sistema::ler_ficheiro_aeroportos() {
    ifstream in("../airports.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        //string palavra;
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string codigo;
            string nome;
            string cidade;
            string pais;
            float latitude;
            float longitude;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        codigo = palavra;
                        break;
                    case 1:
                        nome = palavra;
                        break;
                    case 2:
                        cidade = palavra;
                        break;
                    case 3:
                        pais = palavra;
                        break;
                    case 4:
                        latitude = stof(palavra);
                        break;
                    case 5:
                        longitude = stof(palavra);
                        break;
                }
                count++;

            }
            Aeroporto novo_aeroporto = Aeroporto(codigo, nome, cidade, pais, latitude, longitude);
            g.addVertex(novo_aeroporto);
        }
    }
}

/*
* Function that reads the flights.csv file and stores every flight
* Time complexity: O(l*w), being l the number of lines and w the number of words
*/
void Sistema::ler_ficheiro_voos() {
    ifstream in("../flights.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        //string palavra;
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string partida;
            string destino;
            string companhia;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        partida = palavra;
                        break;
                    case 1:
                        destino = palavra;
                        break;
                    case 2:
                        companhia = palavra;
                        break;
                }
                count++;
            }
            for (auto comp: vetor_de_companhias) {
                if (companhia == comp.get_codigo()) {
                    g.addEdge(partida, destino, comp);
                }
            }
        }
    }
}

/*
* Function that returns the total number of airlines
* Time complexity: O(1)
*/
    void Sistema::numero_de_companhias() {
        cout << "Numero atual de companhias aereas: " << vetor_de_companhias.size() << "\n";
    }

/*
* Function that returns the total number of airports
* Time complexity: O(1)
*/
    void Sistema::numero_de_aeroportos() {
        cout << "Numero atual de aeroportos: " << g.getNumVertex() << "\n";
    }

/*
* Function that returns the total number of flights
* Time complexity: O(1)
*/
    void Sistema::numero_de_voos() {
        cout << "Numero atual de viagens: " << g.getNumEdges() << "\n";
    }

/*
* Function that returns every airline by code and name
* Time complexity: O(n)
*/
    void Sistema::codigo_das_companhias() {
        cout << "Companhias existentes:\n";
        for (Companhia cmp: vetor_de_companhias) {
            cout << cmp.get_codigo() << " - " << cmp.get_nome() << "\n";
        }
    }

/*
* Function that returns every airport by code, city and country
* Time complexity: O(n)
*/
    void Sistema::codigo_dos_aeroportos() {
        cout << "Aeroportos existentes:\n";
        vector<Aeroporto> aeroportos = g.dfs();
        for (Aeroporto aero: aeroportos) {
            cout << aero.get_codigo() << " - " << aero.get_cidade() << " - " << aero.get_pais() << "\n";
        }
    }

/*
* Function that returns the number of flights in a single airport
* Time complexity: O(n)
*/
    void Sistema::consultar_numero_voos_de_aeroporto() {
        string codigo;
        cout << "Numero de viagens do aeroporto:";
        cin >> codigo;
        cout << "\n" << g.getNumedgesInVertex(codigo) << "\n";
    }

/*
* Function that overloads the operator < for the Aeroporto objects
* Time complexity: O(1)
*/
bool operator<(Aeroporto a1,Aeroporto a2) {
    return a1.get_codigo() < a2.get_codigo();
}

/*
* Function that returns the number of airlines and their names in a single airport
* Time complexity: O(n)
*/
void Sistema::consultar_numero_de_voos_de_aeroporto_companhias(){
    string codigo;
    cout << "Companhias aerias com viagens a partir do aeroporto:";
    cin >> codigo;
    auto a = g.findVertexWithCode(codigo);
    set<Companhia> companhias;
    for(Edge<Aeroporto> ed : a->getAdj()){
        companhias.insert(ed.getWeight());
    }
    cout << "Numero de companhias: " << companhias.size() << '\n';
    for(auto comp : companhias){
        comp.print();
    }
}

/*
* Function that transforms a given input into a string with spaces between words
* Time complexity: O(w), being w the number of words
*/
string conversor_palavras(string in) {
    istringstream iss(in);
    char ch;
    string res;
    while (iss >> ch) {
        if (ch != '_') {
            res.push_back(ch);
        } else {
            res.push_back(' ');
        }
    }
    return res;
}

/*
* Function that allows you to search for an airport
* Time complexity: O(n/2)
*/
Vertex<Aeroporto>* Sistema::procura_aeroporto(string aeroportoID) {
    if(aeroportoID.size() == 3){
        Vertex<Aeroporto> *aeroporto = g.findVertexWithCode(aeroportoID);
        if (aeroporto != nullptr) {
            cout << endl;
            aeroporto->getInfo().print();
            return aeroporto;
        }
    } else if(aeroportoID.size() > 3){
        aeroportoID = conversor_palavras(aeroportoID);
        Vertex<Aeroporto> *aeroporto = g.findVertexWithName(aeroportoID);
        if (aeroporto != nullptr) {
            cout << endl;
            aeroporto->getInfo().print();
            return aeroporto;
        }
    }
    cout << "\nNao existe um aeroporto com esse codigo.\n";
    return nullptr;
}

/*
* Function that allows you to search for an airport by city
* Time complexity: O(n)
*/
vector<Vertex<Aeroporto>*> Sistema::procura_aeroporto_cidade(string cidade) {

    cidade = conversor_palavras(cidade);
    vector<Vertex<Aeroporto>*> res;
    for(Vertex<Aeroporto>* aeroporto : g.getVertexSet()){
        if(aeroporto->getInfo().get_cidade() == cidade){
            cout << endl;
            aeroporto->getInfo().print();
            res.push_back(aeroporto);
        }
    }
    if(res.empty()){
        cout << "\nNao existe nenhum aeroporto nessa cidade.\n";
    }
    return res;
}

/*
* Function that returns the number of flights in a single city
* Time complexity: O((n^2)/2)
*/
    void Sistema::numero_de_viagens_cidade(){
    cout << "Qual cidade quer verificar? (Ex.:New_York) ";
    string cidade;
    cin >> cidade;
    cidade = conversor_palavras(cidade);
    cout << "Aeroportos na cidade " << cidade << '\n';
    vector<Aeroporto> aeros;
    int count = 0;
    for(auto aeroporto : g.getVertexSet()){
        if(aeroporto->getInfo().get_cidade() == cidade) aeros.push_back(aeroporto->getInfo());
    }
    for(Aeroporto aero : aeros){
        aero.print();
        count += g.getNumedgesInVertex(aero.get_codigo());
        cout << g.getNumedgesInVertex(aero.get_codigo()) << " viagens \n";
    }
    cout << "Total: " << count << " viagens a partir da cidade " << cidade << '\n';
}

/*
* Function that returns the number of destination airports from another airport
* Time complexity: O(n)
*/
void Sistema::n_destinos_aeroportos(string codigo) {
    Vertex<Aeroporto> *aeroporto_inicial = g.findVertexWithCode(codigo);
    if (aeroporto_inicial == nullptr) {
        cout << "\nNao existe um aeroporto com esse codigo.\n";
    } else {
        set<Aeroporto> set_de_aeroportos;
        int soma = 0;
        for (const Edge<Aeroporto> &edge: aeroporto_inicial->getAdj()) {
            Aeroporto aeroporto_final = edge.getDest()->getInfo();
            if (set_de_aeroportos.insert(aeroporto_final).second) {
                soma++;
            }
        }
        cout << "\nNumero de aeroportos de destino a partir do aeroporto dado: " << soma << endl;
    }
}

/*
* Function that returns the number of destination cities from a single airport
* Time complexity: O(n)
*/
void Sistema::n_destinos_cidades(string codigo) {
    Vertex<Aeroporto>* aeroporto_inicial = g.findVertexWithCode(codigo);
    if(aeroporto_inicial == nullptr){
        cout << "\nNao existe um aeroporto com esse codigo.\n";
    }else {
        set<string> set_de_cidades;
        int soma = 0;
        for (const Edge<Aeroporto> &edge: aeroporto_inicial->getAdj()) {
            string cidade_final = edge.getDest()->getInfo().get_cidade();
            if (set_de_cidades.insert(cidade_final).second) {
                soma++;
            }
        }
        cout << "\nNumero de cidades de destino a partir do aeroporto dado: " << soma << endl;
    }
}

/*
* Function that returns the number of destination countries from a single airport
* Time complexity: O(n)
*/
void Sistema::n_destinos_paises(string codigo) {
    Vertex<Aeroporto> *aeroporto_inicial = g.findVertexWithCode(codigo);
    if (aeroporto_inicial == nullptr) {
        cout << "\nNao existe um aeroporto com esse codigo.\n";
    } else {
        set<string> set_de_paises;
        int soma = 0;
        for (const Edge<Aeroporto> &edge: aeroporto_inicial->getAdj()) {
            string pais_final = edge.getDest()->getInfo().get_pais();
            if (set_de_paises.insert(pais_final).second) {
                soma++;
            }
        }
        cout << "\nNumero de paises de destino a partir do aeroporto dado: " << soma << endl;
    }
}

/*
* Function that returns the number of destination cities from another airport
* Time complexity: O(n)
*/
void Sistema::n_destinos_aeroportos_alcansaveis(string codigo, int escalas) {
    Vertex<Aeroporto> *aeroporto_inicial = g.findVertexWithCode(codigo);
    if (aeroporto_inicial == nullptr) {
        cout << "\nNao existe um aeroporto com esse codigo.\n";
    } else {
        for(auto v : g.getVertexSet()){
            v->setVisited(false);
        }
        int soma = 0;
        aeroportos_alcansaveis(aeroporto_inicial, soma, escalas);
        cout << "\nNumero de aeroportos de destino a partir do aeroporto dado: " << soma << endl;
    }
}

/*
* Function that returns the number of destination airports from another airport given a maximum number of scales
* Time complexity: O(n), being n the number of edges from v 
*/
void Sistema::aeroportos_alcansaveis(Vertex<Aeroporto> *v, int & soma, int escalas) {
    soma++;
    v->setVisited(true);
    if(escalas + 1 > 0) {
        for (const Edge<Aeroporto> &edge: v->getAdj()) {
            if (!edge.getDest()->isVisited()) {
                aeroportos_alcansaveis(edge.getDest(), soma, escalas - 1);
            }
        }
    }
}

/*
* Function that returns the number of destination cities from another airport given a maximum number of scales
* Time complexity: O(n)
*/
void Sistema::n_destinos_cidades_alcansaveis(string codigo, int escalas) {
    Vertex<Aeroporto> *aeroporto_inicial = g.findVertexWithCode(codigo);
    if (aeroporto_inicial == nullptr) {
        cout << "\nNao existe um aeroporto com esse codigo.\n";
    } else {
        for(auto v : g.getVertexSet()){
            v->setVisited(false);
        }
        int soma = 0;
        set<string> set_de_cidades;
        cidades_alcansaveis(aeroporto_inicial, soma,set_de_cidades, escalas);
        cout << "\nNumero de cidades de destino a partir do aeroporto dado: " << soma << endl;
    }
}

/*
* Auxiliary function for the previous function
* Time complexity: O(n), being n the number of edges of v
*/
void Sistema::cidades_alcansaveis(Vertex<Aeroporto> *v, int & soma, set<string> & set_de_cidades, int escalas) {
    if (set_de_cidades.insert(v->getInfo().get_cidade()).second) {
        soma++;
    }
    v->setVisited(true);
    if(escalas + 1 > 0) {
        for (const Edge<Aeroporto> &edge: v->getAdj()) {
            if (!edge.getDest()->isVisited()) {
                cidades_alcansaveis(edge.getDest(), soma, set_de_cidades, escalas - 1);
            }
        }
    }
}

/*
* Function that returns the number of destination countries from another airport given a maximum number of scales
* Time complexity: O(n)
*/
void Sistema::n_destinos_paises_alcansaveis(string codigo, int escalas) {
    Vertex<Aeroporto> *aeroporto_inicial = g.findVertexWithCode(codigo);
    if (aeroporto_inicial == nullptr) {
        cout << "\nNao existe um aeroporto com esse codigo.\n";
    } else {
        for(auto v : g.getVertexSet()){
            v->setVisited(false);
        }
        int soma = 0;
        set<string> set_de_paises;
        paises_alcansaveis(aeroporto_inicial, soma,set_de_paises, escalas);
        cout << "\nNumero de paises de destino a partir do aeroporto dado: " << soma << endl;
    }
}

/*
* Auxiliary function for the previous function
* Time complexity: O(n), being n the number of edges of v
*/
void Sistema::paises_alcansaveis(Vertex<Aeroporto> *v, int & soma, set<string> & set_de_paises, int escalas) {
    if (set_de_paises.insert(v->getInfo().get_pais()).second) {
        soma++;
    }
    v->setVisited(true);
    if(escalas + 1 > 0) {
        for (const Edge<Aeroporto> &edge: v->getAdj()) {
            if (!edge.getDest()->isVisited()) {
                paises_alcansaveis(edge.getDest(), soma, set_de_paises, escalas - 1);
            }
        }
    }
}

/*
* Function that returns the airport with the biggest air traffic
* Time complexity: O(n)
*/
void Sistema::trafego_maior() {
    int max = 0;
    Aeroporto aeroporto_maior = Aeroporto(0,0,0,0,0,0);
    for(Vertex<Aeroporto>* vertex: g.getVertexSet()){
        int temp = vertex->getAdj().size();
        if(max < temp){
            max = temp;
            aeroporto_maior = vertex->getInfo();
        }
    }
}

/*
* Function that overloads the > operator for Vertex<Aeroporto>* objects
* Time complexity: O(1)
*/
bool compareVertex(Vertex<Aeroporto>* v1, Vertex<Aeroporto>* v2){
    return v1->getAdj().size() > v2->getAdj().size();
}

/*void Sistema::trafego_aereo() {
    vector<Vertex<Aeroporto>*> vetor_aeroportos = g.getVertexSet();
    sort(vetor_aeroportos.begin(), vetor_aeroportos.end(), compareVertex);
    int i = 0;
    for(Vertex<Aeroporto>* vertex : vetor_aeroportos){
        cout << i << " | " <<  vertex->getInfo().get_codigo() << " - " << vertex->getInfo().get_cidade() << " - " << vertex->getInfo().get_pais() << "\n";
    }
}*/

/*
* Function that returns the top n airports with most air traffic
* Time complexity: O(nlog(n))
*/
void Sistema::trafego_aereo_2(int n) {
    vector<Vertex<Aeroporto>*> vetor_aeroportos = g.getVertexSet();
    sort(vetor_aeroportos.begin(), vetor_aeroportos.end(), compareVertex);
    for(int i = 0; i < n; i++ ){
        Aeroporto aeroporto = vetor_aeroportos[i+1]->getInfo();
        cout << i+1 << " | " <<  aeroporto.get_codigo() << " - " << aeroporto.get_cidade() << " - " << aeroporto.get_pais() << "\n";
    }
}

void dfs_art(Vertex<Aeroporto> *v, stack<Aeroporto> &s, vector<Aeroporto> &vector, int &i);

/*
* Function that returns articulation points
* Time complexity: O(n^2)
*/
vector<Aeroporto> Sistema::articulation_points() {
    vector<Aeroporto> res;
    stack<Aeroporto> _stack_;
    int i = 1;

    for(Vertex<Aeroporto>* vertex : g.getVertexSet()){
        vertex->setVisited(false);
        vertex->setNum(-1);
    }

    for( Vertex<Aeroporto>* vertex : g.getVertexSet()){
        if(vertex->getNum() == -1){
            dfs_art(vertex,_stack_,res, i);
        }
    }
    return res;
}

/*
* Auxiliary function for the previous function
* Time complexity: O(n), being n the number of edges of v
*/
void dfs_art(Vertex<Aeroporto> *v, stack<Aeroporto> &s, vector<Aeroporto> &vector, int &i){
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo());

    int children = 0;

    for (const Edge<Aeroporto> &edge : v->getAdj()) {
        Vertex<Aeroporto> *w = edge.getDest();
        if (w->getNum() == -1) {
            children++;
            dfs_art(w, s, vector, i);
            v->setLow(min(v->getLow(), w->getLow()));

            // Check for articulation point: SE ELE FOR ROOT NODE E MAIS Q 1 FILHO OUUU NÃO É ROOT (diferente de 1, como há apenas indices positivos, podemos dizer < 1) e o seu filho depende de si proprio(w) ou dele(o seu pai v) para chegarmos a w.
            if ((v->getNum() == 1 && children > 1) || (v->getNum() > 1 && w->getLow() >= v->getNum())) {
                vector.push_back(v->getInfo());
            }
        } else {
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }

    if (v->getNum() == 1 && children > 1) {
        vector.push_back(v->getInfo());
    }

    s.pop();
}

/*
* Function that prints the critical airports
* Time complexity: O(n), being n the number of articulation points
*/
void Sistema::aeroportos_essenciais(){
    vector<Aeroporto> vetor_aeroportos_essenciais = articulation_points();
    if(!vetor_aeroportos_essenciais.empty()) {
        cout << "Os aeroportos essenciais sao os seguintes:" << endl;
        for(Aeroporto aero: vetor_aeroportos_essenciais) {
            cout << aero.get_codigo() << " - " << aero.get_cidade() << " - " << aero.get_pais() << "\n";
        }
    }
}

/*
* Function that performs a search on the Vertex source, level by level
* Time complexity: O(n + e), being v the number of nodes and e the number of edges
*/
void Sistema::bfs(Vertex<Aeroporto>* source, vector<vector<int>>& distMatrix) {
    for (Vertex<Aeroporto>* vertex : g.getVertexSet()) {
        vertex->setVisited(false);
    }

    queue<pair<Vertex<Aeroporto>*, int>> q;
    q.push({source, 0});
    distMatrix[source->getNum()][source->getNum()] = 0;
    source->setVisited(true);

    while (!q.empty()) {
        pair<Vertex<Aeroporto>*, int> par = q.front();
        Vertex<Aeroporto>* currentVertex = par.first;
        int distance = par.second;
        q.pop();

        for (auto& edge : currentVertex->getAdj()) {
            auto neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                q.push({neighbor, distance + 1});
                neighbor->setVisited(true);
                int sourceNum = source->getNum();
                int neighborNum = neighbor->getNum();
                distMatrix[sourceNum][neighborNum] = distance + 1;
                //distMatrix[neighborNum][sourceNum] = distance + 1;
            }
        }
    }
}

/*
* Function that returns the minimum trip 
* Time complexity: O(n*(n+e))
*/
vector<vector<int>> Sistema::minimum() {
    auto vertices = g.getVertexSet();
    int size = vertices.size();
    vector<vector<int>> distMatrix(size, vector<int>(size, -1));

    for (auto vertex : vertices) {
        bfs(vertex, distMatrix);
    }

    return distMatrix;
}

/*
* Function that returns the longest trips
* Time complexity: O(n^2)
*/
void Sistema::viajemMaisLonga() {

    auto vertices = g.getVertexSet();
    int size = vertices.size();

    int maxDistance = 0;
    vector<pair<Aeroporto, Aeroporto>> maxPairs;

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (maxDistance < distMatrix[i][j]) {
                maxDistance = distMatrix[i][j];
                maxPairs = {{vertices[i]->getInfo(), vertices[j]->getInfo()}};
            } else if (maxDistance == distMatrix[i][j]) {
                maxPairs.push_back({vertices[i]->getInfo(), vertices[j]->getInfo()});
            }
        }
    }

    cout << "As viagens mais longas:" << endl;

    for (const pair<Aeroporto, Aeroporto>& par : maxPairs) {
        cout << "( " ;
        par.first.print();
        cout << " , " ;
        par.second.print();
        cout << " )\n";
    }

    cout << "Com " << maxDistance-1 << " escalas." << endl;
}

/*
* Function that search the best way using dfs algorithm
* Time complexity: O(e), being the number of edges
*/
void Sistema::procuraCaminhoDFS(Vertex<Aeroporto> *vertexInicial, Vertex<Aeroporto>* vertexFinal, string companhia, int distancia , vector<vector<pair<Aeroporto,string>>> & res, vector<pair<Aeroporto,string>> temp){
    temp.push_back({vertexInicial->getInfo(), companhia});
    if(distancia == 0) {
        if (vertexInicial == vertexFinal) {
            res.push_back(temp);
        }
    }else if(distancia > 0) {
        for (const Edge<Aeroporto> &edge: vertexInicial->getAdj()) {
            if (!edge.getDest()->isVisited()) {
                procuraCaminhoDFS(edge.getDest(), vertexFinal, edge.getWeight().get_codigo(), distancia - 1, res, temp);
            }
        }
    }
}

/*
* Function that returns the best possible trip for a given beggining and ending
* Time complexity: O(n^2)
*/
void Sistema::melhorViagemPossivel(Vertex<Aeroporto> *vertexInicial, Vertex<Aeroporto> *vertexFinal) {
    vector<vector<pair<Aeroporto,string>>> res;
    vector<pair<Aeroporto,string>> temp;
    for (Vertex<Aeroporto>* vertex : g.getVertexSet()) {
        vertex->setVisited(false);
    }

    procuraCaminhoDFS(vertexInicial, vertexFinal, "", distMatrix[vertexInicial->getNum()][vertexFinal->getNum()], res,
                      temp);
    cout << "Apresentam-se "  << res.size() << " voos possiveis de " << vertexInicial->getInfo().get_codigo() << " para " << vertexFinal->getInfo().get_codigo();

    for(int i = 0; i < res.size() ; i++){
        cout << "\nAlternativa " << i+1 << " :      ";
        temp = res[i];
        cout << temp[0].first.get_codigo() << "->";
        for(int j = 1; j < temp.size()-1 ; j++){
            cout << temp[j].first.get_codigo() << "(" << temp[j].second << ")" << "->";
        }
        cout << temp[temp.size()-1].first.get_codigo() << "(" << temp[temp.size()-1].second << ")\n";
    }

    cout << "\nCom " << distMatrix[vertexInicial->getNum()][vertexFinal->getNum()]-1 << " escalas.\n\n";
}
/*
* Function that returns the best trip
* Time complexity: O(n^4)
*/
void Sistema::melhorViagem(const vector<Vertex<Aeroporto> *>& vetorAeroportosIniciais, const vector<Vertex<Aeroporto> *>& vetorAeroportosFinais) {
    int min = 3000;

    for(Vertex<Aeroporto> * vertexInicial : vetorAeroportosIniciais) {
        for(Vertex<Aeroporto> * vertexFinal : vetorAeroportosFinais) {
            if(min > distMatrix[vertexInicial->getNum()][vertexFinal->getNum()]){
                min = distMatrix[vertexInicial->getNum()][vertexFinal->getNum()];
            }
        }
    }

    for(Vertex<Aeroporto> * vertexInicial : vetorAeroportosIniciais) {
        for(Vertex<Aeroporto> * vertexFinal : vetorAeroportosFinais) {
            if(min == distMatrix[vertexInicial->getNum()][vertexFinal->getNum()]){
                melhorViagemPossivel(vertexInicial, vertexFinal);
            }
        }
    }
}
