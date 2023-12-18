//
// Created by jpsantos on 16-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_AIRLINE_H
#define PROJECT_AED_AIRPORTS_AIRLINE_H

#include <string>
using namespace std;
class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;

public:
    // Constructor
    Airline(const string &code, const string &name, const string &callsign, const string &country);

    // Getters
    string getCode() const;
    string getName() const;
    string getCallsign() const;
    string getCountry() const;

    // Setters
    void setCode(const string &code);
    void setName(const string &name);
    void setCallsign(const string &callsign);
    void setCountry(const string &country);
};

#endif //PROJECT_AED_AIRPORTS_AIRLINE_H