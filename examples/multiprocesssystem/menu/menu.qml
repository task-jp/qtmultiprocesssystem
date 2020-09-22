import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

GridView {
    id: root
    anchors.fill: parent
    visible: enabled
    cellWidth: root.width / 3
    cellHeight: cellWidth

    model: applicationManager
    delegate: RoundButton {
        width: root.width / 3
        height: width
        text: model.name
        font.pixelSize: height / 10
        onClicked: {
            applicationManager.exec(model.key)
        }
    }
}
