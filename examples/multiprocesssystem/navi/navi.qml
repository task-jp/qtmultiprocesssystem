import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15
import '../common/'

AbstractMain {
    id: root

    property bool followme: positionSource.valid
    PositionSource{
        id: positionSource
        active: followme

        onPositionChanged: {
            map.center = positionSource.position.coordinate
        }
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
            onStatusChanged: {
                if (status == RouteModel.Ready) {
                } else if (status == RouteModel.Error) {
                }
            }
        }

        MapItemView {
            id: routeView
            model: routeModel
            delegate: routeDelegate
            autoFitViewport: true
        }

        MapImageItem {
            coordinate: QtPositioning.coordinate(35.7061748, 139.650941)
            source: 'car-rear.svg'
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
                line.width: 15
                smooth: true
                opacity: 0.8
            }
        }

        Component.onCompleted: {
            routeQuery.clearWaypoints()

            var koenjiDepot = QtPositioning.coordinate(35.7061748, 139.650941)
            routeQuery.addWaypoint(koenjiDepot)
            routeQuery.addWaypoint(QtPositioning.coordinate(35.6900898, 139.6985957))
            routeQuery.travelModes = RouteQuery.CarTravel
            routeQuery.routeOptimizations = RouteQuery.FastestRoute
            routeModel.update();
            map.fitViewportToMapItems()
//            map.setBearing(50, QtPositioning.coordinate(35.6528839, 139.7798186))
        }
    }
}
