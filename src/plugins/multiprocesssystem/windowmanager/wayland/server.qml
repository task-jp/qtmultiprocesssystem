import QtQuick 2.15
import QtWayland.Compositor 1.0
import QtMultiProcessSystem.Internal 1.0

WaylandCompositor {
    id: root
    WaylandOutput {
        sizeFollowsWindow: true
        window: Main {
            id: main
        }
    }
    Component {
        id: chromeComponent
        ShellSurfaceItem {
            id: item
            anchors.fill: parent
            visible: enabled
            onSurfaceDestroyed: destroy()
            onWidthChanged: handleResized()
            onHeightChanged: handleResized()
            function handleResized() {
                shellSurface.sendConfigure(Qt.size(width, height));
            }
        }
    }
    IviApplication {
        onIviSurfaceCreated: {
            console.debug('onIviSurfaceCreated', iviSurface.iviId)
            var parent = main.findParent(iviSurface.iviId)
            var item = chromeComponent.createObject(parent, { "shellSurface": iviSurface } );
            item.handleResized();
            root.apps[iviSurface.iviId] = item
        }
    }

    property var apps: ({})
    property int currentID: -1
    Connections {
        target: applicationManager
        function onActivated(id, name) {
            console.debug('onActivated', id, name)
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
        }
    }
}
