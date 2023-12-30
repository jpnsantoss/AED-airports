
#include "Airport.h"

// Constructor
Airport::Airport() {
    this->airportCode = "";
    this->airportName = "";
    this->city = "";
    this->country = "";
    this->location = Location();
}

/**
 * @brief Constructor for Airport class.
 * @param code - the airport code.
 * @param name - the airport name.
 * @param city - the city of the airport.
 * @param country - the country of the airport.
 * @param location - the location of the airport.
 */
Airport::Airport(const string &airportCode, const string &airportName, const string &city, const string &country, const Location &location)
        : airportCode(airportCode), airportName(airportName), city(city), country(country), location(location) {}

// Getters
/**
 * @brief Gets the airport code.
 * @return The airport code.
 */
string Airport::getAirportCode() const {
    return airportCode;
}

/**
 * @brief Gets the airport name.
 * @return The airport name.
 */
string Airport::getAirportName() const {
    return airportName;
}

/**
 * @brief Gets the city of the airport.
 * @return The city of the airport.
 */
string Airport::getCity() const {
    return city;
}

/**
 * @brief Gets the country of the airport.
 * @return The country of the airport.
 */
string Airport::getCountry() const {
    return country;
}

/**
 * @brief Gets the location of the airport.
 * @return The location of the airport.
 */
Location Airport::getLocation() const {
    return location;
}

// Setters
/**
 * @brief Sets the airport code.
 * @param code - the new airport code.
 */
void Airport::setAirportCode(const string &airportCode) {
    this->airportCode = airportCode;
}

/**
 * @brief Sets the airport name.
 * @param name - the new airport name.
 */
void Airport::setAirportName(const string &airportName) {
    this->airportName = airportName;
}

/**
 * @brief Sets the city of the airport.
 * @param city - the new city of the airport.
 */
void Airport::setCity(const string &city) {
    this->city = city;
}

/**
 * @brief Sets the country of the airport.
 * @param country - the new country of the airport.
 */
void Airport::setCountry(const string &country) {
    this->country = country;
}

/**
 * @brief Sets the location of the airport.
 * @param location - the new location of the airport.
 */
void Airport::setLocation(const Location &location) {
    this->location = location;
}

/**
 * @brief Overloaded output stream operator for Airport class.
 * @param os - the output stream.
 * @param airport - the airport object.
 * @return The output stream.
 */
ostream &operator<<(ostream &os, Airport &airport) {
    os << airport.getAirportCode();
    return os;
}

/**
 * @brief Overloaded equality operator for Airport class.
 * @param other - the other airport object for comparison.
 * @return True if the airports have the same airport code and False otherwise.
 */
bool Airport::operator==(const Airport &other) const {
    return (this->airportCode == other.getAirportCode());
}
