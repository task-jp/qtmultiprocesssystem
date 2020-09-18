import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

RowLayout {
    id: root
    anchors.fill: parent

    ListModel {
        id: shortcut
        ListElement {
            appID: 100
            appName: 'menu'
            appTitle: 'Menu'
        }
        ListElement {
            appID: 101
            appName: 'navi'
            appTitle: 'Navi'
        }
    }

    Repeater {
        model: shortcut
        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: model.appTitle
            font.pixelSize: height / 4
            onClicked: {
                applicationManager.exec(model.appID, model.appName)
            }
        }
    }
    Label {
        Layout.fillWidth: true
        Layout.fillHeight: true
        rotation: 20
        text: 'Status'
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
