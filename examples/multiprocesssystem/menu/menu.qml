import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtMultiProcessSystem.ApplicationManager 1.15
import '../common/'

AbstractMain {
    id: root

    GridView {
        anchors.fill: parent
        cellWidth: root.width / 3
        cellHeight: cellWidth

        model: ApplicationManagerModel {
            manager: applicationManager
        }

        delegate: Button {
            width: root.width / 3
            height: width
            text: model.i18nName
            font.pixelSize: height / 6
            onClicked: {
                console.debug('applicationManager.current.key', applicationManager.current.key)
                var application = applicationManager.findByKey(model.key)
                applicationManager.exec(application)
            }
            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                text: model.status
                font.pixelSize: parent.font.pixelSize
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Connections {
        target: applicationManager
        function onKilled(application) {
            if (applicationManager.current.id === application.id)
                applicationManager.exec(root.application)
        }
    }
}
