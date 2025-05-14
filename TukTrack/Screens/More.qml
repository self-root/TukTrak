import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Page {
    ListView{
        anchors.fill: parent
        model: ListModel{
            ListElement{
                title: "Daily Deposits"
                menuIcon: ""
                menuId: 0
            }
            ListElement{
                title: "Maintenance record"
                menuIcon: ""
                menuId: 1
            }
            ListElement{
                title: "About"
                menuIcon: ""
                menuId: 2
            }
        }
        delegate: ItemDelegate{
            width: parent.width
            icon: menuIcon
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
