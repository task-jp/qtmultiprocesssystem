import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtMultiProcessSystem 1.15 as MPS
import QtMultiProcessSystem.ApplicationManager 1.15
import '../common/'

AbstractMain {
    id: root

    ListView {
        anchors.fill: parent

        model: ApplicationManagerModel {
            manager: applicationManager
            excludeAttributes: MPS.Application.SystemUI
        }

        delegate: RowLayout {
            width: ListView.view.width
            height: width / 7
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredHeight: 2
                    text: model.i18nName
                    font.pixelSize: 64
                }
                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredHeight: 1
                    text: model.status
                    font.pixelSize: 32
                }
            }
            ProcessButton {
                Layout.fillHeight: true
                Layout.fillWidth: false
                Layout.preferredWidth: height
                status: model.status
                onLaunch: applicationManager.exec(applicationManager.findByKey(model.key))
                onKill: applicationManager.kill(applicationManager.findByKey(model.key))
            }
        }
    }
}
