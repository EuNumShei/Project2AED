#include <iostream>
#include "Sistema.h"
using namespace std;

void indicacao_de_processo(){
    cout << "Por favor, aguarde enquanto o sistema esta em processamento..." << endl;
}

void bem_vindo(){
    cout << "Processamento finalizado." << endl << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "-          Bem vindo ao sistema NIEUM           -" << endl;
    cout << "-------------------------------------------------" << endl << endl;
}

/** Define uma mensagem inicial para o menu com os comandos disponíveis
* @param vetor de strings com os comandos disponíveis
* Time complexity: O(n)
*/
void print_inicio(const vector<string>& vetor) {
    cout << endl <<"Aqui se encontram todos os comandos disponiveis:" << endl;
    for (const string &metodo: vetor) {
        cout << "     * " << metodo << endl;
    }
}


/** Define o resultado de um comando mal introduzido
* Time complexity: O(1)
*/
void print_incorreto(){
    cout << "Escrito incorretamente. Tente novamente." << endl ;
}

void apresentacao_do_menu_inicial(){
    vector<string> vetor = {"consultar_n_de_companhias      Para consultar o numero de companhias que existem",
                            "consultar_n_de_aeroportos      Para consultar o numero de aeroportos a nivel global",
                            "consultar_n_de_voos            Para consultar o numero de todos os voos possiveis",
                            "consultar_companhias           Para consultar as companhias existentes",
                            "consultar_aeroportos           Para consultar os aeroportos existentes",
                            "consultar_n_voos_aeroporto     Para consultar o numero de voos de um determinado aeroporto",
                            "consultar_companhias_aeroporto Para consultar companhias com viagens de um determinado aeroporto",
                            "consultar_n_viagens_cidade     Para consultar o numero de viagens a partir dos aeroportos de uma dada cidade",
                            "consultar_n_destinos           Para consultar o numero de destinos de um determinado aeroporto",
                            "consultar_n_alcancaveis        Para consultar o numero de destinos de um dado aeroporto usando escalas",
                            "consultar_viajem_longa         Para consultar a viajem mais longa possivel da rede de trafego",
                            "consultar_trafego_aereo        Para consultar os aeroportos com a maior capacidade de tráfego aéreo",
                            "consultar_essencias            Para consultar os aeroportos essencias para a rede de trafego",
                            "consultar_alteracoes           Para consultar todas as alteracoes feitas ao sistema",
                            "procurar_melhor_viagem         Para procurar a melhor viagem a partir de uma partida e de um destino",
                            "sair                           Para terminar programa"};

    cout << "---------Menu inicial---------" << endl;
    print_inicio(vetor);
}

void menu_de_destinos(Sistema & sistema){
    vector<string> vetor = {"aeroportos                     Para consultar todos os aeroportos de destino",
                            "cidades                        Para consultar todos as cidades de destino",
                            "pais                           Para consultar todos os paises de destino",
                            "sair"};
    while (true){
        cout << "-------Consulta de destinos-------" << endl;
        print_inicio(vetor);
        string comando;
        cin >> comando;
        if(comando == "aeroportos"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar os seus paises de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            sistema.n_destinos_aeroportos(codigo);
        }
        else if(comando == "cidades"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar os seus paises de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            sistema.n_destinos_cidades(codigo);
        }
        else if(comando == "pais"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar os seus paises de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            sistema.n_destinos_paises(codigo);
        }
        else if(comando == "sair"){
            apresentacao_do_menu_inicial();
            break;
        }
        else{
            print_incorreto();
        }
    }
}

