import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultiProcessSystem.Internal 1.0

Main {
    id: root

    Component {
        id: chromeComponent
        Loader {
            id: item
            anchors.fill: parent
            property int appId: 0
        }
    }

    property var apps: ({})
    property int currentID: -1
    Connections {
        target: applicationManager
        function onActivated(id, name) {
            if (id === root.currentID)
                return
            if (currentID in root.apps) {
                root.apps[currentID].enabled = false
            }
            currentID = id
            if (currentID in root.apps) {
                root.apps[currentID].enabled = true
                return
            }
            var url = 'qrc:/multiprocesssystem/%1/%1.qml'.arg(name)
            var parent = root.findParent(currentID, name)
            var item = chromeComponent.createObject(parent, {"source": url, "appId": id})
            if (root.isApp(currentID))
                root.apps[id] = item
        }
    }
}
