//
// Created by HP on 07/12/2023.
//

#ifndef PROJETO2_COMPANHIA_H
#define PROJETO2_COMPANHIA_H

#include<string>
#include <iostream>
using namespace std;

class Companhia {
private:
    string codigo;
    string nome;
    string alcunha;
    string pais;
public:
    /* Time complexity: O(1)
    */
    Companhia(string codigo, string nome, string alcunha, string pais){
        this->codigo = codigo;
        this->nome = nome;
        this->alcunha = alcunha;
        this->pais = pais;
    }
    /* Time complexity: O(1)
    */
    string get_codigo(){return codigo;}
    /* Time complexity: O(1)
    */
    string get_nome(){return nome;}
    /* Time complexity: O(1)
    */
    string get_alcunha(){return alcunha;}
    /* Time complexity: O(1)
    */
    string get_pais(){return pais;}
    /* Time complexity: O(1)
    */
    void print(){
        cout << codigo << " | " << nome << " | " << pais << '\n';
    }
    /* Time complexity: O(1)
    */
    bool operator<(const Companhia& outro) const {
        return codigo < outro.codigo;
    }
};


#endif //PROJETO2_COMPANHIA_H
