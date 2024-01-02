
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
    Airline(const string &code);
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

    // Operators
    bool operator<(const Airline& other) const {
        return this->code < other.code;
    }
    bool operator==(const Airline& other) const {
        return code == other.code;
    }
};

template <>
struct std::hash<Airline> {
    size_t operator()(const Airline& airline) const {
        return hash<string>()(airline.getCode());
    }
};

#endif //PROJECT_AED_AIRPORTS_AIRLINE_H