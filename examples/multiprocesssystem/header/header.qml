import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import '../system'

AbstractMain {
    id: root

    RowLayout {
        anchors.fill: parent

        ListModel {
            id: shortcut
            ListElement {
                key: 'menu'
                name: 'Menu'
            }
            ListElement {
                key: 'navi'
                name: 'Navi'
            }
        }

        Repeater {
            model: shortcut
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: model.name
                font.pixelSize: height / 4
                highlighted: applicationManager.current.key === model.key
                onClicked: {
                    applicationManager.exec(model.key)
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
}
