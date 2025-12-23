#include "../include/endereco.hpp"
#include <iostream>

// Inicializa o vetor dinamico e o mapa de IDs com valores padrao.
StreetManager::StreetManager() {
    this->size = 0;
    this->capacity = 100;
    this->data = new Logradouro[this->capacity];

    this->idMap = new int[MAX_ID];

    for (unsigned int i = 0; i < MAX_ID; i++) {
        this->idMap[i] = -1;
    }
}

// Libera a memoria alocada para os vetores.
StreetManager::~StreetManager() {
    if (this->data != nullptr) {
        delete[] this->data;
    }

    if (this->idMap != nullptr) {
        delete[] this->idMap;
    }
}

// Duplica a capacidade do vetor 'data' quando cheio.
void StreetManager::resize() {
    unsigned int newCapacity = this->capacity * 2;
    Logradouro* newData = new Logradouro[newCapacity];

    for (unsigned int i = 0; i < this->size; i++) {
        newData[i] = this->data[i];
    }

    delete[] this->data;
    this->data = newData;
    this->capacity = newCapacity;
}

// Adiciona um novo logradouro ou atualiza um existente.
bool StreetManager::addEntry(unsigned int id, std::string name, double lat, double lon) {
    // Protecao contra overflow do mapa de IDs
    if (id >= MAX_ID) {
        std::cerr << "AVISO: ID " << id << " excede o limite suportado (" << MAX_ID << "). Ignorado." << std::endl;
    }

    int existingIndex = this->idMap[id];

    if (existingIndex != -1) {
        // Logradouro ja existe: apenas acumula coordenadas
        this->data[existingIndex].addCoordinate(lat, lon);
        return false;
    }

    else {
        // Logradouro novo: verifica capacidade e insere
        if (this->size == this->capacity) {
            resize();
        }

        unsigned int newIndex = this->size;
        this->data[newIndex].initialize(id, name);
        this->data[newIndex].addCoordinate(lat, lon);

        this->idMap[id] = newIndex;

        this->size++;
        
        return true;
    }
}

// Itera sobre todos os logradouros para calcular o ponto medio final.
void StreetManager::finalize() {
    for (unsigned int i = 0; i < this->size; i++) {
        this->data[i].calculateMidPoint();
    }
}

// Retorna o objeto Logradouro associado a um ID via busca direta no mapa.
Logradouro StreetManager::getStreetById(unsigned int idLog) const {
    // Bounds Checking explícito
    if (idLog >= MAX_ID) {
        return Logradouro(); 
    }

    int index = this->idMap[idLog];
    
    if (index == -1) {
        return Logradouro(); 
    }

    return this->data[index];
}

// Retorna o indice do ultimo elemento valido.
unsigned int StreetManager::getLastIndex() const {
    return this->size - 1;
}