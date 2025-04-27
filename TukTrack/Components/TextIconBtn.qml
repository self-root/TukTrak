import QtQuick
import ".."

Item {
    id: control
    property alias itemWidth: control.width
    property alias itemHeight: control.height
    property alias icon: iconTxt.text
    property alias iconColor: iconTxt.color
    property alias iconSize: iconTxt.font.pointSize
    property alias itemColor: a_rect.color
    property alias itemRadius: a_rect.radius
    signal clicked()

    Rectangle{
        id: a_rect
        anchors.fill: parent
        color: "transparent"
        Text {
            id: iconTxt
            anchors.centerIn: parent
            font.family: Style.webFont
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true

            onPressed: control.clicked()
        }
    }
}
