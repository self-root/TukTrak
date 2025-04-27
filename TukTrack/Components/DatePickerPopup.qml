import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects

Popup{
    id: calendarPopup
    property date selected_date: new Date()
    property string format: 'dd/MM/yyyy'
    property date _temp_date: selected_date
    property alias title: popupTitle.text
    signal dateSelected(var date)
    modal: true
    closePolicy: Popup.NoAutoClose
    width: 260
    height: 380

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
    ColumnLayout {
        anchors.fill: parent
        Label{
            id: popupTitle
            text: "Select a date"
        }

        RowLayout {
            Layout.fillWidth: true



            Label {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignLeft
                text: _temp_date.toLocaleDateString(Qt.locale(), 'MMM yyyy')
                color: "black"
                font.pixelSize: 20
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log("clicked")
                        rectTumbl.visible = true
                    }
                }
            }

            RoundButton {
                Layout.alignment: Qt.AlignRight
                text: '<'
                onClicked: _temp_date = previous_month()
                flat: true
            }

            RoundButton {
                Layout.alignment: Qt.AlignRight
                text: '>'
                onClicked: _temp_date = next_month()
                flat: true
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
                            radius: width / 2
                            Text {
                                anchors.centerIn: parent
                                text: day
                                color: highlighted? "white" : "black"
                            }
                            color: highlighted ? "#fca311" : "white"
                            highlighted: day === _temp_date.getDate() && selected_date.getMonth() === _temp_date.getMonth() && selected_date.getFullYear() === _temp_date.getFullYear()
                            MouseArea{
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    const _date = _temp_date
                                    _date.setDate(day)
                                    _temp_date = _date
                                    selected_date = _temp_date
                                    //calendarPopup.dateSelected(selected_date)
                                    //calendarPopup.close()
                                }
                            }
                        }
                    }
                }
            }
        }

        RowLayout{
            Layout.alignment: Qt.AlignRight
            Button{
                Material.foreground: "#fca311"
                flat: true
                text: "Cancel"
                onClicked: calendarPopup.close()
            }

            Button{
                Material.foreground: "#fca311"
                flat: true
                text: "Ok"
                onClicked: {
                    calendarPopup.dateSelected(selected_date)
                    calendarPopup.close()
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
            //width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            Tumbler{
                id: monthTumbler
                model: ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
                currentIndex: calendarPopup.selected_date.getMonth()
            }

            Tumbler {
                id: yearTumbler
                property int start: 1900
                property int end: 2100
                model: yearModel
                visibleItemCount: 5
                wrap: false
                currentIndex: calendarPopup.selected_date.getFullYear() - start

            }
        }

        Button{
            text: "Ok"
            flat: true
            Material.foreground: "#fca311"
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

    ListModel {
            id: yearModel
        }

        Component.onCompleted: {
            for (var i = 1900; i <= 2100; i++) {
                yearModel.append({ year: i })
            }
        }

        onAboutToShow: {
            sync_calendar(selected_date)
        }
}


