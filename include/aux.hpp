#ifndef AUX_HPP
#define AUX_HPP

#include <string>

// No de uma lista encadeada simples usada para armazenar os IDs dos logradouros onde uma palavra ocorre.
struct ListNode {
    unsigned int id; // ID do logradouro associado
    ListNode* next; // Ponteiro para o proximo elemento da lista

    ListNode(unsigned int val) : id(val), next(nullptr) {}
};

// No da arvore AVL. Armazena a palavra (chave), uma lista de ocorrencias (head), ponteiros para filhos e altura.
struct AvlNode {
    std::string key; // Palavra indexada (chave de busca)
    ListNode* head; // Ponteiro para o inicio da lista de IDs onde a palavra ocorre

    AvlNode* left; // Filho esquerdo
    AvlNode* right; // Filho direito
    int height; // Altura do no para controle de balanceamento

    AvlNode(std::string k, unsigned int firstId) : key(k), left(nullptr), right(nullptr), height(1) {
        head = new ListNode(firstId);
    }
};

// Retorna o maior entre dois inteiros.
inline int max(int x, int y){ 
    if(x > y){
        return x;
    }
    else return y;
}

#endif
