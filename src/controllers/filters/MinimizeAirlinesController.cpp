#include "MinimizeAirlinesController.h"
#include <stdexcept>
#include <set>

/**
 * @brief Gets teh shortest paths between two airports using BFS.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges in the airport graph.
 * @param origin - the origin airport code;
 * @param destination - the destination airport code.
 * @return A vector of vectors, each representing one of the shortest path.
 */
vector<vector<Airport>> MinimizeAirlinesController::getShortestPathsBFS(const Airport &origin, const Airport &destination) {
    map<Vertex<Airport>*, vector<Vertex<Airport>*>> prev;
    map<Vertex<Airport>*, set<string>> airlinesUsed;
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
                // Add the airline of the current edge to the set of airlines used to reach the neighbor
                airlinesUsed[neighbor] = airlinesUsed[vertex];
                airlinesUsed[neighbor].insert(edge.getAirline().getName());

                // Only visit the neighbor if it leads to a path with less or equal number of different airlines
                if (neighbor->isVisited() && airlinesUsed[neighbor].size() > airlinesUsed[vertex].size()) {
                    continue;
                }

                neighbor->setVisited(true);
                queue.push(neighbor);
                prev[neighbor].push_back(vertex);
            }
        }
    }

    return paths; // Return an empty vector if no path is found
}