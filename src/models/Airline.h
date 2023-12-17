//
// Created by jpsantos on 16-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_AIRLINE_H
#define PROJECT_AED_AIRPORTS_AIRLINE_H

#include <string>
using namespace std;
class Airline {
private:
    string airlineCode;
    string airlineName;

public:
    // Constructor
    Airline(const string &airlineCode, const string &airlineName);

    // Getters
    string getAirlineCode() const;
    string getAirlineName() const;

    // Setters
    void setAirlineCode(const string &airlineCode);
    void setAirlineName(const string &airlineName);
};

#endif //PROJECT_AED_AIRPORTS_AIRLINE_H