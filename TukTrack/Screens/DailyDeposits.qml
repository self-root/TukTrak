import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts
import TukTrack


Page {
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
                text: "Daily deposits"
                font.bold: true
                font.pointSize: 16
                leftPadding: 8
                color: "#023047"
            }
        }
    }

    ListView {
        id: horizontalTumbler
        //property int lastIndex
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        width: parent.width
        height: 60
        layoutDirection: Qt.RightToLeft
        orientation: ListView.Horizontal
        snapMode: ListView.SnapToItem
        boundsMovement: Flickable.FollowBoundsBehavior
        boundsBehavior: Flickable.DragOverBounds
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: width / 2 - (width / 3) / 2
        preferredHighlightEnd: width / 2 + (width / 3) / 2

        model: depositDateList

        delegate: ItemDelegate {
            background: Rectangle {
                color: "transparent"
            }

            width: horizontalTumbler.width / 3
            height: 60

            contentItem: Rectangle {
                width: parent.width
                height: parent.height
                anchors.margins: 6
                color: "transparent"
                Label{
                    text: Qt.formatDate(depositDate, "dd MMM yyyy")
                    color: index === horizontalTumbler.currentIndex ? "white" : Style.accent
                    anchors.centerIn: parent
                }
            }
            onClicked: {
                console.log("clicked index: " + index)
                horizontalTumbler.currentIndex = index
            }
        }

        highlight: Rectangle{
            width: horizontalTumbler.width / 3
            height: 100
            color: Style.primary
        }

        onCurrentItemChanged: {
            console.log("Curent changed: " + horizontalTumbler.currentIndex)
            //console.log("Count: " + horizontalTumbler.count)
            dailyDepositModels.setCurrentDate(depositDateList.dateAt(horizontalTumbler.currentIndex))
        }

        Component.onCompleted: {
            horizontalTumbler.currentIndex = 0
            //positionViewAtEnd()
        }

    }

    ScrollView{
        anchors.top: horizontalTumbler.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 6
        Column{
            spacing: 4
            anchors.fill: parent
            Rectangle{
                id: nightDepositListTitleRect
                width: parent.width
                height: 30
                color: Style.accent
                Text {
                    id: depositListTitle
                    text: qsTr("Morning Deposit Lists")
                    color: "white"
                    anchors.centerIn: parent
                }
            }
            Rectangle{
                id: nightDepositHeaderRect
                width: parent.width
                height: nightDepositHeaderRow.height + 6
                color: Style.primary
                //anchors.topMargin: 4
                //anchors.left: nightDepositListView.left
                RowLayout{
                    id: nightDepositHeaderRow
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 4

                    Label{
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Chauffeur"
                        color: Style.accent
                        font.bold: true
                    }

                    Label{
                        Layout.preferredWidth: 100
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Amount (Ar)"
                        color: Style.accent
                        font.bold: true
                    }
                    Label{
                        Layout.preferredWidth: 100
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Reste (Ar)"
                        color: Style.accent
                        font.bold: true
                    }
                }
            }
            ListView{
                id: nightDepositListView
                width: parent.width
                height: 300
                clip: true
                model: dailyDepositModels.nightShiftModel

                delegate: ItemDelegate{
                    width: nightDepositListView.width
                    height: 30

                    background: Rectangle{
                        width: nightDepositListView.width
                        height: 28
                        anchors.verticalCenter: parent.verticalCenter
                        color: hasDepositLeft ? "#f79d65" : "white"
                    }

                    contentItem: RowLayout{
                        Label{
                            Layout.fillWidth: true
                            verticalAlignment: Text.AlignVCenter
                            text: driverName
                        }
                        Label{
                            Layout.preferredWidth: 100
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: amount
                        }

                        Label{
                            Layout.preferredWidth: 100
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: rest
                        }
                    }
                }
            }

            Rectangle{
                id: dayDepositListTitleRect
                width: parent.width
                height: 30
                color: Style.accent
                Text {
                    text: qsTr("Evening Deposit Lists")
                    color: "white"
                    anchors.centerIn: parent
                }
            }
            Rectangle{
                id: dayDepositHeaderRect
                width: parent.width
                height: dayDepositHeaderRow.height + 6
                color: Style.primary
                //anchors.topMargin: 4
                //anchors.left: nightDepositListView.left
                RowLayout{
                    id: dayDepositHeaderRow
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 4

                    Label{
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Chauffeur"
                        color: Style.accent
                        font.bold: true
                    }

                    Label{
                        Layout.preferredWidth: 100
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Amount (Ar)"
                        color: Style.accent
                        font.bold: true
                    }
                    Label{
                        Layout.preferredWidth: 100
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: "Reste (Ar)"
                        color: Style.accent
                        font.bold: true
                    }
                }
            }
            ListView{
                id: dayDepositListView
                width: parent.width
                height: 300
                clip: true
                model: dailyDepositModels.dayShiftModel

                delegate: ItemDelegate{
                    width: nightDepositListView.width
                    height: 30

                    background: Rectangle{
                        width: dayDepositListView.width
                        height: 28
                        anchors.verticalCenter: parent.verticalCenter
                        color: hasDepositLeft ? "#f79d65" : "white"
                    }

                    contentItem: RowLayout{
                        Label{
                            Layout.fillWidth: true
                            verticalAlignment: Text.AlignVCenter
                            text: driverName
                        }
                        Label{
                            Layout.preferredWidth: 100
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: amount
                        }

                        Label{
                            Layout.preferredWidth: 100
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: rest
                        }
                    }
                }
            }
        }
    }
}
