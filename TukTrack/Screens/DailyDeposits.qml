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
            dailyDepositModels.setCurrentDate(depositDateList.dateAt(horizontalTumbler.currentIndex))
        }

        Component.onCompleted: {
            horizontalTumbler.currentIndex = 0
            //positionViewAtEnd()
        }

    }

    ScrollView{
        id: scrollview
        anchors.top: horizontalTumbler.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 6
        Column{
            spacing: 4
            anchors.fill: parent
            //anchors.margins: 12
            Item {
                id: morningDepositWrapper
                height: scrollview.contentItem.height * 0.35
                width: parent.width
                DropShadow{
                    source:  nightDepositRect
                    anchors.fill: nightDepositRect
                    radius: 4
                    verticalOffset: 0
                    horizontalOffset: 0
                    samples: 9
                    color: "#aa000000"
                }

                Rectangle{
                    id: nightDepositRect
                    anchors.fill: parent
                    anchors.margins: 6
                    radius: 12
                    ColumnLayout{
                        spacing: 0
                        anchors.fill: parent
                        Rectangle{
                            id: nightDepositListTitleRect
                            Layout.preferredHeight: 30
                            Layout.fillWidth: true
                            color: Style.accent
                            radius: 12

                            Rectangle{
                                width: parent.width
                                height: 12
                                anchors.bottom: parent.bottom
                                color: parent.color
                            }

                            Text {
                                id: depositListTitle
                                text: qsTr("Morning Deposit Lists")
                                color: "white"
                                anchors.centerIn: parent
                            }
                        }
                        Rectangle{
                            id: nightDepositHeaderRect
                            //width: parent.width
                            //height: nightDepositHeaderRow.height + 6
                            Layout.fillWidth: true
                            Layout.preferredHeight: nightDepositHeaderRow.height + 6
                            color: Style.primary
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
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.bottomMargin: 12
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
                                onClicked: {
                                    driverDetail.setCurrentDriverId(driverId)
                                    depositSettingListModel.loadDriverDepositSetting(driverId)
                                    depositListModel.setDriverId(driverId)
                                    depositListModel.loadDeposit()
                                    uiController.goDriverDetails()
                                }
                            }
                        }
                    }
                }
            }

            Item {
                id: dayDepositWarpper
                height: scrollview.contentItem.height * 0.35
                width: parent.width
                DropShadow{
                    source:  dayDepositRect
                    anchors.fill: dayDepositRect
                    radius: 4
                    verticalOffset: 0
                    horizontalOffset: 0
                    samples: 9
                    color: "#aa000000"
                }
                Rectangle{
                    id: dayDepositRect
                    anchors.fill: parent
                    anchors.margins: 6
                    radius: 12
                    ColumnLayout{
                        anchors.fill: parent
                        spacing: 0
                        Rectangle{
                            id: dayDepositListTitleRect
                            //width: parent.width
                            //height: 30
                            Layout.preferredHeight: 30
                            Layout.fillWidth: true
                            color: Style.accent
                            radius: 12

                            Rectangle{
                                width: parent.width
                                height: 12
                                anchors.bottom: parent.bottom
                                color: parent.color
                            }
                            Text {
                                text: qsTr("Evening Deposit Lists")
                                color: "white"
                                anchors.centerIn: parent
                            }
                        }
                        Rectangle{
                            id: dayDepositHeaderRect
                            //width: parent.width
                            //height: dayDepositHeaderRow.height + 6
                            Layout.preferredHeight: dayDepositHeaderRow.height + 6
                            Layout.fillWidth: true
                            color: Style.primary

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
                            //width: parent.width
                            //height: parent.height
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Layout.bottomMargin: 12
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

                                onClicked: {
                                    driverDetail.setCurrentDriverId(driverId)
                                    depositSettingListModel.loadDriverDepositSetting(driverId)
                                    depositListModel.setDriverId(driverId)
                                    depositListModel.loadDeposit()
                                    uiController.goDriverDetails()
                                }
                            }
                        }
                    }
                }
            }

            Item{
                id: summaryWrapper
                width: parent.width
                height: 140
                DropShadow{
                    source:  summaryRect
                    anchors.fill: summaryRect
                    radius: 4
                    verticalOffset: 0
                    horizontalOffset: 0
                    samples: 9
                    color: "#aa000000"
                }
                Rectangle{
                    id: summaryRect
                    anchors.fill: parent
                    anchors.margins: 6
                    radius: 12
                    color: "white"
                    GridLayout{
                        anchors.fill: parent
                        anchors.margins: 8
                        columns: 2
                        Label{
                            text: "Morning deposit"
                        }
                        Label{
                            text: dailyDepositModels.nightShiftModel.totalDeposit + " Ar"
                        }
                        Label{
                            text: "Evening deposit"
                        }
                        Label{
                            text: dailyDepositModels.dayShiftModel.totalDeposit + " Ar"
                        }
                        Rectangle{
                            Layout.preferredWidth: parent.width * 0.8
                            Layout.preferredHeight: 2
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            Layout.columnSpan: 2
                            radius: 1
                            color: Style.primary
                        }
                        Label{
                            text: "Total"
                            font.bold: true
                        }


                        Label{
                            text: (dailyDepositModels.nightShiftModel.totalDeposit + dailyDepositModels.dayShiftModel.totalDeposit) + " Ar"
                            font.bold: true
                        }
                    }
                }
            }
        }
    }
}
