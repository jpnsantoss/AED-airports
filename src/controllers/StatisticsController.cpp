
#include <unordered_set>
#include <algorithm>
#include "StatisticsController.h"
#include "FlightController.h"

/**
 * @brief Constructs a StatisticsControler object and initializes the airportGraph using the dataset.
 */
StatisticsController::StatisticsController() {
    Dataset* dataset = Dataset::getInstance();
    airportGraph = dataset->getAirportGraph();
}

/**
 * @brief Gets the total number of airports in the dataset.
 * Complexity: O(1).
 * @return The total number of airports.
 */
size_t StatisticsController::getTotalAirports() {
    Dataset* dataset = Dataset::getInstance();
    return dataset->getAirports().size();
}

/**
 * @brief Gets the total number of flights in the dataset.
 * Complexity: O(1).
 * @return The total number of flights.
 */
size_t StatisticsController::getTotalFlights() {
    Dataset* dataset = Dataset::getInstance();
    return dataset->getFlights().size();
}

/**
 * @brief Gets the number of flights out of a specific airport and the associated airlines.
 * Complexity: O(n), where n is the number of flights from the airport.
 * @param identifier - the origin airport code.
 * @return The number of flights.
 */
size_t StatisticsController::numberOfFlightsOutAirport(string &identifier) {
    string upperId;
    for (char c: identifier) {
        upperId += (char)toupper(c);
    }

    Airport airport = FlightController::findAirport(upperId);

    Vertex<Airport>* airportVertex = airportGraph.findVertex(airport);

    if (airportVertex == nullptr) {
        return 0;
    }

    return airportVertex->getAdj().size();
}

/**
 * @brief Gets a set of airlines the operate flights out of a specific airport.
 * Complexity: O(n), where n is the number of flights in the dataset.
 * @param identifier - the origin airport code.
 * @return A set of airlines operating flights out of the specified airport.
 */
set<Airline> StatisticsController::setOfFlightsOutAirport(string &identifier) {
    set<Airline> airlines;
    string upperId;
    for (char c: identifier) {
        upperId += (char)toupper(c);
    }

    Airport airport = FlightController::findAirport(upperId);

    Vertex<Airport>* airportVertex = airportGraph.findVertex(airport);

    for(const Edge<Airport>& edge: airportVertex->getAdj()) {
        airlines.insert(edge.getAirline());
    }

    return airlines;
}

/**
 * @brief Gets the number of flights operated by a specific airline.
 * Complexity: O(n), where n is the number of flights in the dataset.
 * @param identifier - the airline code.
 * @return The number of flights operated by the specified airline.
 */
int StatisticsController::numberOfFlightsPerAirline(string &identifier) {
    int num = 0;
    string upperId;
    for (char c: identifier) {
        upperId += (char)toupper(c);
    }

    for (const Vertex<Airport>* vertex : airportGraph.getVertexSet()) {
        for (const Edge<Airport>& edge : vertex->getAdj()) {
            if (edge.getAirline().getCode() == upperId) {
                num++;
            }
        }
    }

    return num;
}


/**
 * @brief Gets the number of flights involving a specific city (as origin or destination).
 * Complexity: O(n), where n is the number of flights in the dataset.
 * @param city - the name of the city.
 * @return The number of flights involving the specified city.
 */
int StatisticsController::numberOfFlightsPerCity(string &city) {
    int num = 0;
    vector<Vertex<Airport>*> airports = airportGraph.getVertexSet();
    calculateIndegrees(airports);

    for (const Vertex<Airport>* vertex : airports) {
        if(vertex->getInfo().getCity() == city) {
            num += vertex->getAdj().size();
            num += vertex->getIndegree();
        }
    }

    return num;
}

