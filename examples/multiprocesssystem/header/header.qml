import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtMultiProcessSystem.ApplicationManager 1.15
import '../common/'

AbstractMain {
    id: root

    RowLayout {
        anchors.fill: parent

        Repeater {
            model: ApplicationManagerModel {
                manager: applicationManager
                filters: ['menu', 'navi', 'music']
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: model.i18nName
                font.pixelSize: height / 4
                highlighted: applicationManager.current.key === model.key
                onClicked: {
                    var application = applicationManager.findByKey(model.key)
                    console.debug(model.key, applicationManager.current.key)
                    applicationManager.exec(application)
                }
            }
        }
        Text {
            Layout.fillWidth: true
            Layout.fillHeight: true
            rotation: 20
            text: 'Status'
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
