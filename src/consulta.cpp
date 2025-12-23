#include "../include/consulta.hpp"
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>

// Calcula a distancia Euclidiana entre dois pontos.
double QueryProcessor::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    return std::sqrt(std::pow(lat1 - lat2, 2) + std::pow(lon1 - lon2, 2));
}

// Verifica se um ID existe em uma lista encadeada (busca linear).
bool QueryProcessor::existsInList(ListNode* list, unsigned int id) {
    ListNode* current = list;
    while (current != nullptr) {
        if (current->id == id) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Ordena o vetor de resultados por distancia (Bubble Sort).
void QueryProcessor::sortResults(QueryResult* results, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (results[j].distance > results[j + 1].distance) {
                QueryResult temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }
}

// Construtor e Destrutor padrao
QueryProcessor::QueryProcessor() {}
QueryProcessor::~QueryProcessor() {}

// Orquestra a busca, intersecao de listas e geracao de resposta.
void QueryProcessor::processQuery(std::string queryLine, double originLat, double originLon, int limit, Palavra& index, StreetManager& streetManager) {
    std::stringstream ss(queryLine);
    std::string word;
    std::string idConsultaStr;

    ss >> idConsultaStr; 

    // Busca pelo primeiro termo para inicializar lista de candidatos
    ss >> word;
    ListNode* candidates = index.search(word);

    if (candidates == nullptr) {
        std::cout << idConsultaStr << ";0" << std::endl;
        return;
    }
    
    // Inicializa vetor de aprovados com a primeira lista
    int maxCandidates = 20000;
    unsigned int* approvedIds = new unsigned int[maxCandidates];
    int approvedCount = 0;

    ListNode* curr = candidates;
    while (curr != nullptr && approvedCount < maxCandidates) {
        approvedIds[approvedCount++] = curr->id;
        curr = curr->next;
    }
    
    // Intersecao com os demais termos da consulta
    while (ss >> word) {
        ListNode* newList = index.search(word);

        if (newList == nullptr) {
            approvedCount = 0;
            break;
        }

        // Mantem apenas IDs que tambem existem na newList (AND logico)
        int newCount = 0;
        for (int i = 0; i < approvedCount; i++) {
            if (existsInList(newList, approvedIds[i])) {
                approvedIds[newCount++] = approvedIds[i]; 
            }
        }
        approvedCount = newCount;
        
        if (approvedCount == 0) break;
    }

    // Recuperacao de dados e Calculo de Distancia
    QueryResult* finalResults = new QueryResult[approvedCount];
    int validCount = 0;

    for (int i = 0; i < approvedCount; i++) {
        Logradouro rua = streetManager.getStreetById(approvedIds[i]);
        
        if (rua.getId() != 0) {
            finalResults[validCount].street = rua;
            finalResults[validCount].distance = calculateDistance(originLat, originLon, rua.getLat(), rua.getLon());
            validCount++;
        }
    }

    // Ordenacao e Impressao
    if (validCount > 0) {
        sortResults(finalResults, validCount);
    }

    int printCount = (validCount < limit) ? validCount : limit;

    std::cout << idConsultaStr << ";" << printCount << std::endl;

    for (int i = 0; i < printCount; i++) {
        std::cout << finalResults[i].street.getId() << ";" << finalResults[i].street.getName() << std::endl;
    }

    delete[] approvedIds;
    delete[] finalResults;
}