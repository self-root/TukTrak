import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import TukTrack 1.0
import "Screens"

ApplicationWindow {
    id: appWindow
    property int currentPage: 0
    width: 400
    height: 800
    visible: true
    title: qsTr("TulTrack")
    Material.accent: "#fca311"
    Material.background: "white"

    Connections{
        target: uiController
        function onGoDriverDetails() {
            stackView.push("qrc:/qt/qml/TukTrack/Screens/DriverDetail.qml")
        }

        function onGoTukDetail() {
            stackView.push("qrc:/qt/qml/TukTrack/Screens/TukTukDetail.qml")
        }

        function onGoDailyDeposits() {
            stackView.push("qrc:/qt/qml/TukTrack/Screens/DailyDeposits.qml")
        }

        function onGoMaintenanceRecord() {
            stackView.push("qrc:/qt/qml/TukTrack/Screens/MaintenanceRecord.qml")
        }

        function onGoAbout() {
            stackView.push("qrc:/qt/qml/TukTrack/Screens/About.qml")
        }

        function onGoBack() {
            stackView.pop()
        }
    }

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: mainContent
        focus: true
        Keys.onReleased: (event) => {
            if (event.key === Qt.Key_Back) {
                if (stackView.depth > 1) {
                    //closeEvent.accepted = true
                    stackView.pop()
                    event.accepted = true
                } else if (appWindow.currentPage >= 1) {
                    appWindow.currentPage = 0
                    event.accepted = true
                } else {
                    event.accepted = false
                }

            }
        }
    }

    Page{
        id: mainContent
        SwipeView{
            id: view
            anchors.fill: parent
            currentIndex: currentPage
            onCurrentIndexChanged: {
                currentPage = currentIndex
                console.log("Current page: " + currentPage)
                if (currentPage == 0) {
                    home.loadRevenueBarSeries()
                }
            }
            Home{
                id: home

            }

            TukTuk{

            }

            Drivers{

            }

            More{

            }
        }

        footer: TabBar{
            id: tabBar
            width: parent.width
            currentIndex: currentPage
            onCurrentIndexChanged: currentPage = currentIndex
            TabButton{
                contentItem: ColumnLayout{
                    anchors.centerIn: parent
                    Label{
                        text: "\uf015"
                        font.family: Style.webFont
                        font.pointSize: 16
                        //horizontalAlignment: Qt.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter
                        color: tabBar.currentIndex === 0? "#fca311" : "black"
                    }

                    Label{
                        text: "Accueil"
                        Layout.alignment: Qt.AlignHCenter
                        color: tabBar.currentIndex === 0? "#fca311" : "black"
                        font.pointSize: 16
                    }
                }
            }

            TabButton{
                contentItem: ColumnLayout{
                    anchors.centerIn: parent
                    Label{
                        text: "\uf1ba"
                        font.family: Style.webFont
                        font.pointSize: 16
                        //horizontalAlignment: Qt.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter
                        color: tabBar.currentIndex === 1? "#fca311" : "black"
                    }

                    Label{
                        text: "Tuc tuc"
                        Layout.alignment: Qt.AlignHCenter
                        color: tabBar.currentIndex === 1? "#fca311" : "black"
                        font.pointSize: 14
                    }
                }
            }

            TabButton{
                contentItem: ColumnLayout{
                    anchors.centerIn: parent
                    Label{
                        text: "\uf508"
                        font.family: Style.webFont
                        font.pointSize: 16
                        //horizontalAlignment: Qt.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter
                        color: tabBar.currentIndex === 2? "#fca311" : "black"
                    }

                    Label{
                        text: "Chauffeurs"
                        Layout.alignment: Qt.AlignHCenter
                        color: tabBar.currentIndex === 2? "#fca311" : "black"
                        font.pointSize: 14
                    }
                }
            }

            TabButton{
                contentItem: ColumnLayout{
                    anchors.centerIn: parent
                    Label{
                        text: "\uf141"
                        font.family: Style.webFont
                        font.pointSize: 16
                        //horizontalAlignment: Qt.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter
                        color: tabBar.currentIndex === 3? "#fca311" : "black"
                    }

                    Label{
                        text: "Plus"
                        Layout.alignment: Qt.AlignHCenter
                        color: tabBar.currentIndex === 3? "#fca311" : "black"
                        font.pointSize: 14
                    }
                }
            }
        }
    }



    /*StackView{
        id: stackView
        anchors.fill: parent
        initialItem: "qrc:/qt/qml/TukTrack/Screens/Home.qml"
    }*/
    /*onClosing: (closeEvent) => {
        if (Qt.platform.os === "android") {
            console.log("Close event: " + stackView.depth)
            closeEvent.acceped = false
            if (stackView.depth != 1) {
                //closeEvent.accepted = true
                stackView.pop()
            }
            else {
                stackView.pop()
            }
        }

        else{
            closeEvent.accepted = true
        }

    }*/

}
