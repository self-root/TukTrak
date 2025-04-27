import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects
import ".."


Item {
    id: item
    property date selected_date: new Date()
    property string format: 'dd/MM/yyyy'
    property date _temp_date: selected_date
    property bool date_picker_trigger: false
    property alias popupX: calendarPopup.x
    property alias popupY: calendarPopup.y
    property alias popupW: calendarPopup.width
    property alias popupH: calendarPopup.height
    property var popupParent
    signal dateSelected(var date)
    width: 150
    height: 55

    function calcModel(start, end) {
        var tmp = [];
        if (start > end) {
            model = [];
            return;
        }
        for (var i = start; i <= end; i++) {
            tmp.push(i);
        }
        model = tmp;
    }

    function days_in_a_month(y, m) {
        return new Date(y, m + 1, 0).getDate()
    }

    function week_start(y, m) {
        return new Date(y, m, 1).getDay()
    }

    function sync_calendar(day) {
        const month = day.getMonth()
        const year = day.getFullYear()
        const total_days = days_in_a_month(year, month)
        const first_day = week_start(year, month)

        model.clear()
        for (let filler = 0; filler < first_day; filler++) {
            model.append({ day: 0 })
        }

        for (let i = 1; i <= total_days; i++) {
            model.append({ day: i })
        }
    }

    function next_month() {
        const _date = _temp_date
        _date.setMonth(_temp_date.getMonth() + 1)
        sync_calendar(_date)
        return _date
    }

    function previous_month() {
        const _date = _temp_date
        _date.setMonth(_temp_date.getMonth() - 1)
        sync_calendar(_date)
        return _date
    }

    Column {
        focus: true
        Keys.onPressed: {
            if (event.key === Qt.Key_Escape) {
                date_picker_trigger = false
            }
        }

        Row {
            TextField {
                id: date_field
                text: selected_date.toLocaleDateString(Qt.locale(), format)
                readOnly: true
                leftPadding: 28
                verticalAlignment: TextInput.AlignVCenter
                onPressed:{
                    sync_calendar(selected_date)
                    calendarPopup.open()
                }

                background: Rectangle{
                    id: bg
                    implicitHeight: 55
                    implicitWidth: 150

                    Item {
                        id: rectWraper
                        anchors.fill: parent
                        /*DropShadow{
                            anchors.fill: bgBox
                            source: bgBox
                            horizontalOffset: 0
                            verticalOffset: 0
                            radius: 2
                            color: date_field.focus ? Style.boxShadowActive : Style.boxShadow
                        }*/

                        Rectangle{
                            id: bgBox
                            width: parent.width
                            height: parent.height
                            anchors.bottom: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            border.color: date_field.focus ? "#023047" : "#d6d8d9"
                            color: "transparent"
                            radius: 4

                            TextIconBtn{
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                                itemWidth: 25
                                itemHeight: 40
                                iconColor: "#757575"
                                iconSize: 10
                                icon: "\uf073"
                            }


                        }
                    }
                }
            }
        }




        ListModel {
            id: yearModel
        }

        Component.onCompleted: {
            for (var i = 1900; i <= 2100; i++) {
                yearModel.append({ year: i })
            }
        }
    }

    Popup{
        id: calendarPopup
        width: 260
        height: 340
        //x: 0 - item.parent.parent.x
        //y: 0 - item.parent.parent.y
        x: (Screen.width - calendarPopup.width) / 2 - item.parent.parent.x * 2
        y: (Screen.height - calendarPopup.height) / 2 - item.parent.parent.y *2
        ColumnLayout {
            anchors.fill: parent


            RowLayout {
                Layout.fillWidth: true

                RoundButton {
                    text: '<'
                    onClicked: _temp_date = previous_month()
                }

                Label {
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignHCenter
                    text: _temp_date.toLocaleDateString(Qt.locale(), 'MMM yyyy')
                    color: "black"
                    font.pixelSize: 18
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("clicked")
                            rectTumbl.visible = true
                        }
                    }
                }

                Rectangle{

                }

                RoundButton {
                    Layout.alignment: Qt.AlignRight
                    text: '>'
                    onClicked: _temp_date = next_month()
                }
            }

            Grid {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 7
                rows: 7

                Repeater {
                    model: ['S', 'M', 'T', 'W', 'T', 'F', 'S']
                    delegate: Label {
                        width: 35
                        height: 35
                        color: "black"
                        horizontalAlignment: Text.AlignHCenter
                        text: modelData
                    }
                }

                Repeater {
                    model: ListModel { id: model }

                    delegate: DelegateChooser {
                        DelegateChoice {
                            roleValue: 0

                            delegate: Item {
                                width: 35
                                height: 35
                            }
                        }

                        DelegateChoice {
                            delegate: Rectangle {
                                property bool highlighted
                                width: 35
                                height: 35
                                Text {
                                    anchors.centerIn: parent
                                    text: day
                                    color: highlighted? "white" : "black"
                                }
                                color: highlighted ? "#2a395a" : "white"
                                highlighted: day === _temp_date.getDate() && selected_date.getMonth() === _temp_date.getMonth() && selected_date.getFullYear() === _temp_date.getFullYear()
                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked: {
                                        const _date = _temp_date
                                        _date.setDate(day)
                                        _temp_date = _date
                                        selected_date = _temp_date
                                        date_picker_trigger.checked = false
                                        item.dateSelected(selected_date)
                                        calendarPopup.close()
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        Rectangle{
            id: rectTumbl
            anchors.fill: parent
            visible: false
            color: "white"
            Row{
                id: tumbRow
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                Tumbler{
                    id: monthTumbler
                    model: ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
                    currentIndex: item.selected_date.getMonth()
                }

                Tumbler {
                    id: yearTumbler
                    property int start: 1900
                    property int end: 2100
                    model: yearModel
                    visibleItemCount: 5
                    wrap: false
                    currentIndex: item.selected_date.getFullYear() - start

                }
            }

            Button{
                text: "Ok"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: tumbRow.bottom
                onClicked: {
                    rectTumbl.visible = false
                    selected_date = new Date(yearTumbler.currentIndex + yearTumbler.start, monthTumbler.currentIndex, selected_date.getDay())
                    _temp_date = selected_date
                    sync_calendar(selected_date)
                }
            }


        }


    }
    Component.onCompleted: {
        console.log("Screen Height: " + Screen.height)
    }

}
