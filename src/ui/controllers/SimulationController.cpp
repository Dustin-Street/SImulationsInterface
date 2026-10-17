#include "SimulationController.h"

SimulationController::SimulationController(QObject *parent)
    : QObject(parent)
{
}

QVariantList SimulationController::simulations() const
{

    QVariantList simulations;
    for (const auto &entry : getSimulationList())
    {
        const int simulationID = entry.second.getSimulationID();
        QString simulationName = QString::fromStdString(entry.second.getSimulationName());

        QVariantMap simulation;
        simulation.insert(QStringLiteral("simulationID"), simulationID);
        simulation.insert(QStringLiteral("simulationName"), simulationName);

        simulations.append(simulation);
    }
    return simulations;

}

bool SimulationController::loadSimulation(const QString &name, double simulationData)
{
    const bool loaded = addSimulation(name.toStdString(), simulationData);
    if (loaded)
    {
        emit simulationsChanged();
    }
    return loaded;
}

bool SimulationController::removeSelectedSimulation(const int simulationID)
{

    const bool removed = removeSimulation(simulationID);
    if (removed)
    {
        emit simulationsChanged();
    }
    return removed;
}

std::map<int, Simulation> SimulationController::populateSimulationList()
{
    return getSimulationList();
}