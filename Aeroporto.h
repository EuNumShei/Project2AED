//
// Created by HP on 07/12/2023.
//

#ifndef PROJETO2_AEROPORTO_H
#define PROJETO2_AEROPORTO_H

#include<string>
using namespace std;

class Aeroporto{
private:
    string codigo;
    string nome;
    string cidade;
    string pais;
    float latitude;
    float longitude;
public:
    /* Time complexity: O(1)
    */
    Aeroporto(string codigo, string nome, string cidade, string pais, float latitude_, float longitude_){
        this->codigo = codigo;
        this->nome = nome;
        this->cidade = cidade;
        this->pais = pais;
        this->latitude = latitude;
        this->longitude = longitude;
    }
    /* Time complexity: O(1)
    */
    string get_codigo(){return codigo;}
    /* Time complexity: O(1)
    */
    string get_nome(){return nome;}
    /* Time complexity: O(1)
    */
    string get_cidade(){return cidade;}
    /* Time complexity: O(1)
    */
    string get_pais(){return pais;}
    /* Time complexity: O(1)
    */
    float get_latitude(){return latitude;}
    /* Time complexity: O(1)
    */
    float get_longitude(){return longitude;}
    /* Time complexity: O(1)
    */
    bool operator==(const Aeroporto& outro) const {
        return codigo == outro.codigo;
    }
    /* Time complexity: O(1)
    */
    void print() const {
        cout << codigo << " | " << nome << " | " << pais;
    }
};

#endif //PROJETO2_AEROPORTO_H
