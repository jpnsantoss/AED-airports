//
// Created by jpsantos on 16-12-2023.
//

#include "Flight.h"

// Constructor
Flight::Flight(const Airport &source, const Airport &target, const Airline &airline)
        : source(source), target(target), airline(airline), distance(source.getLocation().calculateDistanceTo(target.getLocation())) {}

// Getters
Airport Flight::getSource() const {
    return source;
}

Airport Flight::getTarget() const {
    return target;
}

Airline Flight::getAirline() const {
    return airline;
}

double Flight::getDistance() const {
    return distance;
}

// Setters
void Flight::setSource(const Airport &source) {
    this->source = source;
    this->distance = this->source.getLocation().calculateDistanceTo(this->target.getLocation());
}

void Flight::setTarget(const Airport &target) {
    this->target = target;
    this->distance = this->source.getLocation().calculateDistanceTo(this->target.getLocation());
}

void Flight::setAirline(const Airline &airline) {
    this->airline = airline;
}