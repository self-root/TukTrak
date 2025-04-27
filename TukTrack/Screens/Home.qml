import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import TukTrack 1.0
import Qt5Compat.GraphicalEffects
import QtCharts

Page {
    id: root
    function formatNumber(number) {
        var loc = Qt.locale()
        return loc.toString(number)
    }
    function loadRevenueBarSeries(){
            dashboardModel.revenueChartModel.loadData()
            var count = dashboardModel.revenueChartModel.rowSize()
            revenueBarSerie.clear()
            expenseBarSerie.clear()
            monthAxis.categories = []
            monthGAxis.categories = []
            revenueYaxis.max = 0
            expenseYaxis.max = 0
            revenueBarSerie.append("Revenue", [])
            expenseBarSerie.append("Expenses", [])
            revenueBarSerie.at(0).color = "#003566"
            expenseBarSerie.at(0).color = "#fca311"

            for (var index = 0; index < count; index++)
            {
                var month = dashboardModel.revenueChartModel.dataAt(index, 257)
                var amounts = dashboardModel.revenueChartModel.dataAt(index, 258)
                var expense = dashboardModel.revenueChartModel.dataAt(index, 259)
                monthAxis.categories.push(month)
                monthGAxis.categories.push(month)

                revenueBarSerie.at(0).values.push(amounts[0])
                revenueYaxis.max = Math.max(revenueYaxis.max, amounts[0])

                expenseBarSerie.at(0).values.push(expense[0])
                expenseYaxis.max = Math.max(expenseYaxis.max, expense[0])
            }
        }
    Component.onCompleted: {
        loadRevenueBarSeries()
    }

    Material.background: "#ffffff"
    header: ToolBar{
        Material.primary:  "white"
        //Material.foreground: Material.accent
        //Material.elevation: 5
        RowLayout{
            anchors.fill: parent
            spacing: 20

            Label {
                id: title
                text: qsTr("TukTrack")
                color: "#fca311"
                leftPadding: 8
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignLeft
                Layout.fillWidth: true
                font.bold: true
                font.pointSize: 18
            }
        }
    }

    GridLayout{
        columns: 2
        columnSpacing: 12
        rowSpacing: 8
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        Item{
            id: totalTukItem
            Layout.preferredHeight: 120
            Layout.maximumHeight: 160
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            DropShadow{
                anchors.fill: tukCountRect
                source:  tukCountRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
            }

            Rectangle{
                id: tukCountRect
                anchors.fill: parent
                //anchors.margins: 18
                radius: 16
                color: "white"
                ColumnLayout{
                    anchors.fill: parent
                    anchors.margins: 6
                    Rectangle{
                        id: tukImgWrapper
                        Layout.preferredHeight: 40
                        Layout.fillWidth: true
                        color: "transparent"
                        Image {
                            source: "qrc:/images/images/tuc-tuc.png"
                            height: parent.height
                            fillMode: Image.PreserveAspectFit
                        }
                    }



                    Label{
                        text: "Total Tuctuc"
                        font.pixelSize: 18
                        color: "#fca311"
                    }
                    Label{
                        font.bold: true
                        font.pixelSize: 26
                        text: dashboardModel.totalActiveTuk
                        color: "#fca311"
                    }
                }


            }
        }

        Item{
            id: totalDriverItem
            Layout.preferredHeight: 120
            Layout.maximumHeight: 160
            Layout.fillWidth: true
            //Layout.maximumHeight: 200
            Layout.alignment: Qt.AlignTop
            DropShadow{
                anchors.fill: driverCountRect
                source:  driverCountRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
            }

            Rectangle{
                id: driverCountRect
                anchors.fill: parent
                //anchors.margins: 18
                radius: 16
                color: "#001219"
                ColumnLayout{
                    anchors.fill: parent
                    anchors.margins: 6
                    Rectangle{
                        id: driverImgWrapper
                        Layout.preferredHeight: 40
                        Layout.fillWidth: true
                        color: "transparent"
                        Image {
                            source: "qrc:/images/images/driver.png"
                            height: parent.height
                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    Label{
                        text: "Total Chauffeur"
                        font.pixelSize: 18
                        color: "white"
                    }
                    Label{
                        font.bold: true
                        font.pixelSize: 26
                        text: dashboardModel.totalActiveDriver
                        color: "white"
                    }
                }


            }
        }

        Item{
            Layout.preferredHeight: 120
            Layout.fillWidth: true
            //Layout.maximumHeight: 200
            Layout.alignment: Qt.AlignTop
            DropShadow{
                anchors.fill: totalRevenueRect
                source:  totalRevenueRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
            }

            Rectangle{
                id: totalRevenueRect
                anchors.fill: parent
                //anchors.margins: 18
                radius: 16
                color: "#003566"
                ColumnLayout{
                    anchors.fill: parent
                    anchors.margins: 6
                    Rectangle{
                        id: revenueImgWrapper
                        Layout.preferredHeight: 40
                        Layout.fillWidth: true
                        color: "transparent"
                        Image {
                            source: "qrc:/images/images/money.png"
                            height: parent.height
                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    Label{
                        text: "Revenu total"
                        font.pixelSize: 18
                        color: "white"
                    }
                    Label{
                        font.bold: true
                        font.pixelSize: 26
                        text: formatNumber(dashboardModel.thisMonthRevenue) + " Ar"
                        color: "white"
                    }
                }
            }
        }

        Item{
            Layout.preferredHeight: 120
            Layout.fillWidth: true
            //Layout.maximumHeight: 200
            Layout.alignment: Qt.AlignTop
            DropShadow{
                anchors.fill: totalexpenseRect
                source:  totalexpenseRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
            }

            Rectangle{
                id: totalexpenseRect
                anchors.fill: parent
                //anchors.margins: 18
                radius: 16
                color: "#fca311"
                ColumnLayout{
                    anchors.fill: parent
                    anchors.margins: 6
                    Rectangle{
                        id: expenseImgWrapper
                        Layout.preferredHeight: 40
                        Layout.fillWidth: true
                        color: "transparent"
                        Image {
                            source: "qrc:/images/images/expenses.png"
                            height: parent.height
                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    Label{
                        text: "Dépenses du mois"
                        font.pixelSize: 18
                        color: "white"
                    }
                    Label{
                        font.bold: true
                        font.pixelSize: 26
                        text: formatNumber(dashboardModel.thisMonthExpense) + " Ar"
                        color: "white"
                    }
                }
            }
        }

        Item {
            id: upcomingMaintenanceItem
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
            DropShadow{
                source: maintenanceListViewRect
                anchors.fill: maintenanceListViewRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
            }

            Rectangle{
                id: maintenanceListViewRect
                anchors.fill: parent
                color: "white"
                radius: 16
                Rectangle{
                    id: maintenanceListTitleRect
                    width: parent.width
                    anchors.top: parent.top
                    radius: 16
                    height: 30
                    color: "#003566"
                    Rectangle{
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.left: parent.left
                        height: 16
                        color: parent.color
                    }
                    Text {
                        id: depositListTitle
                        text: qsTr("Maintenances à venir")
                        color: "white"
                        anchors.centerIn: parent
                    }


                }

                Rectangle{
                    id: futureTitleRect
                    anchors.top: maintenanceListTitleRect.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right

                    height: futureMheaderRow.height + 6
                    color: Style.primary
                    RowLayout{
                        id: futureMheaderRow
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: 16
                        anchors.rightMargin: 16
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 4
                        Label{
                            text: "Date"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            Layout.alignment: Qt.AlignVCenter
                            color: Style.accent
                            font.bold: true
                            Layout.preferredWidth: 120
                        }
                        Label{
                            text: "Maintenance"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: Style.accent
                            font.bold: true
                            Layout.fillWidth: true
                            wrapMode: Label.Wrap
                        }
                        Label{
                            text: "Tuc Tuc"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: Style.accent
                            font.bold: true
                            Layout.preferredWidth: 80
                        }
                    }
                }

                ListView{
                    id: futureMaintenanceListView
                    anchors.top: futureTitleRect.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 4
                    anchors.bottomMargin: 16
                    anchors.leftMargin: 16
                    anchors.rightMargin: 16
                    clip: true
                    model: dashboardModel.upcomingMaintenanceListModel

                    delegate: ItemDelegate{
                        width: futureMaintenanceListView.width
                        height: rowLayout.implicitHeight + 20

                        background: Rectangle{
                            width: futureMaintenanceListView.width
                            height: rowLayout.implicitHeight + 20
                            anchors.verticalCenter: rowLayout.verticalCenter
                            color: index % 2 === 0? "white" : "#fe6d73"
                            radius: 16
                        }
                        contentItem: RowLayout{
                            id: rowLayout
                            Label{
                                Layout.preferredWidth: 120
                                Layout.alignment: Qt.AlignVCenter
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                text: Qt.formatDate(schduleDate, "dd MMM yyyy")
                            }
                            Label{
                                Layout.fillWidth: true
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                text: maintenanceType
                                wrapMode: Label.Wrap
                            }

                            Label{
                                Layout.preferredWidth: 80
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                text: tukNumber
                            }

                        }
                    }

                }
            }


        }
        Item {
            id: revenueChartItem
            Layout.columnSpan: 2
            Layout.fillHeight: true
            Layout.fillWidth: true
            DropShadow{
                source: revenueChartRect
                anchors.fill: revenueChartRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
            }

            Rectangle{
                id: revenueChartRect
                anchors.fill: parent
                color: "white"
                radius: 16

                ChartView{
                    id: revenueChartView
                    title: "Bilan des 4 Derniers Mois"
                    anchors.fill: parent
                    legend.alignment: Qt.AlignLeft
                    antialiasing: true
                    animationOptions: ChartView.SeriesAnimations
                    locale: Qt.locale("en_US")
                    localizeNumbers: true
                    margins.left: 0
                    margins.top: 0
                    margins.right: 0
                    margins.bottom: 0
                    legend.visible: false

                    BarSeries{
                        id: revenueBarSerie
                        axisX: BarCategoryAxis {
                            id: monthAxis
                            categories: ["Revenues"]
                        }
                        axisY: ValuesAxis{
                            id: revenueYaxis
                            min: 0
                            max: 100

                            labelFormat: "%.0f"
                            titleText: "Revenus (Ar)"
                        }
                    }

                    BarSeries{
                        id: expenseBarSerie
                        axisX: BarCategoryAxis {
                            id: monthGAxis
                            visible: false
                            categories: ["Expenses"]
                        }
                        axisYRight: ValuesAxis{
                            id: expenseYaxis
                            min: 0
                            max: 40

                            labelFormat: "%.0f"
                            titleText: "Dépenses (Ar)"
                        }
                    }
                }
            }

        }
    }

}
