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
    property int currentID: -1
    Connections {
        target: applicationManager
        function onActivated(id, name) {
            if (id === root.currentID)
                return
            if (root.isApp(id)) {
                if (root.currentID in root.apps) {
                    root.apps[root.currentID].enabled = false
                }
                root.currentID = id
                if (root.currentID in root.apps) {
                    root.apps[root.currentID].enabled = true
                    return
                }
            }
            var url = 'qrc:/multiprocesssystem/%1/%1.qml'.arg(name)
            var parent = root.findParent(id, name)
            var item = chromeComponent.createObject(parent, {"source": url})
            if (root.isApp(id)) {
                root.apps[id] = item
                item.item.enabled = true
            }
        }
    }
}