/**
 * @brief Gets a set of the countries that a specific airport flies to.
 * Complexity: O(n), where n is the code of adjacent airports.
 * @param identifier - the origin airport code.
 * @return A set of countries that the specified airport flies to.
 */set<string> StatisticsController::countriesForThisAirport(string &identifier) {
    set<string> countries;
    string upperId;
    for (char c: identifier) {
        upperId += (char)toupper(c);
    }

    Airport airport = FlightController::findAirport(upperId);

    Vertex<Airport>* airportVertex = airportGraph.findVertex(airport);

    for(const Edge<Airport>& edge: airportVertex->getAdj()) {
        countries.insert(edge.getDest()->getInfo().getCountry());
    }

    return countries;
}

/**
 * @brief Gets the number of destination airports for a given airport.
 * Complexity: O(n), where n is the number of adjacent airports.
 * @param code - the origin airport code.
 * @return The number of destination airports.
 */
set<string> StatisticsController::countriesForThisCity(string &city) {
    set<string> countries;

    for (const Vertex<Airport>* vertex : airportGraph.getVertexSet()) {
        if(vertex->getInfo().getCity() == city) {
            for (const Edge<Airport> &edge: vertex->getAdj()) {
                countries.insert(edge.getDest()->getInfo().getCountry());
            }
        }
    }

    return countries;
}

/**
 * @brief Gets the number of destination airports for a given airport.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @return The number of destination airports.
 */
size_t StatisticsController::getNumberOfDestinationAirports(const string& code) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw runtime_error("Airport not found");
    }
    set<string> destinationAirports;
    for (const Edge<Airport>& edge : origin->getAdj()) {
        destinationAirports.insert(edge.getDest()->getInfo().getAirportCode());
    }
    return destinationAirports.size();
}

/**
 * @brief Gets the number of destination countries for a given airport.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @return The number of destination countries.
 */
size_t StatisticsController::getNumberOfDestinationCountries(const string& code) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw runtime_error("Airport not found");
    }
    set<string> destinationCountries;
    for (const Edge<Airport>& edge : origin->getAdj()) {
        const Airport& destinationAirport = edge.getDest()->getInfo();
        destinationCountries.insert(destinationAirport.getCountry());
    }
    return destinationCountries.size();
}

/**
 * @brief Gets the number of destination cities for a given airport.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @return The number of destination cities.
 */
size_t StatisticsController::getNumberOfDestinationCities(const string& code) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw runtime_error("Airport not found");
    }
    set<string> destinationCities;
    for (const Edge<Airport>& edge : origin->getAdj()) {
        const Airport& destinationAirport = edge.getDest()->getInfo();
        destinationCities.insert(destinationAirport.getCity());
    }
    return destinationCities.size();
}

/**
 * @brief Gets the number of reachable airports with a maximum number of stops.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @param maxStops - maximum number of stops.
 * @return The number of reachable airports with those stops.
 */
int StatisticsController::getNumberOfReachableAirportsWithMaxStops(const string& code, int maxStops) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw runtime_error("Airport not found");
    }
    queue<pair<Vertex<Airport>*, int>> queue;
    set<Vertex<Airport>*> visited;
    queue.emplace(origin, 0);
    visited.insert(origin);
    int reachableAirports = 0;
    while (!queue.empty()) {
        pair<Vertex<Airport>*, int> current = queue.front();
        queue.pop();
        if (current.second <= maxStops) {
            reachableAirports++;
            for (const Edge<Airport>& edge: current.first->getAdj()) {
                Vertex<Airport>* neighbor = edge.getDest();
                if (visited.find(neighbor) == visited.end()) {
                    queue.emplace(neighbor, current.second + 1);
                    visited.insert(neighbor);
                }
            }
        }
    }
    return reachableAirports-1;
}

/**
 * @brief Gets the number of reachable countries with a maximum number of stops.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @param maxStops - maximum number of stops.
 * @return The number of reachable countries with those stops.
 */
