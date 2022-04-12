import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultiProcessSystem.Internal 1.0

ApplicationWindow {
    id: root
    visible: true
    color: 'transparent'
    Main {
        id: main
    }
    Binding {
        target: main
        property: 'anchors.fill'
        value: root
        when: main instanceof Item
    }
}
