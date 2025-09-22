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

    Canvas {
        id: canva1
        anchors.fill: parent
        onPaint: {
            console.log("onPaint");
            {
                const ctx = getContext("2d");
                ctx.fillStyle = "white";
                ctx.fillRect(0, 0, canva1.width, canva1.height);

                ctx.fillStyle = "#C7B7B7";
                ctx.fillRect(10, 10, canva1.width - 20, canva1.height - 20);
            }

            {
                const ctx = getContext("2d");
                ctx.beginPath()
                ctx.moveTo(30, 20);
                ctx.lineTo(30, canva1.height - 20);
                ctx.lineTo(canva1.width - 30, canva1.height - 20);
                console.log("onPaint", canva1.width - 20);
                ctx.stroke();
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
