

#include "BestOptionController.h"
#include "FlightController.h"

/**
 * @brief Constructor for BestOptionController and initializes the airport graph using the dataset.
 * Complexity: O(1).
 */
BestOptionController::BestOptionController() {
    Dataset* dataset = Dataset::getInstance();
    airportGraph = dataset->getAirportGraph();
}

/**
 * @brief Splits a string into a vector of substrings using a delimiter.
 * Complexity: O(n), where n is the length of the input string.
 * @param str - the string to split.
 * @param delimiter - the character used to separate substrings.
 * @return A vector of the substrings.
 */
vector<string> splitString(const string &str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * @brief Gets the shortest paths between two airports using BFS.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges in the airport graph.
 * @param origin - the origin airport.
 * @param destination - the destination airport.
 * @return A vector of vectors, each representing each shortest paths.
 */
vector<vector<Airport>> BestOptionController::getShortestPathsBFS(const Airport &origin, const Airport &destination) {
    map<Vertex<Airport>*, vector<Vertex<Airport>*>> prev;
    queue<Vertex<Airport>*> queue;
    vector<vector<Airport>> paths;

    Vertex<Airport>* originVertex = airportGraph.findVertex(origin);
    Vertex<Airport>* destinationVertex = airportGraph.findVertex(destination);

    if (originVertex == nullptr || destinationVertex == nullptr) {
        throw runtime_error("Origin or destination airport not found");
    }

    for(Vertex<Airport>* vertex : airportGraph.getVertexSet()) {
        vertex->setVisited(false);
    }

    originVertex->setVisited(true);
    queue.push(originVertex);
    while (!queue.empty()) {
        Vertex<Airport>* vertex = queue.front();
        queue.pop();

        if (vertex->getInfo() == destination) {
            vector<Airport> path;
            buildPaths(originVertex, destinationVertex, prev, path, paths);
            return paths;
        }

        for (const Edge<Airport> &edge : vertex->getAdj()) {
            Vertex<Airport>* neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                neighbor->setVisited(true);
                queue.push(neighbor);
                prev[neighbor].push_back(vertex);
            }
        }
    }

    return paths; // Return an empty vector if no path is found
}

/**
 * @brief Builds paths from the BFS results.
 * Complexity: O(n), where n is the length of the path.
 * @param origin - the origin airport vertex.
 * @param destination - the destination airport vertex.
 * @param prev - mapping of predecessors for each vertex.
 * @param path - vector representing the current path.
 * @param paths - vector to store resulting paths
 */
void BestOptionController::buildPaths(Vertex<Airport>* origin, Vertex<Airport>* destination, map<Vertex<Airport>*, vector<Vertex<Airport>*>>& prev, vector<Airport>& path, vector<vector<Airport>>& paths) {
    path.push_back(destination->getInfo());
    if (destination == origin) {
        vector<Airport> newPath = path;
        reverse(newPath.begin(), newPath.end());
        paths.push_back(newPath);
    } else {
        for (Vertex<Airport>* vertex : prev[destination]) {
            buildPaths(origin, vertex, prev, path, paths);
        }
    }
    path.pop_back();
}

/**
 * @brief Finds the best flight paths between two locations.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges in the airport graph.
 * @param source - the origin airport.
 * @param destination - the destination airport.
 * @param res - the destination airport.
 */
void BestOptionController::findBestFlightPaths(const string &source, const string &destination, vector<vector<Airport>> &res) {
    try {
        Airport sourceAirport = FlightController::findAirport(source);
        Airport destinationAirport = FlightController::findAirport(destination);
        vector<vector<Airport>> paths = getShortestPathsBFS(sourceAirport, destinationAirport);
        res.insert(res.end(), paths.begin(), paths.end());
    } catch (runtime_error &e) {
        // Ignore exceptions for airports without a path
    }
}

/**
 * @brief Gets the best flight options based on origin and destination.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges in the airport graph.
 * @param sourceOption - the source option for identifying airports.
 * @param source - the origin airport code.
 * @param destinationOption - the destination option for identifying airports.
 * @param destination - the destination airport code.
 * @return A vector of vectors, each representing one of the best options.
 */
vector<vector<Airport>> BestOptionController::getBestFlightOption(FlightOption sourceOption, const string &source, FlightOption destinationOption, const string &destination) {
    vector<vector<Airport>> res;

    switch (sourceOption) {
        case FlightOption::ByAirportCode:
        {
            vector<Airport> sourceAirports = vector<Airport>{FlightController::findAirport(source)};
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{FlightController::findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        unordered_set<Airport> destinationAirports = FlightController::findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        unordered_set<Airport> destinationAirports = FlightController::findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        unordered_set<Airport> destinationAirports = FlightController::getNearestAirports(destinationLocation);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    default:
                        throw runtime_error("Invalid destination option");
                }
            }
            break;
        }
        case FlightOption::ByAirportName:
        {
            unordered_set<Airport> sourceAirports = FlightController::findAirportsByName(source);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{FlightController::findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        unordered_set<Airport> destinationAirports = FlightController::findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        unordered_set<Airport> destinationAirports = FlightController::findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));

                        unordered_set<Airport> destinationAirports = FlightController::getNearestAirports(destinationLocation);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    default:
                        throw runtime_error("Invalid destination option");
                }
            }
            break;
        }
        case FlightOption::ByCity:
        {
            unordered_set<Airport> sourceAirports = FlightController::findAirportsByCity(source);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{FlightController::findAirport(destination)};
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        unordered_set<Airport> destinationAirports = FlightController::findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        unordered_set<Airport> destinationAirports = FlightController::findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        unordered_set<Airport> destinationAirports = FlightController::getNearestAirports(destinationLocation);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    default:
                        throw runtime_error("Invalid destination option");
                }
            }
            break;
        }
        case FlightOption::ByLocation:
        {
            vector<string> sourceCoords = splitString(source, ',');
            Location sourceLocation(stod(sourceCoords[0]), stod(sourceCoords[1]));
            unordered_set<Airport> sourceAirports = FlightController::getNearestAirports(sourceLocation);
            for (const auto &sourceAirport : sourceAirports) {
                switch (destinationOption) {
                    case FlightOption::ByAirportCode:
                    {
                        vector<Airport> destinationAirports = vector<Airport>{FlightController::findAirport(destination)};
                        for (auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByAirportName:
                    {
                        unordered_set<Airport> destinationAirports = FlightController::findAirportsByName(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByCity:
                    {
                        unordered_set<Airport> destinationAirports = FlightController::findAirportsByCity(destination);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    case FlightOption::ByLocation:
                    {
                        vector<string> destCoords = splitString(destination, ',');
                        Location destinationLocation(stod(destCoords[0]), stod(destCoords[1]));
                        unordered_set<Airport> destinationAirports = FlightController::getNearestAirports(destinationLocation);
                        for (const auto &destinationAirport : destinationAirports) {
                            findBestFlightPaths(sourceAirport.getAirportCode(), destinationAirport.getAirportCode(), res);
                        }
                        break;
                    }
                    default:
                        throw runtime_error("Invalid destination option");
                }
            }
            break;
        }
        default:
            throw runtime_error("Invalid source option");
    }

    return res;
}