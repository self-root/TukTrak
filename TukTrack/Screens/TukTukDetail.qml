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
                text: tukDetailModel.tuktuk.registrationNumber
                font.bold: true
                font.pointSize: 16
                leftPadding: 8
                color: "#023047"
            }

            ToolButton{
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: 6
                text: "\uf142"
                font.family: Style.webFont
                font.bold: true
                font.pointSize: 14
                Material.foreground: "#023047"
                onClicked: menu.popup()

                Menu{
                    id: menu
                    MenuItem{
                        text: "Change status"
                        onClicked: {
                            statusUpdateDialog.open()
                        }
                    }

                    MenuItem{
                        text: "Update Tuctuc"
                        onClicked: {
                            tukUpdateDialog.open()
                        }
                    }

                    MenuItem{
                        text: "Supprimer"
                        onClicked: {
                            confirmDeleteTukDialog.open()
                        }
                    }
                }
            }

        }
    }

    GridLayout{
        columnSpacing: 8
        rowSpacing: 8
        columns: 2
        anchors.fill: parent
        anchors.margins: 8
        Item {
            id: tukDetailItem
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            Layout.alignment: Qt.AlignTop
            DropShadow{
                source: detailRect
                anchors.fill: detailRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
                color:  "#aa000000"
            }
            Rectangle{
                id: detailRect
                anchors.fill: parent

                radius: 4
                color: Style.accent
                GridLayout{
                    anchors.centerIn: parent
                    columns: 2
                    rowSpacing: 6
                    Label{
                        text: "Numero: "
                        color: "white"
                    }
                    Label {
                        text: tukDetailModel.tuktuk.registrationNumber
                        color: "white"
                    }

                    Label {
                        text: "Model: "
                        color: "white"
                    }

                    Label{
                        text: tukDetailModel.tuktuk.model
                        color: "white"
                    }
                    Label {
                        text: "Phase: "
                        color: "white"
                    }

                    Label{
                        text: tukDetailModel.tuktuk.phase
                        color: "white"
                    }
                    Label{
                        text: "Achat: "
                        color: "white"
                    }
                    Label{
                        text: Qt.formatDate(tukDetailModel.tuktuk.purchaseDate, "dd MMM yyyy")
                        color: "white"
                    }

                    Label {
                        text: "Status: "
                        color: "white"
                    }

                    Label{
                        text: tukDetailModel.tuktuk.status
                        color: "white"
                    }
                }
            }
        }

        Item {
            id: tukDriverListItem
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            Layout.alignment: Qt.AlignTop
            DropShadow{
                source: driversRect
                anchors.fill: driversRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
                color:  "#aa000000"
            }
            Rectangle{
                id: driversRect
                anchors.fill: parent
                radius: 4
                color: "white"
                Rectangle{
                    id: driverListTitleRect
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    height: 30
                    radius: parent.radius
                    color: Style.accent
                    Rectangle{
                        anchors.right: parent.right
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        height: parent.radius
                        color: parent.color
                    }

                    //radius: 4
                    Label {
                        anchors.centerIn: parent
                        text: "Chauffeur"
                        color: "white"
                    }

                }

                Rectangle{
                    id: headerRect
                    anchors.left: driverListTitleRect.left
                    anchors.right: driverListTitleRect.right
                    anchors.top: driverListTitleRect.bottom
                    height: 25
                    color: Style.primary
                    RowLayout{
                        anchors.fill: parent
                        Label{
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            Layout.preferredWidth: driversRect.width * 0.5
                            text: "Prenom"
                            color: Style.accent
                            font.bold: true
                        }

                        Label{
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            Layout.preferredWidth: driversRect.width * 0.2
                            text: "Shift"
                            color: Style.accent
                            font.bold: true
                        }

                        Label{
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            Layout.preferredWidth: driversRect.width * 0.2
                            text: ""
                            color: Style.accent
                            font.bold: true
                        }
                    }


                }

                ListView{
                    id: driverListView
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.top: headerRect.bottom
                    anchors.rightMargin: 6
                    anchors.leftMargin: 6
                    anchors.topMargin: 3
                    anchors.bottom: parent.bottom
                    model: tukDetailModel.tukDriverListModel
                    clip: true

                    delegate: ItemDelegate{
                        width: driverListView.width
                        height: 25
                        contentItem: RowLayout{
                            anchors.fill: parent
                            Label{
                                Layout.preferredWidth: driversRect.width * 0.5
                                text: name
                                color: "black"
                            }
                            Label{
                                Layout.preferredWidth: driversRect.width * 0.2
                                text: shift
                            }

                            Label{
                                Layout.preferredWidth: driversRect.width * 0.2
                                horizontalAlignment: Text.AlignHCenter
                                text: "\uf111"
                                color: isActive? "#7ae582" : "#fe6d73"
                                font.bold: true
                                font.family: Style.webFont
                            }
                        }
                    }

                }
            }
        }

        Item {
            id: maintenanceListItem
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop
            Layout.columnSpan: 2

            DropShadow{
                source: maintenanceListRect
                anchors.fill: maintenanceListRect
                verticalOffset: 0
                horizontalOffset: 0
                radius: 6
                samples: 13
                color:  "#aa000000"
            }
            Rectangle{
                id: maintenanceListRect
                anchors.fill: parent
                radius: 4
                color: "white"
            }

            TabBar {
                id: bar
                anchors.top: parent.top
                width: parent.width
                TabButton {
                    text: "Maint. Prévue"
                }
                TabButton {
                    text: "Maint. terminée"
                }
                TabButton {
                    text: "Versement"
                }
            }

            StackLayout {
                anchors.top: bar.bottom
                currentIndex: bar.currentIndex
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.topMargin: 4
                Item {
                    id: futureMaintenanceTab
                    Rectangle{
                        id: futureTitleRect
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: futureMheaderRow.height + 6
                        color: Style.primary
                        RowLayout{
                            id: futureMheaderRow
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
                                Layout.preferredWidth: 120
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
                                text: "Rec(J)"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                color: Style.accent
                                font.bold: true
                                Layout.preferredWidth: 40
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

                    ToolButton{
                        id: addMaintenanceBtn
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.margins: 6
                        text: "\uf067"
                        font.family: Style.webFont
                        font.bold: true
                        font.pointSize: 14
                        onClicked: {
                            maintenanceFormDialog.update = false
                            maintenanceFormDialog.open()
                        }
                    }

                    ListView{
                        id: futureMaintenanceListView
                        anchors.top: futureTitleRect.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: addMaintenanceBtn.top
                        anchors.margins: 6
                        clip: true
                        model: tukDetailModel.futureMaintenanceListModel

                        delegate: SwipeDelegate{
                            width: futureMaintenanceListView.width
                            height: rowLayout.implicitHeight + 20
                            swipe.right: Row {
                                anchors.right: parent.right
                                anchors.verticalCenter: parent.verticalCenter
                                height: parent.height

                                Label {
                                    id: moveLabel
                                    text: "Modifier"
                                    color: "white"
                                    verticalAlignment: Label.AlignVCenter
                                    padding: 12
                                    height: parent.height

                                    SwipeDelegate.onClicked: {
                                        maintenanceFormDialog.update = true
                                        maintenanceFormDialog.update_id = maintenanceId
                                        maintenanaceTypeCombo.editText = maintenanceType
                                        descriptionEdit.text = description
                                        scheduleDatePopup.selected_date = schduleDate
                                        costEdit.text = cost
                                        reccurenceCheck.checkState = reccuring? Qt.Checked : Qt.Unchecked
                                        reccurenceDaysSpin.value = reccurenceDay
                                        maintenanceFormDialog.open()
                                    }

                                    background: Rectangle {
                                        color: moveLabel.SwipeDelegate.pressed ? Qt.darker("#ffbf47", 1.1) : "#ffbf47"
                                    }
                                }
                                Label {
                                    id: deleteLabel
                                    text: "Supprimer"
                                    color: "white"
                                    verticalAlignment: Label.AlignVCenter
                                    padding: 12
                                    height: parent.height

                                    SwipeDelegate.onClicked: {
                                        confirmMaintenanceDeleteDialog.confirm(maintenanceId, Qt.formatDate(schduleDate, "dd/MM/yyyy"))
                                    }

                                    background: Rectangle {
                                        color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                                    }
                                }
                            }
                            background: Rectangle{
                                width: futureMaintenanceListView.width
                                height: rowLayout.implicitHeight + 20
                                anchors.verticalCenter: rowLayout.verticalCenter
                                color: "white"
                            }
                            contentItem: RowLayout{
                                id: rowLayout
                                //anchors.left: parent.left
                                //anchors.right: parent.right
                                //height: d.height
                                //anchors.centerIn: parent
                                Label{
                                    Layout.preferredWidth: 120
                                    Layout.alignment: Qt.AlignVCenter
                                    verticalAlignment: Text.AlignVCenter
                                    text: Qt.formatDate(schduleDate, "dd MMM yyyy")
                                }
                                Label{
                                    Layout.preferredWidth: 100
                                    verticalAlignment: Text.AlignVCenter
                                    text: maintenanceType
                                    wrapMode: Label.Wrap
                                }

                                Label{
                                    Layout.preferredWidth: 40
                                    verticalAlignment: Text.AlignVCenter
                                    text: reccurenceDay
                                }

                                Label{
                                    id: d
                                    Layout.fillWidth: true
                                    verticalAlignment: Text.AlignVCenter
                                    text: description
                                    wrapMode: Label.Wrap
                                }
                            }
                        }

                    }
                }
                Item {
                    id: pastMaintenanceTab
                    Rectangle{
                        id: pastTitleRect
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: pastMheaderRow.height + 6
                        color: Style.primary
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
                        model: tukDetailModel.pastMaintenanceListModel
                        clip: true

                        delegate: ItemDelegate{
                            width: pastMaintenanceListView.width
                            //height: 30
                            contentItem: RowLayout{
                                id: rowLayout2
                                //anchors.left: parent.left
                                //anchors.right: parent.right
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
                Item {
                    id: versementTab

                    Rectangle{
                        id: depositHeaderRect
                        width: parent.width
                        height: depositHeaderRow.height + 6
                        color: Style.primary
                        anchors.top: parent.top
                        //anchors.topMargin: 4
                        anchors.left: depositListView.left
                        RowLayout{
                            id: depositHeaderRow
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 4
                            Label{
                                Layout.preferredWidth: 110
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Date"
                                color: Style.accent
                                font.bold: true
                            }
                            Label{
                                Layout.fillWidth: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Chauffeur"
                                color: Style.accent
                                font.bold: true
                            }

                            Label{
                                Layout.preferredWidth: 80
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Amount (Ar)"
                                color: Style.accent
                                font.bold: true
                            }
                            Label{
                                Layout.preferredWidth: 80
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Reste (Ar)"
                                color: Style.accent
                                font.bold: true
                            }
                        }
                    }

                    ListView{
                        id: depositListView
                        anchors.top: depositHeaderRect.bottom
                        anchors.right: parent.right
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        clip: true
                        model: tukDetailModel.depositListModel

                        delegate: ItemDelegate{
                            width: depositListView.width
                            height: 30

                            background: Rectangle{
                                width: depositListView.width
                                height: 28
                                anchors.verticalCenter: parent.verticalCenter
                                color: hasDepositLeft ? "#f79d65" : "white"
                            }

                            contentItem: RowLayout{
                                Label{
                                    Layout.preferredWidth: 110
                                    verticalAlignment: Text.AlignVCenter
                                    text: Qt.formatDate(depositDate, "ddd, dd MMM")
                                }
                                Label{
                                    Layout.fillWidth: true
                                    verticalAlignment: Text.AlignVCenter
                                    text: driverName
                                }
                                Label{
                                    Layout.preferredWidth: 80
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignHCenter
                                    text: amount
                                }

                                Label{
                                    Layout.preferredWidth: 80
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
    }

    Dialog{
        id: maintenanceFormDialog
        property int update_id
        property bool update
        function clearForm() {
            maintenanaceTypeCombo.editText = ""
            descriptionEdit.clear()
            scheduleDatePopup.selected_date = new Date()
            performedDatePopup.selected_date = new Date()
            reccurenceCheck.checkState = Qt.Unchecked
            reccurenceDaysSpin.value = 0
            costEdit.clear()
            finishCheck.checkState = Qt.Unchecked
            maintenanaceTypeCombo.currentIndex = -1
        }

        x: (root.width - width) / 2
        y: (root.height - height) / 2
        modal: true
        closePolicy: Popup.NoAutoClose
        //modality: Qt.ApplicationModal
        title: maintenanceFormDialog.update? "Modifier une maintenance": "Planifier une maintenance"
        contentItem: GridLayout {
            columnSpacing: 8
            rowSpacing: 8
            columns: 2
            ComboBox{
                id: maintenanaceTypeCombo
                Layout.preferredWidth: 150
                editable: true
                model: tukDetailModel.maintenanceTypeListModel
                textRole: "maintenanceType"
                currentIndex: -1
            }


            TextArea{
                id: descriptionEdit
                Layout.preferredWidth: 150
                Layout.maximumHeight: 100
                placeholderText: "Description"
                wrapMode: TextInput.Wrap
            }

            TextField{
                id: scheduleDateEdit
                Layout.preferredWidth: 150
                placeholderText: "Date prévue"
                text: Qt.formatDate(scheduleDatePopup.selected_date, "dd/MM/yyyy")
                //inputMask: "0000/00/00;_"
                readOnly: true

                onPressed: {
                    scheduleDatePopup.open()
                }
            }

            TextField{
                id: costEdit
                Layout.preferredWidth: 150
                placeholderText: "Cost"
            }

            CheckBox{
                id: reccurenceCheck
                text: "Récurrent"
            }

            SpinBox{
                id: reccurenceDaysSpin
                Layout.preferredWidth: 150
                enabled: reccurenceCheck.checked
                from: 0
                editable: true
            }


            CheckBox{
                id: finishCheck
                text: "Terminé?"
            }


            TextField{
                id: datePerformed
                enabled: finishCheck.checked
                Layout.preferredWidth: 150
                placeholderText: "Date d'exécution"
                text: Qt.formatDate(performedDatePopup.selected_date, "dd/MM/yyyy")
                //inputMask: "0000/00/00;_"
                readOnly: true

                onPressed: {
                    performedDatePopup.open()
                }
            }


            RowLayout{
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignRight
                Button{
                    text: "Annuler"
                    Material.foreground: Style.primary
                    flat: true
                    onClicked: maintenanceFormDialog.close()
                }

                Button{
                    text: "Enregistrer"
                    Material.foreground: Style.primary
                    flat: true
                    onClicked: {
                        if (maintenanceFormDialog.update) {
                            tukDetailModel.updateMaintenance(
                                maintenanceFormDialog.update_id,
                                {
                                    "maintenance_type": maintenanaceTypeCombo.editText,
                                    "description": descriptionEdit.text,
                                    "schedule_date": scheduleDatePopup.selected_date,
                                    "performed_date": performedDatePopup.selected_date,
                                    "reccuring": reccurenceCheck.checked,
                                    "reccurence": reccurenceDaysSpin.value,
                                    "cost": costEdit.text,
                                    "finished": finishCheck.checked
                                }
                            )
                        }

                        else{
                            tukDetailModel.addMaintenance(
                                {
                                    "maintenance_type": maintenanaceTypeCombo.editText,
                                    "description": descriptionEdit.text,
                                    "schedule_date": scheduleDatePopup.selected_date,
                                    "performed_date": performedDatePopup.selected_date,
                                    "reccuring": reccurenceCheck.checked,
                                    "reccurence": reccurenceDaysSpin.value,
                                    "cost": costEdit.text,
                                    "finished": finishCheck.checked
                                }
                            )
                        }


                        maintenanceFormDialog.clearForm()
                        maintenanceFormDialog.close()
                    }
                }
            }
        }
    }
    Dialog{
        id: confirmMaintenanceDeleteDialog
        property int maintenanceId
        property string maintenanceDate

        function confirm(maintenance_id, maintenance_date) {
            maintenanceId = maintenance_id
            maintenanceDate = maintenance_date
            confirmMaintenanceDeleteDialog.open()
        }

        title: "Supprimer maintenance"
        anchors.centerIn: parent
        contentItem: ColumnLayout{
            Text{
                //Layout.columnSpan: 2
                Layout.maximumWidth: 300
                wrapMode: Text.Wrap
                text: "Confirmer la suppression de maintenance du <b>" + confirmMaintenanceDeleteDialog.maintenanceDate + "</b>?"
            }
            RowLayout{
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight
                Button{
                    Layout.alignment: Qt.AlignRight
                    Material.foreground: Style.primary
                    flat: true
                    text: "Annuler"
                    onClicked: {
                        confirmMaintenanceDeleteDialog.close()
                    }
                }

                Button{
                    Layout.alignment: Qt.AlignRight
                    Material.foreground: Style.primary
                    flat: true
                    text: "Ok"
                    onClicked: {
                        tukDetailModel.removeMaintenance(confirmMaintenanceDeleteDialog.maintenanceId)
                        confirmMaintenanceDeleteDialog.close()
                    }
                }
            }
        }
    }

    DatePickerPopup{
        id: scheduleDatePopup
        anchors.centerIn: parent
        title: "Select schedule date"
    }

    DatePickerPopup{
        id: performedDatePopup
        anchors.centerIn: parent
    }

    Dialog{
        id: statusUpdateDialog
        title: "Change Tuc tuc status"
        anchors.centerIn: parent

        contentItem: ColumnLayout{
            ComboBox{
                id: statusCombo
                Layout.fillWidth: true
                model: ["active", "in_maintenance", "retired"]
                currentIndex: model.indexOf(tukDetailModel.tuktuk.status)
            }

            RowLayout{
                Layout.alignment: Qt.AlignRight
                Button{
                    Material.foreground: Style.primary
                    flat: true
                    text: "Annuler"
                    onClicked: {
                        statusUpdateDialog.close()
                    }
                }

                Button{
                    Material.foreground: Style.primary
                    flat: true
                    text: "Ok"
                    onClicked: {
                        tukDetailModel.updateStatus(tukDetailModel.tuktuk.id, statusCombo.currentText)
                        statusUpdateDialog.close()
                    }
                }
            }
        }

    }

    Dialog{
        id: confirmDeleteTukDialog
        property string tuktuk: ""
        x: (root.width - width) / 2
        y: (root.height - height) / 2
        title: "Supprimer un tuctuc"
        contentItem: ColumnLayout{
            Label {
                text: "Supprimer " + tukDetailModel.tuktuk.registrationNumber + " ?";
            }

            RowLayout{
                Layout.alignment: Qt.AlignRight
                Button{
                    text: "Annuler"
                    flat: true
                    Material.foreground: "#fca311"
                    onClicked: confirmDeleteTukDialog.close()
                }
                Button{
                    text: "Yah letsy eh!"
                    flat: true
                    Material.foreground: "#fca311"
                    onClicked: {
                        tukDetailModel.removeTukTuk(tukDetailModel.tuktuk.id)
                        uiController.goBack()
                        confirmDeleteTukDialog.close()
                    }
                }
            }
        }
    }

    Dialog{
        id: tukUpdateDialog
        modal: true
        closePolicy: Popup.NoAutoClose
        anchors.centerIn: parent
        title: "Update tuc tuc"
        contentItem: GridLayout{
            columns: 2
            rowSpacing: 4
            columnSpacing: 4
            TextField{
                id: numeroEdit
                placeholderText: "Numero plaque"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                text: tukDetailModel.tuktuk.registrationNumber
            }

            TextField{
                id: modelEdit
                placeholderText: "Model"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                text: tukDetailModel.tuktuk.model
            }



            TextField{
                id: phaseEdit
                placeholderText: "Phase"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                text: tukDetailModel.tuktuk.phase
            }

            TextField{
                id: dateChooser
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                placeholderText: "Date d'achat"
                text: Qt.formatDate(purchaseDateDialog.selected_date, "dd/MM/yyyy")
                readOnly: true
                onPressed: {
                    purchaseDateDialog.open()
                }
            }

            RowLayout{
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignRight
                Button{
                    flat: true
                    Material.foreground: Style.primary
                    text: "Annuler"
                    onClicked: {
                        tukUpdateDialog.close()
                    }
                }

                Button{
                    Layout.columnSpan: 2
                    //Layout.alignment: Qt.AlignHCenter
                    text: "Enregistrer"
                    flat: true
                    Material.foreground: Style.primary
                    onClicked: {
                        let data = {
                            "registrationNumber": numeroEdit.text,
                            "purchaseDate": purchaseDateDialog.selected_date,
                            "phase": phaseEdit.text,
                            "model": modelEdit.text
                        }
                        tukListModel.updateTukTuk(tukDetailModel.tuktuk.id,
                            data
                        )
                        tukDetailModel.updateCurrentTuk(data)
                        tukUpdateDialog.close()
                        numeroEdit.clear()
                        phaseEdit.clear()
                        modelEdit.clear()

                    }
                }
            }

        }

    }

    DatePickerPopup{
        id: purchaseDateDialog
        anchors.centerIn: parent
        selected_date: tukDetailModel.tuktuk.purchaseDate
    }
}
