#ifndef SIMULATION_DATABASE_H
#define SIMULATION_DATABASE_H

#include <string>
#include <vector>

struct SimulationRecord
{
    int simulationID;
    std::string simulationName;
    std::string simulationLogic;
};

bool initializeSimulationDatabase(const std::string &databasePath);
bool loadSimulationsFromDatabase(
    const std::string &databasePath,
    std::vector<SimulationRecord> &simulations);

#endif
