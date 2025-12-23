#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>
#include "palavra.hpp"
#include "logradouro.hpp"
#include "endereco.hpp"

// Estrutura auxiliar para armazenar o resultado de uma busca contendo o objeto Logradouro e a distancia calculada ate a origem.
struct QueryResult {
    Logradouro street;
    double distance;
};

// Esta classe nao possui atributos de estado persistente.
// Ela atua como um "Service" ou "Motor de Execucao".
class QueryProcessor {
    private:
    // Calcula a distancia Euclidiana entre dois pontos.
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);

    // Verifica se um ID existe em uma lista encadeada (busca linear).
    bool existsInList(ListNode* list, unsigned int id);

    // Ordena o vetor de resultados por distancia (Bubble Sort).
    void sortResults(QueryResult* results, int count);

    public:
    // Construtor e Destrutor padrao
    QueryProcessor();
    ~QueryProcessor();

    // Orquestra a busca, intersecao de listas e geracao de resposta.
    void processQuery(std::string queryLine, double originLat, double originLon, int limit, Palavra& index, StreetManager& streetManager);
};



#endif