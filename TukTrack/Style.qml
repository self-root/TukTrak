pragma Singleton
import QtQuick

Item {
    readonly property string robotFont: robotoF.name
    readonly property string webFont: webF.name
    readonly property string primary: "#fca311"
    readonly property string accent: "#003566"//"#023047"

    FontLoader{
            id: robotoF
            source: "qrc:/fonts/Roboto-Regular.ttf"
        }

        FontLoader{
            id: webF
            source: "qrc:/fonts/webfont.ttf"
        }
}
