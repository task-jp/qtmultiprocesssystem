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
                if (width < 0 || height < 0)
                    return
                shellSurface.sendConfigure(Qt.size(width, height), WlShellSurface.NoneEdge);
            }
        }
    }
    WlShell {
        onWlShellSurfaceCreated: {
            shellSurface.titleChanged.connect(function() {
                var key = shellSurface.title
                console.debug(key)
                if (key === Qt.application.name) // QPA changes title once with its name
                    return
                var app = applicationManager.findByKey(key)
                var parent = main.findParent(app)
                var item = chromeComponent.createObject(parent, { "shellSurface": shellSurface } )
                item.handleResized()
                root.apps[key] = item
            })
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
