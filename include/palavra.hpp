#ifndef PALAVRA_HPP
#define PALAVRA_HPP

#include "aux.hpp"
#include <string>

class Palavra {
    private: 
    AvlNode* root; // Ponteiro para a raiz da arvore AVL (indice invertido)

    // Funcoes Auxiliares da AVL (Privadas)

    // Retorna altura do no.
    int getHeight(AvlNode* node);
    // Calcula fator de balanceamento.
    int getBalance(AvlNode* node);

    // Operacoes de rotacao para balancear a arvore.
    AvlNode* rightRotate(AvlNode* y);
    AvlNode* leftRotate(AvlNode* x);

    // Funcao recursiva para inserir palavra ou adicionar ID na lista.
    AvlNode* insertRecursive(AvlNode* node, std::string key, unsigned int id);

    // Libera memoria da arvore e das listas encadeadas.
    void destroyRecursive(AvlNode* node);

    // Busca recursiva por uma chave na arvore.
    ListNode* searchRecursive(AvlNode* node, std::string key);

    public:
    Palavra();
    ~Palavra();

    // Interface publica para insercao no indice.
    void insert(std::string word, unsigned int id);
    
    // Interface publica para busca. Retorna a lista de IDs.
    ListNode* search(std::string word);
};


#endif