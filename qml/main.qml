import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window1
    width: 512
    height: 512
    visible: true
    title: qsTr("Qt5 Freq Viewer")

    FontLoader {
        id: customFont
        source: "qrc:/fonts/CruNattapong-XyOd.ttf"
        // onStatusChanged: {
        //     if (customFont.status === FontLoader.Ready) {
        //         console.log("Custom font loaded: " + customFont.name);
        //         // window1.font = customFont
        //     }
        // }
    }

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
        // font.pointSize: 24

        Timer {
            interval: 500
            running: true
            repeat: true
            onTriggered: {
                if (CanvasController.hasRequestRepaint) {
                    CanvasController.hasRequestRepaint = false;
                    canva1.requestPaint();
                }
            }
        }

        onPaint: {
            console.log("onPaint");
            const ctx = getContext("2d");

            // clear canvas
            ctx.fillStyle = "white";
            ctx.fillRect(0, 0, canva1.width, canva1.height);

            ctx.fillStyle = "#C7B7B7";
            ctx.fillRect(10, 10, canva1.width - 20, canva1.height - 20);

            ctx.beginPath()
            ctx.moveTo(30, 20);
            ctx.lineTo(30, canva1.height - 20);
            ctx.lineTo(canva1.width - 30, canva1.height - 20);
            console.log("onPaint", canva1.width - 20);
            ctx.stroke();

            ctx.font = "bold 24px \"" + customFont.name + "\""
            ctx.font.pointSize = 24
            ctx.fillStyle = "black";
            ctx.textAlign = "center";
            ctx.textBaseline = "middle";
            ctx.fillText(CanvasController.header1, canva1.width / 2, 30);
        }
    }

    // Text {
    //     id: helloText
    //     text: MyTextController.myText // Bind to the C++ property
    //     y: 30
    //     // anchors.horizontalCenter: page.horizontalCenter
    //     font.pointSize: 12
    //     font.bold: true
    // }
}
