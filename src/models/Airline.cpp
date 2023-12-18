//
// Created by jpsantos on 16-12-2023.
//

#include "Airline.h"

// Constructor
Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country)
        : code(code), name(name), callsign(callsign), country(country) {}

// Getters
std::string Airline::getCode() const {
    return code;
}

std::string Airline::getName() const {
    return name;
}

std::string Airline::getCallsign() const {
    return callsign;
}

std::string Airline::getCountry() const {
    return country;
}

// Setters
void Airline::setCode(const std::string &code) {
    this->code = code;
}

void Airline::setName(const std::string &name) {
    this->name = name;
}

void Airline::setCallsign(const std::string &callsign) {
    this->callsign = callsign;
}

void Airline::setCountry(const std::string &country) {
    this->country = country;
}