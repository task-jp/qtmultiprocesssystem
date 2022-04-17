import QtQuick 2.15
import QtQuick.Layouts 1.15
import '../system'

AbstractMain {
    id: root

    ListModel {
        id: model
    }

    Component.onCompleted: {
        var applications = applicationManager.applications
        for (var i = 0; i < applications.length; i++) {
            var application = applications[i]
            if (!application.systemUI)
                model.append(application)
        }
    }

    GridView {
        anchors.fill: parent
        cellWidth: root.width / 3
        cellHeight: cellWidth

        model: model
        delegate: Button {
            width: root.width / 3
            height: width
            text: model.name
            font.pixelSize: height / 6
            onClicked: {
                var application = applicationManager.findByKey(model.key)
                applicationManager.exec(application)
            }
        }
    }
}
