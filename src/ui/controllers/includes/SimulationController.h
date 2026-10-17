#ifndef SIMULATION_CONTROLLER_H
#define SIMULATION_CONTROLLER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QStringLiteral>

#include <map>
#include <string>
#include "Simulation.h"
#include "simulationRegistery.h"

class SimulationController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList simulations READ simulations NOTIFY simulationsChanged)

public:
    explicit SimulationController(QObject *parent = nullptr);

    QVariantList simulations() const;

public slots:
    bool loadSimulation(const QString &name, double simulationData);
    bool removeSelectedSimulation(const int simulationID);
    std::map<int, Simulation> populateSimulationList();

signals:
    void simulationsChanged();
};

#endif