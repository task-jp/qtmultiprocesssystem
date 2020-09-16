import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

Map {
    id: root
    anchors.fill: parent
    visible: enabled

    plugin: Plugin {
        id: mapPlugin
        name: "osm"
    }

    center: QtPositioning.coordinate(59.91, 10.75) // Oslo
    zoomLevel: 19
}
