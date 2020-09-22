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
            var app = applicationManager.findByID(iviSurface.iviId)
            var parent = main.findParent(app)
            var item = chromeComponent.createObject(parent, { "shellSurface": iviSurface } );
            item.handleResized();
            root.apps[iviSurface.iviId] = item
        }
    }

    property var apps: ({})
    Connections {
        target: applicationManager
        function onActivated(app) {
            var current = applicationManager.current
            if (app.id === current.id)
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
        }
    }
}
