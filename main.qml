import QtQuick 2.0
import VtkQuick 1.0

Rectangle {
    id: root

    width: 800
    height: 600
    color: "yellow"

    Rectangle {
        id : vtkRenderWindowContainer
        anchors.fill: parent
        anchors.margins: 20
        border.width: 4
        border.color: "black"
        color: "blue"

        VtkRenderWindow {
            id: vtkRenderWindow
            anchors.fill: parent
        }

        MouseArea {
            id: mousearea
            anchors.fill: parent
        }
    }

}
