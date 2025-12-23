#include "../include/consulta.hpp"
#include "../include/endereco.hpp"
#include "../include/palavra.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

// Helper para extrair o N-esimo campo de uma string separada por ';'
std::string getField(std::string line, int index) {
    int semicolonCount = 0;
    std::string result = "";
    
    for (size_t i = 0; i < line.length(); i++) {
        char c = line[i];
        if (c == ';') {
            semicolonCount++;
            if (semicolonCount > index) break;
        } else {
            if (semicolonCount == index) result += c;
        }
    }
    return result;
}

int main() {
    // Try-Catch global para capturar erros fatais de memoria ou logica
    try {
        // Otimizacao de I/O para leitura rapida
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);

        // Instancia dos controladores principais
        StreetManager streetManager;
        Palavra wordIndex;
        QueryProcessor processor;

        int N;
        if (!(std::cin >> N)) return 0;
        std::cin.ignore(); 

        // Leitura e Construcao dos Indices
        for (int i = 0; i < N; ++i) {
            std::string line;
            // Validação de fluxo: interrompe se falhar a leitura
            if (!std::getline(std::cin, line)) break;
            
            std::string idStr = getField(line, 1);
            std::string nameStr = getField(line, 3);
            std::string latStr = getField(line, 8);
            std::string lonStr = getField(line, 9);

            try {
                // Conversao de string para tipos numericos
                unsigned int idLog = std::stoul(idStr);
                double lat = std::stod(latStr);
                double lon = std::stod(lonStr);

                // Insercao no gerenciador de enderecos
                // Retorna true se for um logradouro novo (ainda nao indexado)
                bool isNewStreet = streetManager.addEntry(idLog, nameStr, lat, lon);

                // Se for novo, indexa cada palavra do nome na AVL
                if (isNewStreet){
                    std::stringstream ss(nameStr);
                    std::string word;
                    while (ss >> word) {
                        wordIndex.insert(word, idLog);
                    }
                }
            } catch (...) {
                // Ignora linha malformada
                std::cerr << "Aviso: Linha malformada ignorada: " << i << std::endl;
                continue;
            }
        }

        // Finaliza o processamento dos enderecos (calcula medias de coordenadas)
        streetManager.finalize();

        // Processamento das Consultas
        int M, R;
        if (std::cin >> M >> R) {
            std::cin.ignore(); 
            std::cout << M << std::endl;

            for (int i = 0; i < M; ++i) {
                std::string line;
                std::getline(std::cin, line);
                if (line.empty()) continue;

                // Parsing da linha de consulta
                std::string idQuery = getField(line, 0);
                std::string searchTerms = getField(line, 1);
                std::string latOrigStr = getField(line, 2);
                std::string lonOrigStr = getField(line, 3);

                try {
                    double latOrig = std::stod(latOrigStr);
                    double lonOrig = std::stod(lonOrigStr);
                    // Combina ID e Termos para facilitar o processamento interno
                    std::string combinedQuery = idQuery + " " + searchTerms;

                    // Executa a consulta, intersecao e impressao dos resultados
                    processor.processQuery(combinedQuery, latOrig, lonOrig, R, wordIndex, streetManager);
                } catch (...) {
                     std::cerr << "Erro ao processar consulta " << idQuery << std::endl;
                }
            }
        }
    } 
    // Tratamento especifico para falta de memoria
    catch (const std::bad_alloc& e) {
        std::cerr << "Erro Crítico: Memória insuficiente." << std::endl;
        return 1;
    }
    // Tratamento generico para outras excecoes
    catch (const std::exception& e) {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}