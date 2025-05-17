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
                text: driverDetail.driver.firstName
                font.bold: true
                font.pointSize: 16
                leftPadding: 8
                color: "#023047"
            }

            ToolButton{
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: 6
                text: "\uf095"
                font.family: Style.webFont
                font.bold: true
                font.pointSize: 14
                Material.foreground: "#023047"
                onClicked: {
                    driverDetail.callDriver()
                }
            }

        }
    }

        ColumnLayout{
            id: column
            anchors.fill: parent
            anchors.margins: 8
            spacing: 8
            Item{
                Layout.fillWidth: true
                Layout.preferredHeight: 120
                DropShadow{
                    source: driverRect
                    anchors.fill: driverRect
                    horizontalOffset: 0
                    verticalOffset: 0
                    radius: 4
                    samples: 9
                    color: "#aa000000"
                }

                Rectangle{
                    id: driverRect
                    width: parent.width
                    height: 120
                    radius: 4
                    color: "white"
                    Rectangle{
                        id: driverDetailTitleRect
                        width: parent.width
                        height: 30
                        color: Style.accent
                        Text {
                            id: driverDetailTitle
                            text: qsTr("Chauffeur")
                            color: "white"
                            anchors.centerIn: parent
                        }
                    }

                    GridLayout{
                        columns: 2
                        anchors.top: driverDetailTitleRect.bottom
                        anchors.right: parent.right
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        anchors.margins: 8
                        Label{
                            //Layout.column: 0
                            text: "Nom: " + driverDetail.driver.lastName
                        }

                        Label{
                            //Layout.column: 0
                            text: "Prénom: " + driverDetail.driver.firstName
                        }

                        Label{
                            //Layout.column: 0
                            text: "CIN: " + driverDetail.driver.idNumber
                        }

                        Label{
                            //Layout.column: 0
                            text: "Phone: " + driverDetail.driver.phoneNumber
                        }

                        Label{
                            //Layout.column: 1
                            text: "Tuc Tuc: " + driverDetail.driverSetting.tukNumber
                        }

                        Label{
                            //Layout.column: 1
                            text: "Shift: " + driverDetail.driverSetting.shift
                        }
                    }
                }
            }

            Item {
                id: depositSettingItem
                Layout.fillWidth: true
                Layout.preferredHeight: 200

                DropShadow{
                    source: depositSettingRect
                    anchors.fill: depositSettingRect
                    horizontalOffset: 0
                    verticalOffset: 0
                    radius: 6
                    samples: 13
                    color: "#aa000000"
                }

                Rectangle{
                    id: depositSettingRect
                    anchors.fill: depositSettingItem
                    radius: 4
                    //color: Style.primary
                    Rectangle{
                        id: depositSettingTitleRect
                        width: parent.width
                        height: 30
                        color: Style.accent
                        Text {
                            id: depositSettingTitle
                            text: qsTr("Deposit settings")
                            color: "white"
                            anchors.centerIn: parent
                        }
                    }

                    ToolButton{
                        id: addDepositSettingBtn
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.margins: 6
                        text: "\uf067"
                        font.family: Style.webFont
                        font.bold: true
                        font.pointSize: 14
                        onClicked: {
                            depositSettingPopup.open()
                        }
                    }

                    Rectangle{
                        height: 25
                        width: parent.width
                        anchors.top: depositSettingTitleRect.bottom
                        anchors.left: depositSettingHorizontalHeader.left
                        color: Style.primary
                        anchors.topMargin: 4
                    }

                    HorizontalHeaderView{
                        id: depositSettingHorizontalHeader
                        anchors.top: depositSettingTitleRect.bottom
                        anchors.left: depositSettingTable.left
                        anchors.topMargin: 4
                        //anchors.right: depositSettingTable.right
                        syncView: depositSettingTable
                        clip: true
                        delegate: ItemDelegate{
                            implicitWidth: 125
                            implicitHeight: 25
                            background: Rectangle{
                                anchors.fill: parent
                                color: Style.primary
                            }

                            Label{
                                anchors.centerIn: parent
                                text: modelData
                                color: Style.accent
                                font.bold: true
                            }
                        }
                    }

                    TableView{
                        id: depositSettingTable
                        anchors.top: depositSettingHorizontalHeader.bottom
                        anchors.right: addDepositSettingBtn.left
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        clip: true
                        model: depositSettingListModel

                        delegate: ItemDelegate{
                            implicitWidth: 125
                            implicitHeight: 30
                            text: modelData
                        }
                    }

                }
            }

            Item {
                id: depositListItem
                Layout.fillWidth: true
                Layout.fillHeight: true

                DropShadow{
                    source: depositListRect
                    anchors.fill: depositListRect
                    horizontalOffset: 0
                    verticalOffset: 0
                    radius: 6
                    samples: 13
                    color: "#aa000000"
                }

                Rectangle{
                    id: depositListRect
                    anchors.fill: depositListItem
                    radius: 4
                    //color: Style.primary
                    Rectangle{
                        id: depositListTitleRect
                        width: parent.width
                        height: 30
                        color: Style.accent
                        Text {
                            id: depositListTitle
                            text: qsTr("Deposit Lists")
                            color: "white"
                            anchors.centerIn: parent
                        }
                    }

                    ToolButton{
                        id: addDepositBtn
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.margins: 6
                        text: "\uf067"
                        font.family: Style.webFont
                        font.bold: true
                        font.pointSize: 14
                        enabled: driverDetail.driver.active
                        onClicked: {
                            addDepositPopup.updateDeposit = false
                            addDepositPopup.open()
                        }
                    }

                    /*Rectangle{
                        height: 25
                        width: parent.width
                        anchors.top: depositListTitleRect.bottom
                        anchors.left: headerRect.left
                        color: Style.primary
                        anchors.topMargin: 4
                    }*/

                    Rectangle{
                        id: headerRect
                        width: parent.width
                        height: 25
                        color: Style.primary
                        anchors.top: depositListTitleRect.bottom
                        anchors.topMargin: 4
                        anchors.left: depositListView.left
                        RowLayout{
                            anchors.fill: parent
                            Label{
                                Layout.preferredWidth: 120
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "Date"
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

                            Label{
                                Layout.fillWidth: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                text: "note"
                                color: Style.accent
                                font.bold: true
                            }
                        }

                    }

                    ListView{
                        id: depositListView
                        anchors.top: headerRect.bottom
                        anchors.right: parent.right
                        anchors.left: parent.left
                        anchors.bottom: addDepositBtn.top
                        clip: true
                        model: depositListModel
                        enabled: driverDetail.driver.active

                        delegate: SwipeDelegate{
                            width: depositListView.width
                            height: 30
                            swipe.right: Row {
                                anchors.right: parent.right
                                anchors.verticalCenter: parent.verticalCenter
                                height: parent.height - 2

                                Label {
                                    id: moveLabel
                                    text: "Modifier"
                                    color: "white"
                                    verticalAlignment: Label.AlignVCenter
                                    padding: 12
                                    height: parent.height

                                    SwipeDelegate.onClicked: {
                                        addDepositPopup.updateDeposit = true
                                        addDepositPopup.updateIndex = index
                                        depositAmountEdit.text = amount
                                        noteEdit.text = note
                                        depositDateChoserPopup.selected_date = depositDate
                                        addDepositPopup.open()
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

                                    SwipeDelegate.onClicked: depositListModel.removeDeposit(index)

                                    background: Rectangle {
                                        color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                                    }
                                }
                            }


                            background: Rectangle{
                                width: depositListView.width
                                height: 28
                                anchors.verticalCenter: parent.verticalCenter
                                color: hasDepositLeft ? "#f79d65" : "white"
                            }

                            contentItem: RowLayout{
                                //anchors.fill: parent
                                Label{
                                    Layout.preferredWidth: 120
                                    verticalAlignment: Text.AlignVCenter
                                    text: Qt.formatDate(depositDate, "ddd, dd MMM")
                                }
                                Label{
                                    Layout.preferredWidth: 80
                                    verticalAlignment: Text.AlignVCenter
                                    text: amount
                                }

                                Label{
                                    Layout.preferredWidth: 80
                                    verticalAlignment: Text.AlignVCenter
                                    text: rest
                                }

                                Label{
                                    Layout.fillWidth: true
                                    verticalAlignment: Text.AlignVCenter
                                    text: note
                                }
                            }
                        }
                    }
                }
            }
        }

    Popup{
        id: depositSettingPopup
        x: (root.width - width) / 2
        y: (root.height - height) / 2

        contentItem: ColumnLayout{
            Column{
                Layout.alignment: Qt.AlignHCenter
                ButtonGroup {
                    id: checkGroup
                    exclusive: false
                    checkState: parentBox.checkState
                }

                CheckBox{
                    id: parentBox
                    text: "Selectionner tous"
                    checkState: checkGroup.checkState
                }
                GridLayout{
                    columns: 2
                    columnSpacing: 4
                    rowSpacing: 4
                    CheckBox{
                        text: "Lundi"
                        ButtonGroup.group: checkGroup
                        //leftPadding: indicator.width
                        objectName: "Monday"
                    }
                    CheckBox{
                        text: "Mardi"
                        ButtonGroup.group: checkGroup
                        //leftPadding: indicator.width
                        objectName: "Tuesday"
                    }
                    CheckBox{
                        text: "Mercredi"
                        ButtonGroup.group: checkGroup
                        //leftPadding: indicator.width
                        objectName: "Wednesday"
                    }
                    CheckBox{
                        text: "Jeudi"
                        ButtonGroup.group: checkGroup
                        //leftPadding: indicator.width
                        objectName: "Thursday"
                    }
                    CheckBox{
                        text: "Vendredi"
                        ButtonGroup.group: checkGroup
                        //leftPadding: indicator.width
                        objectName: "Friday"
                    }
                    CheckBox{
                        text: "Samedi"
                        ButtonGroup.group: checkGroup
                        //leftPadding: indicator.width
                        objectName: "Saturday"
                    }
                    CheckBox{
                        text: "Dimanche"
                        ButtonGroup.group: checkGroup
                        //leftPadding: indicator.width
                        objectName: "Sunday"
                    }
                }


            }



            TextField{
                id: expectedAmountEdit
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                placeholderText: "Versement (Ar)"
                validator: RegularExpressionValidator{
                    regularExpression: /[0-9]+/
                }
            }

            Button{
                text: "Enregistrer"
                Layout.alignment: Qt.AlignHCenter
                Material.background: Style.primary
                Material.foreground: Style.accent
                onClicked: {
                    if (expectedAmountEdit.text)
                    {
                        var c = checkGroup.buttons
                        var days = []
                        for (var i = 0; i < 7; i++ ) {
                            if (c[i].checkState === 2)
                            {
                                days.push(c[i].objectName);
                            }
                        }
                        depositSettingListModel.addDepositSettings(driverDetail.driver.id, days, expectedAmountEdit.text);
                    }


                    depositSettingPopup.close()
                }
            }
        }
    }

    Popup{
        id: addDepositPopup
        x: (root.width - width) / 2
        y: (root.height - height) / 2
        modal: true
        closePolicy: Popup.NoAutoClose
        property bool updateDeposit
        property int updateIndex
        contentItem: ColumnLayout{
            spacing: 12
            anchors.margins: 12
            Text{
                text: addDepositPopup.updateDeposit ?  "Modifier Versement" : "Ajouter Versement"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
            }

            TextField{
                id: depositAmountEdit
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                placeholderText: "Versement (Ar)"
                validator: RegularExpressionValidator{
                    regularExpression: /[0-9]+/
                }
            }

            TextField{
                id: noteEdit
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                placeholderText: "Remarque"
            }

            TextField {
                id: depositDateChooser
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                placeholderText: "Date versement"
                readOnly: true
                text: Qt.formatDate(depositDateChoserPopup.selected_date, "dd/MM/yyyy")
                onPressed: {
                    depositDateChoserPopup.open()
                }

            }

            RowLayout{
                Layout.alignment: Qt.AlignRight
                Button{
                    text: "Annuler"
                    flat: true
                    Material.foreground: Style.primary
                    onClicked: {
                        addDepositPopup.close()
                    }
                }

                Button{
                    //Layout.alignment: Qt.AlignHCenter
                    text: "Enregistrer"
                    flat: true
                    Material.foreground: Style.primary
                    onClicked: {
                        if (depositAmountEdit.text)
                        {
                            if (addDepositPopup.updateDeposit) {
                                depositListModel.updateDeposit(addDepositPopup.updateIndex,
                                                               {
                                                                   "amount": depositAmountEdit.text,
                                                                   "note": noteEdit.text,
                                                                    "date": depositDateChoserPopup.selected_date
                                                               })
                            }
                            else {
                                depositListModel.addDeposit(driverDetail.driver.id,
                                           driverDetail.driverSetting.tukId,
                                           {
                                               "amount": depositAmountEdit.text,
                                               "note": noteEdit.text,
                                                "date": depositDateChoserPopup.selected_date
                                           })
                            }


                            depositAmountEdit.clear()
                            noteEdit.clear()
                        }
                        addDepositPopup.close()
                    }
                }
            }


        }
    }
    DatePickerPopup{
        id: depositDateChoserPopup
        anchors.centerIn: parent
    }
}
