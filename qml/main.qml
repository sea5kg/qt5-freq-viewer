import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    width: 512
    height: 512
    visible: true
    title: qsTr("QML Menu with C++ Actions")

    // color: "lightgray"

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Open...")
                onTriggered: MenuController.performActionOpen() // Call C++ method
            }
            MenuItem {
                text: qsTr("Close")
                onTriggered: MenuController.performActionClose() // Call C++ method
            }
        }
    }

    Text {
        id: helloText
        text: myTextController.myText // Bind to the C++ property
        y: 30
        // anchors.horizontalCenter: page.horizontalCenter
        font.pointSize: 12
        font.bold: true
    }
}
