import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Page {
    ListView{
        anchors.fill: parent
        model: ListModel{
            ListElement{
                title: "Daily Deposits"
                menuIcon: "qrc:/images/images/deposit.png"
                menuId: 0
            }
            ListElement{
                title: "Maintenance record"
                menuIcon: "qrc:/images/images/data-visualization.png"
                menuId: 1
            }
            ListElement{
                title: "About"
                menuIcon: "qrc:/images/images/info-button.png"
                menuId: 2
            }
        }
        delegate: ItemDelegate{
            width: parent.width
            icon.source: menuIcon
            //icon.height: 32
            text: title
            onClicked: {
                if (menuId === 0) {
                    depositDateList.loadData()
                    uiController.goDailyDeposits()
                }
                else if (menuId === 1) {
                    uiController.goMaintenanceRecord()
                }
                else if (menuId === 2) {
                    uiController.goAbout()
                }
            }
        }
    }

}
