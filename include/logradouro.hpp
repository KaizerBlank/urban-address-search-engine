#ifndef LOGRADOURO_HPP
#define LOGRADOURO_HPP

#include <string>

class Logradouro {
    private:
    std::string name; // Nome textual do logradouro
    unsigned int id; // Identificador unico numérico (IdLog)

    double latSum; // Acumulador de latitudes de todos os enderecos
    double lonSum; // Acumulador de longitudes de todos os enderecos
    unsigned int addressCount; // Contador de enderecos agregados neste logradouro

    double midLat; // Latitude média final (Calculada no finalize)
    double midLon; // Longitude média final (Calculada no finalize)

    public:
    Logradouro() : id(0), latSum(0), lonSum(0), addressCount(0), midLat(0), midLon(0) {}

    // Configura os dados iniciais de um logradouro (ID e Nome).
    void initialize(unsigned int idVal, std::string nameVal);
    // Acumula as coordenadas latitude e longitude para calculo posterior da media.
    void addCoordinate(double lat, double lon);
    // Calcula o centroide (media) das coordenadas acumuladas.
    void calculateMidPoint();

    // Getters.
    std::string getName() const;
    unsigned int getId() const;
    double getLat() const;
    double getLon() const;


};


#endif