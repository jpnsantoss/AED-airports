
#include "AirlineFilterController.h"

/**
 * @brief Filters the airports based on the provided list of airlines and creates a graph with only the airports serviced by the specified airlines.
 * Complexity: O(V+E), where V is the number of vertices and E the number of edges in the original graph.
 * @param airlines - a vector of airline names to filter the airports.
 */
AirlineFilterController::AirlineFilterController(const vector<string>& airlines) {
    Dataset* dataset = Dataset::getInstance();
    Graph<Airport> originalGraph = dataset->getAirportGraph();

    // Iterate over all the vertices in the original graph
    for (const auto& vertex : originalGraph.getVertexSet()) {
        // Check if the airport is serviced by any of the airlines in the list
        for (const auto& edge : vertex->getAdj()) {
            for (const auto& airline : airlines) {
                if (edge.getAirline().getName() == airline) {
                    // If the airport is serviced by the airline, add it to the new graph
                    airportGraph.addVertex(vertex->getInfo());
                    break;
                }
            }
        }
    }

    // Iterate over all the edges in the original graph
    for (const auto& vertex : originalGraph.getVertexSet()) {
        for (const auto& edge : vertex->getAdj()) {
            // If both the source and destination airports are in the new graph, add the edge to the new graph
            if (airportGraph.findVertex(edge.getDest()->getInfo()) != nullptr) {
                airportGraph.addEdge(vertex->getInfo(), edge.getDest()->getInfo(), edge.getDistance(), edge.getAirline());
            }
        }
    }
}