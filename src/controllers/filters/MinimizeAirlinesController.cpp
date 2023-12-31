#include "MinimizeAirlinesController.h"


vector<vector<Airport>> MinimizeAirlinesController::getShortestPathsBFS(const Airport &origin, const Airport &destination) {
    map<Vertex<Airport>*, vector<pair<Vertex<Airport>*, set<string>>>> prev;
    queue<Vertex<Airport>*> queue;
    vector<vector<Airport>> paths;
    vector<set<string>> airlinesUsedForPaths;

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
            set<string> airlinesUsed;
            buildPaths(originVertex, destinationVertex, prev, path, paths, airlinesUsed, airlinesUsedForPaths);
            continue;
        }

        for (const Edge<Airport> &edge : vertex->getAdj()) {
            Vertex<Airport>* neighbor = edge.getDest();
            if (!neighbor->isVisited()) {
                neighbor->setVisited(true);
                queue.push(neighbor);
                set<string> airlinesUsed = prev[vertex].empty() ? set<string>() : prev[vertex].back().second;
                airlinesUsed.insert(edge.getAirline().getName());
                prev[neighbor].emplace_back(vertex, airlinesUsed);
            }
        }
    }

    // Find the path with the least number of airlines
    size_t minAirlines = numeric_limits<size_t >::max();
    vector<Airport> bestPath;
    for (int i = 0; i < paths.size(); i++) {
        if (airlinesUsedForPaths[i].size() < minAirlines) {
            minAirlines = airlinesUsedForPaths[i].size();
            bestPath = paths[i];
        }
    }

    return vector<vector<Airport>>{bestPath}; // Return the path with the least number of airlines
}

void MinimizeAirlinesController::buildPaths(Vertex<Airport>* origin, Vertex<Airport>* destination, map<Vertex<Airport>*, vector<pair<Vertex<Airport>*, set<string>>>>& prev, vector<Airport>& path, vector<vector<Airport>>& paths, set<string>& airlinesUsed, vector<set<string>>& airlinesUsedForPaths) {
    path.push_back(destination->getInfo());
    if (destination == origin) {
        vector<Airport> newPath = path;
        reverse(newPath.begin(), newPath.end());
        paths.push_back(newPath);
        airlinesUsedForPaths.push_back(airlinesUsed);
    } else {
        for (auto &pair : prev[destination]) {
            Vertex<Airport>* vertex = pair.first;
            set<string> airlines = pair.second;
            buildPaths(origin, vertex, prev, path, paths, airlines, airlinesUsedForPaths);
        }
    }
    path.pop_back();
}