size_t StatisticsController::getNumberOfReachableCountriesWithMaxStops(const string& code, int maxStops) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw runtime_error("Airport not found");
    }
    queue<pair<Vertex<Airport>*, int>> queue;
    set<Vertex<Airport>*> visited;
    queue.emplace(origin, 0);
    visited.insert(origin);
    set<string> reachableCountries;
    while (!queue.empty()) {
        pair<Vertex<Airport>*, int> current = queue.front();
        queue.pop();
        if (current.second <= maxStops) {
            for (const Edge<Airport>& edge: current.first->getAdj()) {
                Vertex<Airport>* neighbor = edge.getDest();
                queue.emplace(neighbor, current.second + 1);
                visited.insert(neighbor);
                reachableCountries.insert(neighbor->getInfo().getCountry());
            }
        }
    }
    return reachableCountries.size();
}

/**
 * @brief Gets the number of reachable cities with a maximum number of stops.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param code - the origin airport code.
 * @param maxStops - maximum number of stops.
 * @return The number of reachable cities with those stops.
 */
size_t StatisticsController::getNumberOfReachableCitiesWithMaxStops(const string& code, int maxStops) const {
    Airport airport = FlightController::findAirport(code);
    Vertex<Airport>* origin = airportGraph.findVertex(airport);
    if (origin == nullptr) {
        throw runtime_error("Airport not found");
    }
    queue<pair<Vertex<Airport>*, int>> queue;
    set<Vertex<Airport>*> visited;
    queue.emplace(origin, 0);
    visited.insert(origin);
    set<string> reachableCities;
    while (!queue.empty()) {
        pair<Vertex<Airport>*, int> current = queue.front();
        queue.pop();
        if (current.second <= maxStops) {
            for (const Edge<Airport>& edge: current.first->getAdj()) {
                Vertex<Airport>* neighbor = edge.getDest();
                queue.emplace(neighbor, current.second + 1);
                visited.insert(neighbor);
                reachableCities.insert(neighbor->getInfo().getCity());
            }
        }
    }
    return reachableCities.size();
}

/**
 * @brief Depth-first search to find all paths starting from a vertex.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 */
void dfsAllPaths(Vertex<Airport>* v, vector<Airport>& path, int& maxStops, vector<pair<Airport, Airport>>& maxPaths) {
    v->setProcessing(true);
    path.push_back(v->getInfo());

    if (path.size() > maxStops) {
        maxStops = path.size();
        maxPaths.clear();
        maxPaths.push_back(make_pair(path.front(), path.back()));
    } else if (path.size() == maxStops) {
        maxPaths.push_back(make_pair(path.front(), path.back()));
    }

    for (const Edge<Airport>& e : v->getAdj()) {
        if (!e.getDest()->isProcessing()) {
            dfsAllPaths(e.getDest(), path, maxStops, maxPaths);
        }
    }

    v->setProcessing(false);
    path.pop_back();
}

/**
 * @brief Gets a vector containing pairs of airports representing maximum-stop trips.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @return Vector containing pairs of airports representing maximum-stops trips.
 */
vector<pair<Airport, Airport>> StatisticsController::getMaximumTrips() {
    vector<Airport> path;
    vector<pair<Airport, Airport>> maxPaths;
    int maxStops = 0;

    for (Vertex<Airport>* v : airportGraph.getVertexSet()) {
        if (!v->isProcessing()) {
            dfsAllPaths(v, path, maxStops, maxPaths);
        }
    }

    if (maxPaths.empty()) {
        throw runtime_error("No path found");
    }

    return maxPaths;
}

/**
 * @brief Compares two airports based on their total degrees.
 * Complexity: O(1)
 * @param a1 - Pointer to the first airport vertex.
 * @param a2 - Pointer to the second airport vertex.
 * @return True if the first airport has an higher total degree than the second; false otherwise.
 */
bool compareAirportsByTotalDegree(const Vertex<Airport>* a1, const Vertex<Airport>* a2) {
    unsigned long totalDegreeA1 = a1->getIndegree() + a1->getAdj().size();
    unsigned long totalDegreeA2 = a2->getIndegree() + a2->getAdj().size();
    return totalDegreeA1 > totalDegreeA2; // Higher degree comes first
}

