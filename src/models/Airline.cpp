
#include "Airline.h"

// Constructor
/**
 * @brief Constructor for Airline class.
 * @param code - the airline code.
 * @param name - the airline name.
 * @param callsign - the airline callsign.
 * @param country - the country of the airline.
 */
Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country)
        : code(code), name(name), callsign(callsign), country(country) {}

// Getters

/**
 * @brief Gets the airline code.
 * @return The airline code.
 */
string Airline::getCode() const {
    return code;
}

/**
 * @brief Gets the airline name.
 * @return The airline name.
 */
string Airline::getName() const {
    return name;
}

/**
 * @brief Gets the airline callsign.
 * @return The airline callsign.
 */
string Airline::getCallsign() const {
    return callsign;
}

/**
 * @brief Gets the airline country,
 * @return The country of the airline.
 */
string Airline::getCountry() const {
    return country;
}

// Setters

/**
 * @brief Set the airline code.
 * @param code - the new airline code.
 */
void Airline::setCode(const string &code) {
    this->code = code;
}

/**
 * @brief Set the airline name.
 * @param name - the new airline name.
 */
void Airline::setName(const string &name) {
    this->name = name;
}

/**
 * @brief Set the airline callsign.
 * @param callsign - the new airline callsign.
 */
void Airline::setCallsign(const string &callsign) {
    this->callsign = callsign;
}

/**
 * @brief Set the country of the airline.
 * @param country - the new country of the airline.
 */
void Airline::setCountry(const string &country) {
    this->country = country;
}