import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

Window {
    id: root
    width: layout.width * layout.scale
    height: layout.height * layout.scale
    visible: true
    title: '%1 - %2'.arg(Qt.application.name).arg(applicationManager.current.i18nName)

    Skin {
        anchors.centerIn: layout
        anchors.horizontalCenterOffset: -layout.width * 0.065
        anchors.verticalCenterOffset: layout.height * 0.089
        scale: layout.scale * 4.4
        visible: Qt.platform.pluginName !== 'eglfs'
    }

    ColumnLayout {
        id: layout
        width: 1080
        height: 1920
        scale: Math.min(Screen.width / layout.width, Screen.height / layout.height) * (Qt.platform.pluginName === 'eglfs' ? 1 : 0.8)
        antialiasing: true
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
