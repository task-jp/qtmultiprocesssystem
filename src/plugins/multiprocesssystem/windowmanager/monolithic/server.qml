import QtQuick 2.15
import QtMultiProcessSystem.Internal 1.0

Main {
    id: root

    Component {
        id: chromeComponent
        Loader {
            anchors.fill: parent
        }
    }

    property var apps: ({})
    Connections {
        target: applicationManager
        function onActivated(application) {
            var current = applicationManager.current
            if (application === current)
                return
            if (!application.area) {
                if (current.id in root.apps) {
                    root.apps[current.id].enabled = false
                }
                applicationManager.current = application
                if (application.id in root.apps) {
                    root.apps[application.id].enabled = true
                    return
                }
            }
            var url = 'qrc:/multiprocesssystem/%1/%1.qml'.arg(application.key)
            var parent = root.findParent(application)
            var item = chromeComponent.createObject(parent, {"source": url})
            if (!application.area) {
                root.apps[application.id] = item
                item.item.enabled = true
            }
        }
    }
}
