
#include "Flight.h"

// Constructor
/**
 * @brief Constructor for Flight class.
 * @param source - the source airport of the flight.
 * @param target - the target airport of the flight.
 * @param airline - the airline responsible for the flight.
 */
Flight::Flight(const Airport &source, const Airport &target, const Airline &airline)
        : source(source), target(target), airline(airline), distance(source.getLocation().calculateDistanceTo(target.getLocation())) {}

// Getters

/**
 * @brief Gets the source airport of the flight.
 * @return The source airport.
 */
Airport Flight::getSource() const {
    return source;
}

/**
 * @brief Gets the target airport of the flight.
 * @return The target airport.
 */
Airport Flight::getTarget() const {
    return target;
}

/**
 * @brief Gets the airline responsible for the flight.
 * @return The airline.
 */
Airline Flight::getAirline() const {
    return airline;
}

/**
 * @brief Gets the distance between the source and target airports.
 * @return The distance of the flight.
 */
double Flight::getDistance() const {
    return distance;
}

// Setters

/**
 * @brief Sets the source airport of the flight.
 * @param source - The new source airport.
 */
void Flight::setSource(const Airport &source) {
    this->source = source;
    this->distance = this->source.getLocation().calculateDistanceTo(this->target.getLocation());
}

/**
 * @brief Sets the target airport of the flight.
 * @param target - The new target airport of the flight.
 */
void Flight::setTarget(const Airport &target) {
    this->target = target;
    this->distance = this->source.getLocation().calculateDistanceTo(this->target.getLocation());
}

/**
 * @brief Sets the airline responsible for the flight.
 * @param airline - The new airline.
 */
void Flight::setAirline(const Airline &airline) {
    this->airline = airline;
}