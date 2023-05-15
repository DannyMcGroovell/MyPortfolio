import QtQuick 2.0

Rectangle {
    id: root

    property string displayText: ""

    color: "royalblue"

    radius: 10

    border.color: "black"
    border.width: 2

    Text {
        id: _firstText
        anchors.centerIn: root

        text: root.displayText
        font {
            pointSize: Math.min(root.width, root.height) / 3
            bold: true
        }
    }
}
