import QtQuick 2.15
import QtQuick.Controls 2.15
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
        function onActivated(app) {
            var current = applicationManager.current
            if (app === current)
                return
            if (!app.area) {
                if (current.id in root.apps) {
                    root.apps[current.id].enabled = false
                }
                applicationManager.current = app
                if (app.id in root.apps) {
                    root.apps[app.id].enabled = true
                    return
                }
            }
            var url = 'qrc:/multiprocesssystem/%1/%1.qml'.arg(app.key)
            var parent = root.findParent(app)
            var item = chromeComponent.createObject(parent, {"source": url})
            if (!app.area) {
                root.apps[app.id] = item
                item.item.enabled = true
            }
        }
    }
}
