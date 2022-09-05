import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import '../common/'

AbstractMain {
    id: root

    property bool northUp: false
    property var koenjiDepot: QtPositioning.coordinate(35.7061748, 139.650941)
    property var currentCoordinate: root.koenjiDepot
    property real direction: 0.25

    Binding on currentCoordinate {
        when: positionSource.valid && positionSource.position.latitudeValid && positionSource.position.longitudeValid
        value: positionSource.position.coordinate
    }
    Binding on direction {
        when: positionSource.valid && positionSource.position.directionValid
        value: positionSource.position.direction
    }

    StateGroup {
        states: [
            State {
                when: root.northUp
                PropertyChanges {
                    target: map
                    tilt: 60
                    fieldOfView: 120
                    bearing: root.direction * 360
                    zoomLevel: 19
                    center: root.currentCoordinate
                }
                PropertyChanges {
                    target: routeView
                    autoFitViewport: false
                }
                PropertyChanges {
                    target: car
                    source: 'car-rear.svg'
                }
            }
        ]

        transitions: [
            Transition {
                NumberAnimation {
                    properties: 'tilt, fieldOfView, zoomLevel'
                    duration: 1500
                    easing.type: Easing.InOutExpo
                }
                RotationAnimation {
                    properties: 'bearing'
                    duration: 1500
                    easing.type: Easing.InOutExpo
                }
                CoordinateAnimation {
                    properties: 'center'
                    duration: 1500
                    easing.type: Easing.InOutExpo
                }
            }
        ]
    }

    PositionSource {
        id: positionSource
        active: true
    }

    Map {
        id: map
        anchors.fill: parent

        plugin: Plugin {
            id: mapPlugin
            name: "mapboxgl"
        }

        zoomLevel: 19

        RouteModel {
            id: routeModel
            plugin: Plugin {
                id: routePlugin
                name: "osm"
            }
            query: RouteQuery {
                id: routeQuery
            }
        }

        MapItemView {
            id: routeView
            model: routeModel
            delegate: routeDelegate
        }

        MapImageItem {
            id: car
            coordinate: root.koenjiDepot
            source: 'car.svg'
            align: Item.Center
        }

        MapImageItem {
            coordinate: QtPositioning.coordinate(35.6900898, 139.6985957)
            source: 'map-pin.svg'
            align: Item.Bottom
        }

        Component {
            id: routeDelegate

            MapRoute {
                route: model.routeData
                line.color: "green"
                line.width: 25
                smooth: true
                opacity: 0.5
            }
        }

        Component.onCompleted: {
            routeQuery.clearWaypoints()

            routeQuery.addWaypoint(root.koenjiDepot)
            routeQuery.addWaypoint(QtPositioning.coordinate(35.6900898, 139.6985957))
            routeQuery.travelModes = RouteQuery.CarTravel
            routeQuery.routeOptimizations = RouteQuery.FastestRoute
            routeModel.update();
            map.fitViewportToMapItems()
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 200
        height: 200
        color: 'red'
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.northUp = !root.northUp
//                if (root.northUp) {
////                    map.pan()
//                } else {
//                    map.fitViewportToMapItems()
//                }
            }
        }
    }
}
