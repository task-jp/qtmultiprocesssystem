import QtQuick 2.15
import QtQuick.Window 2.15
import QtMultiProcessSystem.Internal 1.0

Window {
    id: root
    visible: true
    color: 'transparent'

    Binding on width {
        when: main.implicitWidth > 0
        value: main.implicitWidth
    }
    Binding on height {
        when: main.implicitHeight > 0
        value: main.implicitHeight
    }

    Main {
        id: main
        anchors.fill: parent
        application: applicationManager.findByKey(Qt.application.name)
        enabled: application.area || applicationManager.current.key === application.key
        Component.onCompleted: {
            var args = []
            for (var i = 2; i < Qt.application.arguments.length; i++) {
                args.push(Qt.application.arguments[i])
            }
            if (typeof main.activated === 'function')
                main.activated(args)
        }
    }
}