/**
 * @brief Calculates and updates the indegrees for a given vector of airport vertices.
 * Complexity: O(V*log(V), where V is the number of vertices.
 * @param airports - vector containing airport vertices.
 */
void StatisticsController::calculateIndegrees(const vector<Vertex<Airport>*>& airports) {
    // Reset indegree for all vertices
    for (Vertex<Airport>* v : airports) {
        v->setIndegree(0);
    }

    for (Vertex<Airport>* v : airports) {
        for (const Edge<Airport>& edge : v->getAdj()) {
            Vertex<Airport>* dest = edge.getDest();
            dest->setIndegree(dest->getIndegree()+1);
        }
    }
}

/**
 * @brief Returns the top-k airports with the highest air traffic based on total indegree.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param k - number of airports to retrieve.
 * @return A vector of pairs representing the airports and their total degree, sorted in descending order by degree.
 */
vector<pair<Airport, unsigned long>> StatisticsController::topKAirTraffic(int k) {
    vector<Vertex<Airport>*> airports;
    vector<pair<Airport, unsigned long>> topAirports;

    for (Vertex<Airport>* vertex : airportGraph.getVertexSet()) {
        airports.push_back(vertex);
    }

    calculateIndegrees(airports);

    sort(airports.begin(), airports.end(), compareAirportsByTotalDegree);

    // Insert the top-k airports into the set
    for (int i = 0; i < k && i < airports.size(); i++) {
        Airport airport = airports[i]->getInfo();
        unsigned long totalDegree = airports[i]->getIndegree() + airports[i]->getAdj().size();
        topAirports.emplace_back(airport, totalDegree);
    }

    return topAirports;
}

/**
 * @brief Finds airports that are essential to the network's capability.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @return An unordered set of essential airports.
 */
unordered_set<Airport> StatisticsController::findEssentialAirports() {
    int index = 1;
    unordered_set<Airport> essentialAirports;
    stack<Vertex<Airport>*> vertexStack;
    for (Vertex<Airport>* vertex : airportGraph.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }

    for (Vertex<Airport>* vertex : airportGraph.getVertexSet()) {
        if (!vertex->isVisited()) {
            dfsForEssentialAirports(vertex, essentialAirports, vertexStack, index);
        }
    }

    return essentialAirports;
}

/**
 * @brief Performs DFS from a specific vertex to identify essential airports.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges.
 * @param vertex - the current vertex.
 * @param essentialAirports - set to store essential airports.
 * @param vertexStack - the stack that tracks the visited vertices during the execution of DFS.
 * @param index - the index to identify the vertices.
 */
void StatisticsController::dfsForEssentialAirports(Vertex<Airport>* vertex, unordered_set<Airport>& essentialAirports, stack<Vertex<Airport>*>& vertexStack, int& index) {
    vertex->setNum(index);
    vertex->setLow(index);
    vertex->setVisited(true);
    index++;

    vertexStack.push(vertex);
    vertex->setProcessing(true);

    int childCount = 0;
    bool isEssential = false;

    for (auto &edge : vertex->getAdj()) {
        Vertex<Airport>* adjacentVertex = edge.getDest();
        if (!adjacentVertex->isVisited()) {
            childCount++;
            dfsForEssentialAirports(adjacentVertex, essentialAirports, vertexStack, index);
            vertex->setLow(min(vertex->getLow(), adjacentVertex->getLow()));

            if (adjacentVertex->getLow() >= vertex->getNum()) {
                isEssential = true;
            }
        } else if (adjacentVertex->isProcessing()) {
            vertex->setLow(min(vertex->getLow(), adjacentVertex->getNum()));
        }
    }

    if ((vertex->getNum() == vertex->getLow() && childCount > 1) || (vertex->getNum() != vertex->getLow() && isEssential)) {
        essentialAirports.insert(vertex->getInfo());

        while (!vertexStack.empty()) {
            Vertex<Airport>* poppedVertex = vertexStack.top();
            vertexStack.pop();
            poppedVertex->setProcessing(false);

            if (poppedVertex == vertex) {
                break;
            }
        }
    }
}