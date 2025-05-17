import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects
import QtQuick.Layouts
import TukTrack 1.0
import "../Components"

Page {
    id: root
    property bool expandForm
    Material.background: "#ffffff"
    //Material.accent: "#023047"
    function colorFor(tuk_status) {
        if (tuk_status === "active")
            return "#007200"

        else if(tuk_status === "in_maintenance")
            return "#ffc300"

        else
            return "#f95738"
    }

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
                text: "Tuc Tuc"
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
                }
            }
        }
    }

    Rectangle{
        id: tukForm
        //height: 0
        //color: "red"
        width: parent.width
        GridLayout{
            anchors.fill: parent
            columns: 2
            visible: expandForm
            Text{
                text: "Add TukTuk"
                Layout.alignment: Qt.AlignHCenter
                Layout.columnSpan: 2
            }

            TextField{
                id: numeroEdit
                placeholderText: "Numero plaque"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }

            TextField{
                id: modelEdit
                placeholderText: "Model"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
            }



            TextField{
                id: phaseEdit
                placeholderText: "Phase"
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 150
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

            Button{
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignHCenter
                text: "Enregistrer"
                flat: true
                Material.foreground: Style.primary
                onClicked: {
                    tukListModel.addTukTuk(
                        {
                            "registrationNumber": numeroEdit.text,
                            "purchaseDate": purchaseDateDialog.selected_date,
                            "phase": phaseEdit.text,
                            "model": modelEdit.text
                        }
                    )
                    expandForm = false
                    numeroEdit.clear()
                    phaseEdit.clear()
                    modelEdit.clear()

                }
            }

        }

        states: [
            State {
                name: "collapsed"
                when: !expandForm
                PropertyChanges {
                    target: tukForm
                    height: 0
                }
            },
            State {
                name: "expanded"
                when: expandForm
                PropertyChanges {
                    target: tukForm
                    height: 300
                }
            }
        ]

        transitions: [
            Transition {
                from: "collapsed"
                to: "expanded"

                NumberAnimation {
                    target: tukForm
                    property: "height"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            },
            Transition {
                from: "expanded"
                to: "collapsed"


                NumberAnimation {
                    target: tukForm
                    property: "height"
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        ]
    }

    ListView{
        id: tukListView
        anchors.top: tukForm.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 3
        clip: true
        model: tukListModel

        delegate: ItemDelegate{
            width: tukListView.width
            height: 90

            DropShadow{
                source: itemContentRect
                anchors.fill: itemContentRect
                horizontalOffset: 0
                verticalOffset: 0
                radius: 4
                samples: 9
                color: "#aa000000"
            }

            background: Rectangle{
                id: itemContentRect
                anchors.fill: parent
                anchors.margins: 4
                radius: 6
            }
            contentItem: RowLayout{
                    spacing: 4
                    anchors.fill: parent
                    anchors.margins: 8

                    Rectangle{
                        Layout.preferredHeight: 60
                        Layout.maximumWidth: 60
                        Layout.margins: 4
                        Layout.preferredWidth: height
                        Layout.alignment: Qt.AlignLeft
                        radius: width / 2
                        color: colorFor(status)
                        Label{
                            anchors.centerIn: parent
                            text: phase
                            font.bold: true
                            color: "white"
                            font.pixelSize: 16
                        }
                    }

                    Column{
                        Layout.fillWidth: true
                        //Layout.preferredWidth: 100
                        //Layout.maximumWidth: 100
                        //Layout.minimumWidth: 100
                        Layout.alignment: Qt.AlignLeft
                        spacing: 4
                        Text {
                            text: plateNumber + " | " + tukModel
                            font.bold: true
                        }
                        Text {
                            text: purchaseDate
                            color: "grey"
                        }

                        Text{
                            text: status
                            color: "grey"
                        }

                    }
                }

            onClicked: {
                tukDetailModel.setCurrentTuk(plateNumber)
                uiController.goTukDetail();
            }
        }
    }

    DatePickerPopup{
        id: purchaseDateDialog
        anchors.centerIn: parent
    }

}
