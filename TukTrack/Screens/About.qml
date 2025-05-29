import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts
import TukTrack


Page {
    id: root
    Material.background: "#ffffff"
    header: ToolBar{
        Material.primary:  "white"
        Material.elevation: 4
        RowLayout{
            anchors.fill: parent
            spacing: 10

            ToolButton{
                Layout.leftMargin: 6
                text: "\uf177"
                font.family: Style.webFont
                font.bold: true
                font.pointSize: 14
                Material.foreground: "#023047"
                onClicked: {
                    uiController.goBack()
                }
            }

            Label{
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignLeft
                Layout.fillWidth: true
                text: "About"
                font.bold: true
                font.pointSize: 16
                leftPadding: 8
                color: "#023047"
            }
        }
    }

    Rectangle{
        id: c_rect
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 6
        ScrollView {
            anchors.fill: parent
            anchors.topMargin: 6

                ColumnLayout {
                    spacing: 20
                    width: c_rect.width
                    anchors.margins: 20
                    //anchors.horizontalCenter: parent.horizontalCenter
                    //anchors.fill: parent
                    Image {
                        source: "qrc:/images/images/tuk.png"
                        Layout.preferredHeight: 100
                        //height: 100
                        //anchors.horizontalCenter: parent.horizontalCenter
                        Layout.alignment: Qt.AlignHCenter
                        fillMode: Image.PreserveAspectFit
                    }

                    Text {
                        text: "TukTrack v1.1.1"
                        font.pixelSize: 20
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        //Layout.preferredWidth: c_rect.width * 0.8
                        Layout.fillWidth: true
                        //Layout.alignment: Qt.AlignHCenter
                    }

                    Rectangle{
                        Layout.fillWidth: true
                        Layout.preferredHeight: about.height
                        //color: "black"
                        Label {
                            id: about
                            anchors.centerIn: parent
                            //Layout.fillWidth: true
                            width: parent.width
                            text: "TukTrack helps tuktuk owners in Madagascar manage their vehicles, track driver deposits, and schedule maintenance efficiently."
                            wrapMode: Text.Wrap
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                            //Layout.preferredWidth: c_rect.width * 0.8
                        }
                    }



                    GroupBox {
                        title: "Key Features"
                        Layout.fillWidth: true

                        Column {
                            spacing: 8
                            Text { text: "• Manage tuktuks & drivers" }
                            Text { text: "• Assign shifts & track deposits" }
                            Text { text: "• Schedule and track maintenance" }
                            Text { text: "• Visualize revenue and expenses" }
                        }
                    }

                    GroupBox {
                        title: "Developer Info"
                        Layout.fillWidth: true

                        Column {
                            spacing: 4
                            Text { text: "Developer: iRoot" }
                            Text { text: "Contact: irootsoftware@gmail.com" }
                        }
                    }

                    Button {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Privacy Policy"
                        //onClicked: Qt.openUrlExternally("https://yourdomain.com/privacy")
                    }

                    Button {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Send Feedback"
                        onClicked: Qt.openUrlExternally("mailto:irootsoftware@gmail.com")
                    }

                    Rectangle {
                        Layout.alignment: Qt.AlignHCenter
                        height: 1
                        color: "#ccc"
                        width:  root.width * 0.8
                    }

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: "Built with love to support local tuktuk businesses. 🇲🇬"
                        font.italic: true
                        horizontalAlignment: Text.AlignHCenter
                        width:  root.width * 0.8
                        wrapMode: Text.Wrap
                    }
                }
            }
    }


}
