import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: root
    width: layout.width * layout.scale
    height: layout.height * layout.scale
    visible: true
    title: '%1 - %2'.arg(Qt.application.name).arg(applicationManager.current.name)

    Skin {
        anchors.centerIn: layout
        anchors.horizontalCenterOffset: -layout.width * 0.047
        anchors.verticalCenterOffset: layout.height * 0.067
        scale: layout.scale * 4.4
    }

    ColumnLayout {
        id: layout
        width: 1080
        height: 1920
        scale: 0.3
        anchors.centerIn: parent
        spacing: 0

        Item {
            id: header
            Layout.fillWidth: true
            Layout.preferredHeight: 200
            clip: true
        }

        Item {
            id: app
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
        }

        Item {
            id: footer
            Layout.fillWidth: true
            Layout.preferredHeight: 200
            clip: true
        }

        Component.onCompleted: {
            applicationManager.init()
        }
    }

    function findParent(application) {
        switch (application.area) {
        case 'header':
            return header
        case 'footer':
            return footer
        default:
            break
        }
        return app
    }
}
