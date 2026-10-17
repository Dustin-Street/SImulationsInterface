import QtQuick
import QtQuick.Controls

Rectangle {
    id:row

    required property string simulationName
    required property int simulationID

    signal removeRequested(int simulationID)

    height: 44
    radius: 6
    color: '#2a2c2b'
    border {
        color: "black"
        width: 2
    }

    Text {
        anchors.fill: parent
        anchors.leftMargin: 12
        verticalAlignment: Text.AlignVCenter
        text: simulationName
        color: "white"
    }

    Button {
        background: Rectangle {
            color: removeSimulation.hovered ? '#2a2c2c': '#181a1a'
            radius: 12
            border {width: 2;
                color:removeSimulation.hovered ? '#57d2e7' : "#4bbace";}
            }
            anchors.right: viewSimulation.left
            anchors.verticalCenter : parent.verticalCenter
            anchors.margins : 12
            width: removeSimulation.hovered ? removeSimulationButtonText.width + 16 : removeSimulationButtonText.width + 14
            height: removeSimulation.hovered ? removeSimulationButtonText.height + 18 : removeSimulationButtonText.height + 16
            id: removeSimulation
            Text {
                id:removeSimulationButtonText
                text: "Remove"
                color: "white"
                anchors.centerIn: parent}
                onClicked: row.removeRequested(simulationID)
            }

            Button {
                background: Rectangle {
                    color: viewSimulation.hovered ? '#2a2c2c': '#181a1a'
                    radius: 12
                    border {width: 2;
                        color:viewSimulation.hovered ? '#57d2e7' : "#4bbace";}
                    }
                    anchors.right: parent.right
                    anchors.verticalCenter : parent.verticalCenter
                    anchors.margins : 24
                    width: viewSimulation.hovered ? buttonText.width + 16 : buttonText.width + 14
                    height: viewSimulation.hovered ? buttonText.height + 18 : buttonText.height + 16
                    id: viewSimulation
                    Text {
                        id:buttonText
                        text: "Open"
                        color: "white"
                        anchors.centerIn: parent}
                    }
                }