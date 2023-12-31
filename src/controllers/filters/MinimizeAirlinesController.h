
#ifndef PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESCONTROLLER_H
#define PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESCONTROLLER_H

#include "controllers/BestOptionController.h"
#include <vector>
#include <stdexcept>
#include <set>

class MinimizeAirlinesController : public BestOptionController {
public:
    vector<vector<Airport>> getShortestPathsBFS(const Airport &origin, const Airport &destination) override;

    void buildPaths(Vertex<Airport> *origin, Vertex<Airport> *destination,
                    map<Vertex<Airport> *, vector<pair<Vertex<Airport> *, set<string>>>> &prev, vector<Airport> &path,
                    vector<vector<Airport>> &paths, set<string> &airlinesUsed,
                    vector<set<string>> &airlinesUsedForPaths);
};

#endif //PROJECT_AED_AIRPORTS_MINIMIZEAIRLINESCONTROLLER_H