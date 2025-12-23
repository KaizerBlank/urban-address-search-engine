#ifndef ENDERECO_HPP
#define ENDERECO_HPP

#include "logradouro.hpp"

class StreetManager {
    private:
    Logradouro* data; // Vetor dinamico principal
    unsigned int size; // Numero atual de elementos
    unsigned int capacity; // Capacidade atual do vetor

    int* idMap; // Tabela de Hash/Lookup direta para mapear ID -> Indice no vetor data
    const unsigned int MAX_ID = 1000000;

    // Duplica a capacidade do vetor 'data' quando cheio.
    void resize();

    public:
    // Inicializa o vetor dinamico e o mapa de IDs com valores padrao.
    StreetManager();
    // Libera a memoria alocada para os vetores.
    ~StreetManager();

    // Adiciona um novo logradouro ou atualiza um existente.
    bool addEntry(unsigned int id, std::string name, double lat, double lon);

    // Itera sobre todos os logradouros para calcular o ponto medio final.
    void finalize();

    // Retorna o objeto Logradouro associado a um ID via busca direta no mapa.
    Logradouro getStreetById(unsigned int idLog) const;

    // Retorna o indice do ultimo elemento valido.
    unsigned int getLastIndex() const;
};

#endif