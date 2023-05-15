import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 400
    height: 400
    title: qsTr("15")

    GameBoard {
        anchors.fill: parent
    }
}
