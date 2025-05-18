import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts
import QtCharts
import TukTrack
import "../Components"


Page {
    /*Connections{
        target: uiController
        function onGoMaintenanceRecord() {
            loadRevenueBarSeries(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
        }
    }*/

    Connections{
        target: maintenanceRecordController
        function onStartDateChanged() {
            loadRevenueBarSeries(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
            loadCostByTucSeries(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
            loadCostByMaintenanceType(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
        }

        function onEndDateChanged() {
            loadRevenueBarSeries(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
            loadCostByTucSeries(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
            loadCostByMaintenanceType(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
        }
    }

    Component.onCompleted: {
        loadRevenueBarSeries(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
        loadCostByTucSeries(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
        loadCostByMaintenanceType(maintenanceRecordController.startDate, maintenanceRecordController.endDate)
    }

    function formatNumber(number) {
        var loc = Qt.locale()
        return loc.toString(number)
    }

    function formatFloat(number) {
        //var loc = Qt.locale()
        return number.toLocaleString(Qt.locale(), 'f', 2)
    }

    function loadRevenueBarSeries(startDate, endDate){
            maintenanceRecordController.revenueChartModel.loadData(startDate, endDate)
            var count = maintenanceRecordController.revenueChartModel.rowSize()
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
                var month = maintenanceRecordController.revenueChartModel.dataAt(index, 257)
                var amounts = maintenanceRecordController.revenueChartModel.dataAt(index, 258)
                var expense = maintenanceRecordController.revenueChartModel.dataAt(index, 259)
                monthAxis.categories.push(month)
                monthGAxis.categories.push(month)

                revenueBarSerie.at(0).values.push(amounts[0])
                revenueYaxis.max = Math.max(revenueYaxis.max, amounts[0])

                expenseBarSerie.at(0).values.push(expense[0])
                expenseYaxis.max = Math.max(expenseYaxis.max, expense[0])
            }
        }
    function loadCostByTucSeries (startDate, endDate) {
        maintenanceRecordController.maintenanceCostByTuk.loadData(startDate, endDate)
        var count = maintenanceRecordController.maintenanceCostByTuk.rowCount()
        costByTucSeries.clear()
        for (var index = 0; index < count; index ++) {
            costByTucSeries.append(maintenanceRecordController.maintenanceCostByTuk.dataAt(index, 257), maintenanceRecordController.maintenanceCostByTuk.dataAt(index, 258))
        }
    }

    function loadCostByMaintenanceType (startDate, endDate) {
        maintenanceRecordController.maintenanceCostByType.loadData(startDate, endDate)
        var count = maintenanceRecordController.maintenanceCostByType.rowCount()
        costByTypeSeries.clear()
        var colors = generateColors(count, "green")
        for (var index = 0; index < count; index ++) {
            var slice = costByTypeSeries.append(maintenanceRecordController.maintenanceCostByType.dataAt(index, 257), maintenanceRecordController.maintenanceCostByType.dataAt(index, 258))
            slice.color = colors[index]
        }
    }

    function generateColors(colorCount, color_) {
        var colors = []
        var color = Qt.color(color_)
        //color.setHsv(12, 122, 0)
        for (let i = colorCount - 1; i >= 0; i--) {
            var lightness = i / colorCount
            colors.push(Qt.hsla(0.1, 0.97, lightness, 1))
            //colors.push(color)
        }
        return colors
    }
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
                text: "Maintenance Record"
                font.bold: true
                font.pointSize: 16
                leftPadding: 8
                color: "#023047"
            }
        }
    }
    RowLayout{
        id: datePickerRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 12
        spacing: 4
        //height: 300

        TextField {
            id: fromDateChooser
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 150
            placeholderText: "From"
            readOnly: true
            text: Qt.formatDate(maintenanceRecordController.startDate, "dd/MM/yyyy")
            onPressed: {
                fromDateChoserPopup.open()
            }

        }

        TextField {
            id: toDateChooser
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 150
            placeholderText: "To"
            readOnly: true
            text: Qt.formatDate(maintenanceRecordController.endDate, "dd/MM/yyyy")
            onPressed: {
                toDateChoserPopup.open()
            }

        }
    }

    ScrollView{
        id: scrollView
        anchors.top: datePickerRow.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 8
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        Column{
            width: parent.width
            spacing: 20
            Item{
                id: pastMaintenanceItem
                width: parent.width
                height: scrollView.contentItem.height * 0.3

                DropShadow{
                    anchors.fill: pastMaintenanceRect
                    source: pastMaintenanceRect
                    horizontalOffset: 0
                    verticalOffset: 0
                    radius: 4
                    samples: 9
                    color: "#aa000000"
                }

                Rectangle {
                    id: pastMaintenanceRect
                    anchors.fill: parent
                    anchors.margins: 4
                    radius: 12
                    //anchors.topMargin: 6
                    Rectangle{
                        id: pastTitleRect
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: pastMheaderRow.height + 6
                        color: Style.primary
                        radius: 12
                        Rectangle{
                            width: parent.width
                            height: 12
                            anchors.bottom: parent.bottom
                            color: parent.color
                        }

                        RowLayout{
                            id: pastMheaderRow
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 4
                            Label{
                                text: "Date"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                Layout.alignment: Qt.AlignVCenter
                                color: Style.accent
                                font.bold: true
                                Layout.preferredWidth: 110
                            }
                            Label{
                                text: "Maintenance"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                color: Style.accent
                                font.bold: true
                                Layout.preferredWidth: 100
                                wrapMode: Label.Wrap
                            }
                            Label{
                                text: "Cost (Ar)"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                color: Style.accent
                                font.bold: true
                                Layout.preferredWidth: 50
                            }
                            Label{
                                text: "Description"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                color: Style.accent
                                font.bold: true
                                Layout.fillWidth: true
                                wrapMode: Label.Wrap
                            }
                        }
                    }

                    ListView{
                        id: pastMaintenanceListView
                        anchors.top: pastTitleRect.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.margins: 6
                        model: maintenanceRecordController.maintenanceList
                        clip: true

                        delegate: ItemDelegate{
                            width: pastMaintenanceListView.width
                            //height: rowLayout2.implicitHeight + 20
                            contentItem: RowLayout{
                                id: rowLayout2
                                //anchors.left: parent.left
                                //anchors.right: parent.right
                                //anchors.fill: parent
                                //anchors.margins: 8
                                //height: d.height
                                Label{
                                    Layout.preferredWidth: 110
                                    text: Qt.formatDate(performedDate, "dd MMM yyyy")
                                }
                                Label{
                                    Layout.preferredWidth: 100
                                    text: maintenanceType
                                    wrapMode: Label.Wrap
                                }

                                Label{
                                    Layout.preferredWidth: 50
                                    text: cost
                                }

                                Label{
                                    Layout.fillWidth: true
                                    text: description
                                    wrapMode: Label.Wrap
                                }
                            }
                        }

                    }
                }
            }

            Item{
                id: revenueChartItem
                width: parent.width
                height: scrollView.contentItem.height * 0.35

                DropShadow{
                    anchors.fill: revenueChartRect
                    source: revenueChartRect
                    horizontalOffset: 0
                    verticalOffset: 0
                    radius: 4
                    samples: 9
                    color: "#aa000000"
                }

                Rectangle {
                    id: revenueChartRect
                    anchors.fill: parent
                    anchors.margins: 4
                    radius: 12
                    //anchors.topMargin: 6
                    Rectangle{
                        id: revenueChartTitleRect
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: pastMheaderRow.height + 6
                        color: Style.primary
                        radius: 12
                        Rectangle{
                            width: parent.width
                            height: 12
                            anchors.bottom: parent.bottom
                            color: parent.color
                        }
                        Label{
                            anchors.centerIn: parent
                            color: Style.accent
                            text: "Revenue & maintenance cost"
                        }
                    }

                    ChartView{
                        id: revenueChartView
                        anchors.top: revenueChartTitleRect.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
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
                                labelsAngle: -50

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
                                labelsAngle: -50
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

            Item{
                width: parent.width
                height: scrollView.contentItem.height * 0.35

                DropShadow{
                    anchors.fill: costByTucChartRect
                    source: costByTucChartRect
                    horizontalOffset: 0
                    verticalOffset: 0
                    radius: 4
                    samples: 9
                    color: "#aa000000"
                }

                Rectangle {
                    id: costByTucChartRect
                    anchors.fill: parent
                    anchors.margins: 4
                    radius: 12
                    //anchors.topMargin: 6
                    Rectangle{
                        id: costByTucChartTitleRect
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: pastMheaderRow.height + 6
                        color: Style.accent
                        radius: 12
                        Rectangle{
                            width: parent.width
                            height: 12
                            anchors.bottom: parent.bottom
                            color: parent.color
                        }
                        Label{
                            anchors.centerIn: parent
                            color: "white"
                            text: "maintenance cost per Tuctuc (Ar)"
                        }
                    }

                    ChartView{
                        id: costByTucChartView
                        anchors.top: costByTucChartTitleRect.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
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
                        ScrollView{
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.margins: 8
                            Column{
                                id: customLegend
                                width: parent.width
                                spacing: 4

                                Repeater {
                                    model: costByTucSeries.count
                                    delegate: Row {
                                        spacing: 8

                                        Rectangle {
                                            width: 16; height: 16
                                            color: costByTucSeries.at(index).color
                                        }

                                        Text {
                                            text: maintenanceRecordController.maintenanceCostByTuk.dataAt(index, 257) + " (" + formatNumber(costByTucSeries.at(index).value) + ")"
                                        }
                                    }
                                }
                            }
                        }


                        PieSeries{
                            id: costByTucSeries
                            horizontalPosition: 0.3
                            size: 0.9
                            onClicked: (pieSlice) => {
                                pieSlice.exploded = !pieSlice.exploded
                                pieSlice.label = qsTr("%1 %").arg((pieSlice.percentage * 100).toLocaleString(Qt.locale(), 'f', 2))
                                pieSlice.labelPosition = PieSlice.LabelInsideNormal
                                pieSlice.labelVisible = pieSlice.exploded
                                pieSlice.labelColor = "white"

                            }
                        }

                    }
                }
            }

            Item{
                width: parent.width
                height: scrollView.contentItem.height * 0.35

                DropShadow{
                    anchors.fill: costByTypeChartRect
                    source: costByTypeChartRect
                    horizontalOffset: 0
                    verticalOffset: 0
                    radius: 4
                    samples: 9
                    color: "#aa000000"
                }

                Rectangle {
                    id: costByTypeChartRect
                    anchors.fill: parent
                    anchors.margins: 4
                    radius: 12
                    //anchors.topMargin: 6
                    Rectangle{
                        id: costByTypeChartTitleRect
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: pastMheaderRow.height + 6
                        color: Style.primary
                        radius: 12
                        Rectangle{
                            width: parent.width
                            height: 12
                            anchors.bottom: parent.bottom
                            color: parent.color
                        }
                        Label{
                            anchors.centerIn: parent
                            color: Style.accent
                            text: "maintenance cost per type (Ar)"
                        }
                    }

                    ChartView{
                        id: costByTypeChartView
                        anchors.top: costByTypeChartTitleRect.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
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
                        ScrollView{
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.margins: 8
                            width: parent.width * 0.4
                            Column{
                                width: parent.width
                                spacing: 4

                                Repeater {
                                    model: costByTypeSeries.count
                                    delegate: Row {
                                        spacing: 8

                                        Rectangle {
                                            width: 16; height: 16
                                            color: costByTypeSeries.at(index).color
                                        }

                                        Text {
                                            width: costByTypeChartView.width * 0.35
                                            wrapMode: Text.Wrap
                                            //text: qsTr("%1").arg()
                                            text: maintenanceRecordController.maintenanceCostByType.dataAt(index, 257) + " (" + formatNumber(costByTypeSeries.at(index).value) + ")"
                                        }
                                    }
                                }
                            }
                        }


                        PieSeries{
                            id: costByTypeSeries
                            horizontalPosition: 0.3
                            size: 0.9
                            onClicked: (pieSlice) => {
                                pieSlice.exploded = !pieSlice.exploded
                                pieSlice.label = qsTr("%1 %").arg((pieSlice.percentage * 100).toLocaleString(Qt.locale(), 'f', 2))
                                pieSlice.labelPosition = PieSlice.LabelInsideNormal
                                pieSlice.labelVisible = pieSlice.exploded
                                pieSlice.labelColor = "white"
                            }
                        }
                    }
                }
            }

            GridLayout{
                width: parent.width
                columns: 2
                columnSpacing: 8
                rowSpacing: 12
                Rectangle{
                    Layout.preferredHeight: 60
                    Layout.preferredWidth: 120
                    radius: 12
                    color: Style.primary
                    ColumnLayout{
                        anchors.fill: parent
                        anchors.margins: 8
                        Label{
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            text: "Total revenue"
                            color: "white"
                        }

                        Label{
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            text: formatNumber(maintenanceRecordController.revenueChartModel.totalRevenue) + " Ar"
                            color: "white"
                            font.bold: true
                        }
                    }


                }
                ChartView{
                    id: expensePercendageChartView
                    Layout.rowSpan: 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
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
                    PieSeries{
                        id: expensePercentageSeries
                        size: 0.9
                        holeSize: 0.4
                        PieSlice{
                            label: formatFloat(percentage * 100) + " %"
                            value: maintenanceRecordController.revenueChartModel.totalMaintenanceCost
                            color: Style.accent
                            labelVisible: true
                        }
                        PieSlice{
                            label: formatFloat(percentage * 100) + " %"
                            labelVisible: true
                            value: maintenanceRecordController.revenueChartModel.totalRevenue - maintenanceRecordController.revenueChartModel.totalMaintenanceCost
                            color: Style.primary
                        }
                    }
                }

                Rectangle{
                    Layout.preferredHeight: 60
                    Layout.preferredWidth: 120
                    radius: 12
                    color: Style.accent
                    ColumnLayout{
                        anchors.fill: parent
                        anchors.margins: 8
                        Label{
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            text: "Total expense"
                            color: "white"
                        }

                        Label{
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            text: formatNumber(maintenanceRecordController.revenueChartModel.totalMaintenanceCost) + " Ar"
                            color: "white"
                            font.bold: true
                        }
                    }
                }
            }
        }
    }

    DatePickerPopup{
        id: fromDateChoserPopup
        anchors.centerIn: parent
        selected_date: maintenanceRecordController.startDate
        onDateSelected: {
            maintenanceRecordController.startDate = selected_date
        }

    }
    DatePickerPopup{
        id: toDateChoserPopup
        anchors.centerIn: parent
        selected_date: maintenanceRecordController.endDate
        onDateSelected: {
            maintenanceRecordController.endDate = selected_date
        }
    }
}
