#include "../include/logradouro.hpp"

// Configura os dados iniciais de um logradouro (ID e Nome).
void Logradouro::initialize(unsigned int idVal, std::string nameVal) {
    this->id = idVal;
    this->name = nameVal;
    this->latSum = 0;
    this->lonSum = 0;
    addressCount = 0;
}

// Acumula as coordenadas latitude e longitude para calculo posterior da media.
void Logradouro::addCoordinate(double lat, double lon) {
    this->latSum += lat;
    this->lonSum += lon;
    this->addressCount++;
}

// Calcula o centroide (media) das coordenadas acumuladas.
void Logradouro::calculateMidPoint() {
    if (addressCount > 0) {
        this->midLat = latSum / addressCount;
        this->midLon = lonSum / addressCount;
    }
}

// Getters.
std::string Logradouro::getName() const {
    return this->name;
}

unsigned int Logradouro::getId() const {
    return this->id;
}

double Logradouro::getLat() const {
    return this->midLat;
}

double Logradouro::getLon() const {
    return this->midLon;
}
