import QtQuick
import QtQuick.Controls
import SimulationsInterface

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600


    SimulationController {
        id: controller
    }

    background: Rectangle {
        color: '#393b3a'
        radius: 10;
        border.width: 4
        border.color: '#4bbace'


        Text {
            id: simulationsTitle
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 24
            text: "Loaded simulations"
            color: "white"
            font.pixelSize: 22
        }

        ListView {
            id: simulationList
            anchors.top: simulationsTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: addSimulation.top
            anchors.margins: 24
            anchors.bottomMargin: 16
            clip: true
            spacing: 8
            model: controller.simulations

            delegate: SimulationListItem {
                width: simulationList.width

                onRemoveRequested: function (simulationID){
                controller.removeSelectedSimulation(simulationID)
            }
        }

    }

    Text {
        anchors.centerIn: simulationList
        visible: simulationList.count === 0
        text: "No simulations loaded. Click below to add one."
        color: "#cccccc"
    }

    Button {

        background: Rectangle {
            color: addSimulation.hovered ? '#2a2c2c': '#181a1a'
            radius: 12
            border {width: 2;
                color:addSimulation.hovered ? '#57d2e7' : "#4bbace";}
            }
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            id: addSimulation
            width: addSimulation.hovered ? addSimulationButtonText.width + 14 : addSimulationButtonText.width + 12
            height: addSimulation.hovered ? addSimulationButtonText.height + 18 : addSimulationButtonText.height + 16
            Text {
                id:addSimulationButtonText
                text: "Add Simulation"
                color: "white"
                anchors.centerIn: parent}

                onClicked: controller.loadSimulation("Demo", 42.0)
                anchors.margins: 25
            }




        }

    }

