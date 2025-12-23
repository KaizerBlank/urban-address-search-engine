#include "../include/palavra.hpp"

// Retorna altura do no.
int Palavra::getHeight(AvlNode* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->height;
    }
}

// Calcula fator de balanceamento.
int Palavra::getBalance(AvlNode* node) {
    if (node == nullptr) {
        return 0;
    } else {
        return getHeight(node->right) - getHeight(node->left);
    }
}

// Operacoes de rotacao para balancear a arvore.

// Realiza rotacao simples a direita para balanceamento.
AvlNode* Palavra::rightRotate(AvlNode* y) {
    AvlNode* x = y->left;
    AvlNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Realiza rotacao simples a esquerda para balanceamento.
AvlNode* Palavra::leftRotate(AvlNode* x) {
    AvlNode* y = x->right;
    AvlNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Funcao recursiva para inserir palavra ou adicionar ID na lista.
AvlNode* Palavra::insertRecursive(AvlNode* node, std::string key, unsigned int id){
    if (node == nullptr) {
        return new AvlNode(key, id);
    }
    if (key < node->key) {
        node->left = insertRecursive(node->left, key, id);
    }
    else if (key > node->key) {
        node->right = insertRecursive(node->right, key, id);
    }
    else {
        // Caso a palavra ja exista, adiciona o ID na lista (encadeamento)
        ListNode* newListNode = new ListNode(id);

        newListNode->next = node->head;
        node->head = newListNode;

        return node;
    }
    
    // Atualiza altura
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Verifica balanceamento e rotaciona se necessario
    int balance = getBalance(node);

    if (balance > 1 && key > node->right->key) {
        return leftRotate(node);
    }

    if (balance < -1 && key < node->left->key) {
        return rightRotate(node);
    }

    if (balance > 1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    if (balance < -1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    return node;
}

// Interface publica para busca. Retorna a lista de IDs.
ListNode* Palavra::search(std::string word) {
    return searchRecursive(root, word);
}

// Busca recursiva por uma chave na arvore.
ListNode* Palavra::searchRecursive(AvlNode* node, std::string key) {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (key == node->key) {
        return node->head;
    }

    if (key < node->key) {
        return searchRecursive(node->left, key);
    }

    else {
        return searchRecursive(node->right, key);
    }
}

// Libera memoria da arvore e das listas encadeadas.
void Palavra::destroyRecursive(AvlNode* node) {
    if (node == nullptr) {
        return;
    }

    destroyRecursive(node->left);
    destroyRecursive(node->right);

    ListNode* currentList = node->head;

    while (currentList != nullptr) {
        ListNode* temp = currentList;
        currentList = currentList->next;
        delete temp;
    }
    
    delete node;
}

// Destrutor e construtor.
Palavra::~Palavra() {
    destroyRecursive(this->root);
}

Palavra::Palavra() {
    root = nullptr;
}

// Interface publica para insercao no indice.
void Palavra::insert(std::string word, unsigned int id) {
    root = insertRecursive(root, word, id);
}