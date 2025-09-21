import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    width: 512
    height: 512
    visible: true
    // color: "lightgray"

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem { text: "Open..." }
            MenuItem { text: "Close" }
        }
        // Menu {
        //     title: "Edit"
        //     MenuItem { text: "Cut" }
        //     MenuItem { text: "Copy" }
        //     MenuItem { text: "Paste" }
        // }
    }

    Text {
        id: helloText
        text: "Hello world!"
        y: 30
        // anchors.horizontalCenter: page.horizontalCenter
        font.pointSize: 24
        font.bold: true
    }
}
