import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects
import TukTrack
import "../Components"


Page {
    id: root
    property bool expandForm
    function confifmRetireDriver(driverName) {
        confirmRetireDialog.driverName = driverName
        confirmRetireDialog.open()
    }

    function confirmDeleteDriver(driverName) {
        confirmDeleteDialog.driverName = driverName
        confirmDeleteDialog.open()
    }

    background: Rectangle{
        id: bg
        anchors.fill: parent
        color: "transparent"
    }

    Material.background: "#ffffff"
    header: ToolBar{
        Material.primary:  "white"
        //Material.elevation: 5
        RowLayout{
            anchors.fill: parent
            spacing: 20

            Label{
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignLeft
                Layout.fillWidth: true
                text: "Chauffeurs"
                font.bold: true
                font.pointSize: 16
                leftPadding: 8
                color: "#023047"
            }
            ToolButton{
                text: "\uf067"
                font.family: Style.webFont
                font.bold: true
                font.pointSize: 14
                onClicked: {
                    expandForm = !expandForm
                    driverForm.updatingDriver = false
                }
            }
        }
    }

    Rectangle{
        id: driverForm
        property bool updatingDriver
        //height: 0
        //color: "red"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        width: parent.width
        anchors.bottomMargin: 4
        GridLayout{
            id: formLayout
            anchors.fill: parent
            columns: 2
            visible: expandForm
            Text{
                text: driverForm.updatingDriver ? "Modifier chaufeur" : "Ajouter chauffeur"
                Layout.alignment: Qt.AlignHCenter
                Layout.columnSpan: 2
            }

            TextField{
                id: lastNameEdit
                placeholderText: "Nom"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }

            TextField{
                id: firstNameEdit
                placeholderText: "Prenom"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }



            TextField{
                id: idNumberEdit
                placeholderText: "CIN"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                validator: RegularExpressionValidator{
                    regularExpression: /[0-9]{12}/
                }
            }

            TextField{
                id: phoneNumberEdit
                placeholderText: "Phone Number"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                validator: RegularExpressionValidator{
                    regularExpression: /\d{10}/
                }
            }

            TextField{
                id: startDate
                placeholderText: "Start Date"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                readOnly: true
                text: Qt.formatDate(startDateDialod.selected_date, "dd/MM/yyyy")
                onPressed: startDateDialod.open()
            }

            ComboBox{
                id: shiftCombo
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                model: ["Jour", "Nuit"]
            }

            ComboBox{
                id: tukTuk
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
                model: tukListModel
                textRole: "plateNumber"
            }

            Button{
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignHCenter
                flat: true
                Material.foreground: Style.primary
                text: "Enregistrer"
                onClicked: {
                    if (driverForm.updatingDriver) {
                        driverListModel.updateDriver(driverDetail.driver.id, driverDetail.driverSetting.id,
                        {
                            "lastName": lastNameEdit.text,
                            "firstName": firstNameEdit.text,
                            "idNumber": idNumberEdit.text,
                            "phoneNumber": phoneNumberEdit.text,
                            "shift": shiftCombo.currentIndex === 0? "day" : "night",
                            "date_start": startDateDialod.selected_date,
                            "tuktukId": tukListModel.tukIdOf(tukTuk.currentText)
                        })
                    }
                    else {
                        driverListModel.addDriver(
                            {
                                "lastName": lastNameEdit.text,
                                "firstName": firstNameEdit.text,
                                "idNumber": idNumberEdit.text,
                                "phoneNumber": phoneNumberEdit.text,
                                "shift": shiftCombo.currentIndex === 0? "day" : "night",
                                "date_start": startDateDialod.selected_date,
                                "tuktuk": tukTuk.currentText
                            }
                        )
                    }

                    expandForm = false
                    lastNameEdit.clear()
                    firstNameEdit.clear()
                    idNumberEdit.clear()
                    phoneNumberEdit.clear()
                    driverForm.updatingDriver = false

                }
            }

        }

        states: [
            State {
                name: "collapsed"
                when: !expandForm
                PropertyChanges {
                    target: driverForm
                    height: 0
                }

                PropertyChanges{
                    target: formLayout
                    visible: false
                }
            },
            State {
                name: "expanded"
                when: expandForm
                PropertyChanges {
                    target: driverForm
                    height: 300
                }
                PropertyChanges{
                    target: formLayout
                    visible: true
                }
            }

        ]

        transitions: [
            Transition {
                from: "collapsed"
                to: "expanded"

                NumberAnimation {
                    target: driverForm
                    property: "height"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }


                PropertyAnimation {
                    target: formLayout
                    property: "visible"
                    duration: 200
                }
            },
            Transition {
                from: "expanded"
                to: "collapsed"

                NumberAnimation {
                    target: driverForm
                    property: "height"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        ]
    }

    ListView{
        id: driversListView
        anchors.top: driverForm.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: expandForm? 16 : 4
        anchors.leftMargin: 4
        anchors.rightMargin: 4
        anchors.bottomMargin: 4
        model: driverListModel
        clip: true

        delegate: ItemDelegate{
            id: itemDelegate
            width: driversListView.width
            height: 90

            DropShadow{
                source: contentRect
                anchors.fill: contentRect
                horizontalOffset: 0
                verticalOffset: 0
                radius: 4
                samples: 9
                color: "#aa000000"
            }

            background: Rectangle{
                id: contentRect
                radius: 4
                width: parent.width - 8
                height: parent.height - 8
                anchors.centerIn: parent
                anchors.margins: 8
                color: isActive ? "white" : "#dee2e6"
            }

                contentItem: RowLayout{
                    anchors.fill: parent
                    anchors.centerIn: parent
                    anchors.margins: 8
                    spacing: 6
                    ColumnLayout{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter
                        spacing: 6

                        Text {
                            text: lastName + " " + firstName
                            font.bold: true
                            font.pixelSize: 14
                        }

                        Text {
                            text: "\uf2c2" + " " + idNumber
                            color: "#adb5bd"
                            font.family: Style.webFont
                            font.pixelSize: 12
                        }

                        Text {
                            text: "\uf095" + " " + pnoneNumber
                            color: "#adb5bd"
                            font.family: Style.webFont
                            font.pixelSize: 12
                            Layout.alignment: Qt.AlignVCenter
                        }
                    }
                }

                onClicked: {
                    console.log("Id: " + id)
                    driverDetail.setCurrentDriverId(id)
                    depositSettingListModel.loadDriverDepositSetting(id)
                    depositListModel.setDriverId(id)
                    depositListModel.loadDeposit()
                    uiController.goDriverDetails()
                }

                onPressAndHold: {
                    driverDetail.setCurrentDriverId(id)
                    menu.currentIndex = -1
                    menu.currentDriverId = id
                    //let globalPos = driversListView.mapToGlobal(mouse.x, mouse.y)
                    //console.log("X: " + mouse.x + " y: " + mouse.y)
                    //console.log("Global_X: " + globalPos.x + " global_y: " + globalPos.y)
                    let glopalPos = mapToGlobal(pressX, pressY)
                    let itemPos = mapToItem(root, pressX, pressY)
                    //menu.x = glopalPos.x
                    //menu.y = glopalPos.y - contentRect.y
                    //menu.open()
                    menu.popup(itemPos.x, itemPos.y)
                }

            /*MouseArea{
                id: mouseArea
                anchors.fill: parent
                pressAndHoldInterval: 400
                enabled: !driverForm.updatingDriver
                //acceptedButtons: Qt.RightButton



            }*/
        }
    }

    Menu{
        id: menu
        property int currentDriverId
        MenuItem{
            text: "Modifier"
            onTriggered: {
                driverForm.updatingDriver = true
                firstNameEdit.text = driverDetail.driver.firstName
                lastNameEdit.text = driverDetail.driver.lastName
                idNumberEdit.text = driverDetail.driver.idNumber
                phoneNumberEdit.text = driverDetail.driver.phoneNumber
                startDateDialod.selected_date = driverDetail.driverSetting.startDate
                shiftCombo.currentIndex = driverDetail.driverSetting.shift === "Jour"? 0 : 1
                //shiftCombo.displayText
                tukTuk.currentIndex = tukListModel.indexOf(driverDetail.driverSetting.tukNumber)

                root.expandForm = true
            }
        }
        MenuItem{
            text: "Desactiver"
            enabled: driverDetail.driver.active
            onTriggered: {
                confifmRetireDriver(driverDetail.driver.firstName)
            }
        }

        MenuItem{
            text: "Reactiver"
            enabled: !driverDetail.driver.active
            onTriggered: {
                driverListModel.activateDriver(menu.currentDriverId)
            }
        }

        MenuItem{
            text: "Supprimer"
            onTriggered: {
                confirmDeleteDriver(driverDetail.driver.firstName)
            }
        }
    }

    Dialog{
        id: confirmRetireDialog
        property string driverName: ""
        x: (root.width - width) / 2
        y: (root.height - height) / 2
        title: "Desactiver un chauffeur"
        contentItem: ColumnLayout{
            Label {
                text: "Desactiver " + confirmRetireDialog.driverName + " ?";
            }

            RowLayout{
                Layout.alignment: Qt.AlignRight
                Button{
                    text: "Annuler"
                    flat: true
                    Material.foreground: "#fca311"
                    onClicked: confirmRetireDialog.close()
                }
                Button{
                    text: "Yah letsy eh!"
                    flat: true
                    Material.foreground: "#fca311"
                    onClicked: {
                        driverListModel.retireDriver(menu.currentDriverId)
                        confirmRetireDialog.close()
                    }
                }
            }
        }


    }

    Dialog{
        id: confirmDeleteDialog
        property string driverName: ""
        anchors.centerIn: parent
        title: "Supprimer un chauffeur"
        contentItem: ColumnLayout{
            Label {
                text: "Supprimer " + confirmDeleteDialog.driverName + " ?";
            }

            RowLayout{
                Layout.alignment: Qt.AlignRight
                Button{
                    text: "Annuler"
                    flat: true
                    Material.foreground: "#fca311"
                    onClicked: {
                        confirmDeleteDialog.close()
                    }
                }
                Button{
                    text: "Yah letsy eh!"
                    flat: true
                    Material.foreground: "#fca311"
                    onClicked: {
                        driverListModel.removeDriver(menu.currentDriverId)
                        confirmDeleteDialog.close()
                    }

                }
            }
        }
    }

    DatePickerPopup{
        id: startDateDialod
        anchors.centerIn: parent
    }

}