void menu_melhor_viagem(Sistema & sistema){
    vector<string> vetor = {"aeroporto                      Para procurar o melhor voo recorrendo ao codigo ou nome do aeroporto",
                            "cidade                         Para procurar o melhor voo recorrendo a todos os aeroportos de uma dada cidade",
                            "coordenadas                    Para procurar o melhor voo recorrendo a coordenadas geograficas",};
    string resposta;
    bool continuar = true;
    while (continuar){
        cout << "-------Consulta de viagens-------" << endl;
        print_inicio(vetor);

        cout << "\nEscolha qual metodo prefere para encontrar o(s) aeroporto(s) que deseja como partida.";

        string comando;
        vector<Vertex<Aeroporto>*> aeroportos_iniciais;

        while(comando != "aeroporto" and comando != "cidade" and comando != "coordenadas") {
            cout << "Escreva aqui:";
            cin >> comando;
            cout << endl;
            if (comando == "aeroporto") {
                string aeroporto;
                cout << "Indique o aeroporto de onde deseja iniciar a sua partida, usando o codigo ou nome correspondente (Ex.:OPO)";
                Vertex<Aeroporto> *aeroporto_inicial = nullptr;
                while (aeroporto_inicial == nullptr) {
                    cout << "Escreva aqui:";
                    cin >> aeroporto;
                    aeroporto_inicial = sistema.procura_aeroporto(aeroporto);
                }
                aeroportos_iniciais.push_back(aeroporto_inicial);
            } else if (comando == "cidade") {
                string cidade;
                cout << "Indique o nome da cidade de onde deseja inicializar a sua viagem (Ex.:New_York)";

                while (aeroportos_iniciais.empty()) {
                    cout << "Escreva aqui:";
                    cin >> cidade;
                    aeroportos_iniciais = sistema.procura_aeroporto_cidade(cidade);
                }
            } else if (comando == "coordenadas") {

            } else {
                print_incorreto();
            }
        }

        cout << "\nEscolha qual metodo prefere para encontrar o(s) aeroporto(s) que deseja como destino.";
        comando = "";

        vector<Vertex<Aeroporto>*> aeroportos_finais;
        while(comando != "aeroporto" and comando != "cidades" and comando != "coordenadas") {
            cout << "Escreva aqui:";
            cin >> comando;
            cout << endl;
            if (comando == "aeroporto") {
                string aeroporto;
                cout<< "Indique o aeroporto de onde deseja finalizar a sua viagem, usando o codigo ou nome correspondente (Ex.:OPO)";
                Vertex<Aeroporto> *aeroporto_final = nullptr;
                while (aeroporto_final == nullptr) {
                    cout << "Escreva aqui:";
                    cin >> aeroporto;
                    aeroporto_final = sistema.procura_aeroporto(aeroporto);
                }
                aeroportos_finais.push_back(aeroporto_final);
            } else if (comando == "cidade") {
                string cidade;
                cout << "Indique o nome da cidade de onde deseja finalizar a sua viagem (Ex.:New_York)";
                while (aeroportos_finais.empty()) {
                    cout << "Escreva aqui:";
                    cin >> cidade;
                    aeroportos_finais = sistema.procura_aeroporto_cidade(cidade);
                }
            } else if (comando == "coordenadas") {

            } else {
                print_incorreto();
            }
        }
        cout << "\nAeroportos pedidos encontrados.\n";
        sistema.melhorViagem(aeroportos_iniciais, aeroportos_finais);
        cout << "Continuar procura? Digite 'nao' para voltar ao menu principal.\n";
        cin >> resposta;
        if(resposta == "nao"){
            continuar = false;
        }
    }
    apresentacao_do_menu_inicial();
}

