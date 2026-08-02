import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Minimal Qt Android")

    Rectangle {
        anchors.fill: parent
        color: "#1e1e2e"

        Text {
            anchors.centerIn: parent
            text: "Hello from Qt C++ Android!"
            color: "#cdd6f4"
            font.pixelSize: 24
        }
    }
}