void menu_de_destinos_alcansaveis(Sistema & sistema){
    vector<string> vetor = {"aeroportos                     Para consultar o numero de aeroportos acessiveis usando escalas",
                            "cidades                        Para consultar o numero das cidades acessiveis usando escalas",
                            "pais                           Para consultar o numero dos paises acessiveis usando escalas",
                            "sair"};
    cout << "-------Consulta de destinos alcansaveis-------" << endl;
    print_inicio(vetor);
    while (true){
        string comando;
        cin >> comando;
        if(comando == "aeroportos"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar os seus paises de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            string escalas;
            cout<<"\nEscreva o numero de escalas (Ex.:1):";
            cin >> escalas;
            try{
                int escalas_int = stoi(escalas);
                sistema.n_destinos_aeroportos_alcansaveis(codigo,escalas_int);
            }catch(exception e){
                cout << "\nNumero errado. Tente novamente" << endl;
            }
        }
        else if(comando == "cidades"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar os seus paises de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            string escalas;
            cout<<"\nEscreva o numero de escalas (Ex.:1):";
            cin >> escalas;
            try{
                int escalas_int = stoi(escalas);
                sistema.n_destinos_cidades_alcansaveis(codigo,escalas_int);
            }catch(exception e){
                cout << "\nNumero errado. Tente novamente" << endl;
            }
        }
        else if(comando == "pais"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar os seus paises de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            string escalas;
            cout<<"\nEscreva o numero de escalas (Ex.:1):";
            cin >> escalas;
            try{
                int escalas_int = stoi(escalas);
                sistema.n_destinos_paises_alcansaveis(codigo,escalas_int);
            }catch(exception e){
                cout << "\nNumero errado. Tente novamente" << endl;
            }
        }
        else if(comando == "sair"){
            apresentacao_do_menu_inicial();
            break;
        }
        else{
            print_incorreto();
        }
    }
}

void menu_inicial(Sistema & sistema) {
    apresentacao_do_menu_inicial();
    while (true) {
        string comando;
        cin >> comando;
        if (comando == "consultar_n_de_companhias") {
            sistema.numero_de_companhias();
        }else if (comando == "consultar_n_de_aeroportos") {
            sistema.numero_de_aeroportos();
        }else if (comando == "consultar_n_de_voos") {
            sistema.numero_de_voos();
        }else if (comando == "consultar_companhias") {
            sistema.codigo_das_companhias();
            apresentacao_do_menu_inicial();
        }else if (comando == "consultar_aeroportos") {
            sistema.codigo_dos_aeroportos();
            apresentacao_do_menu_inicial();
        }else if (comando == "consultar_n_voos_aeroporto") {
            sistema.consultar_numero_voos_de_aeroporto();
        }else if (comando == "consultar_companhias_aeroporto") {
            sistema.consultar_numero_de_voos_de_aeroporto_companhias();
            apresentacao_do_menu_inicial();
        }else if (comando == "consultar_n_viagens_cidade") {
            sistema.numero_de_viagens_cidade();
            apresentacao_do_menu_inicial();
        }else if (comando == "consultar_n_destinos") {
            menu_de_destinos(sistema);
        }else if (comando == "consultar_n_alcancaveis") {
            menu_de_destinos_alcansaveis(sistema);
        } else if (comando == "consultar_trafego_aereo") {
            string n;
            cout<<"\nEscreva o numero de aeroportos que pretende vizualizar (Ex.:1):";
            cin >> n;
            try{
                int n_int = stoi(n);
                sistema.trafego_aereo_2(n_int);
                apresentacao_do_menu_inicial();
            }catch(exception e){
                cout << "\nNumero errado. Tente novamente" << endl;
            }
        } else if (comando == "consultar_essencias") {
            sistema.aeroportos_essenciais();
            apresentacao_do_menu_inicial();
        } else if (comando == "consultar_viajem_longa") {
            sistema.viajemMaisLonga();
        } else if (comando == "procurar_melhor_viagem") {
            menu_melhor_viagem(sistema);
        } else if (comando == "sair") {
            // guardar_dados();
            break;
        } else {
            print_incorreto();
        }
    }
}



int main(){
    indicacao_de_processo();
    Sistema sistema;
    bem_vindo();
    menu_inicial(sistema);
    sistema.codigo_dos_aeroportos();
    sistema.consultar_numero_voos_de_aeroporto();
    return 0;
}