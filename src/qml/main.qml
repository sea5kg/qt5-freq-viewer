import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window1
    width: 512
    height: 512
    visible: true
    title: qsTr("Qt5 Freq Viewer")

    // FontLoader {
    //     id: customFont
    //     source: "qrc:/fonts/CruNattapong-XyOd.ttf"
    // }

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
            // console.log("onPaint");
            const ctx = getContext("2d");

            // clear canvas
            ctx.fillStyle = "white";
            ctx.fillRect(0, 0, canva1.width, canva1.height);

            ctx.fillStyle = "#C7B7B7";
            ctx.fillRect(10, 10, canva1.width - 20, canva1.height - 20);

            var paddingLeft = 100;
            var paddingRight = 30;
            var paddingTop = 50;
            var paddingBottom = 40;
            var width_dia = canva1.width - paddingLeft - paddingRight;
            var height_dia = canva1.height - paddingTop - paddingBottom;

            ctx.beginPath()
            ctx.moveTo(paddingLeft, paddingTop);
            ctx.lineTo(paddingLeft, canva1.height - paddingBottom);
            ctx.lineTo(canva1.width - paddingRight, canva1.height - paddingBottom);
            ctx.lineTo(canva1.width - paddingRight, paddingTop);
            ctx.lineTo(paddingLeft, paddingTop);
            ctx.stroke();

            // ctx.font = "bold 24px \"" + customFont + "\""
            ctx.font = "bold 24px \"AAA-Watin New\""
            // console.log(ctx.font)
            ctx.font.pointSize = 24
            ctx.fillStyle = "black";
            ctx.textAlign = "center";
            ctx.textBaseline = "middle";
            ctx.fillText(CanvasController.header1, canva1.width / 2, paddingTop - 20);

            var x_vals = CanvasController.getValuesX(canva1.width, canva1.height);
            var y_vals = CanvasController.getValuesY(canva1.width, canva1.height);
            if (x_vals.length == 0) {
                x_vals = [0];
            }
            if (y_vals.length == 0) {
                y_vals = [0];
            }

            // console.log(x_vals, y_vals);

            var y_min = y_vals[0];
            var y_max = y_vals[0];
            for (var i = 1; i < y_vals.length; i++) {
                y_max = Math.max(y_max, y_vals[i]);
                y_min = Math.min(y_min, y_vals[i]);
            }

            // console.log("y_max", y_max.toFixed(5))
            // console.log("y_min", y_min.toFixed(5))

            var y_length = y_max - y_min;
            y_max += y_length * 0.1; // add 10%
            y_min -= y_length * 0.1; // minus 10%
            y_length = y_max - y_min;

            // console.log("y_max", y_max)
            // console.log("y_min", y_min)

            var x_min = x_vals[0];
            var x_max = x_vals[x_vals.length - 1];
            var x_length = x_max - x_min;

            ctx.textAlign = "left";
            ctx.fillText("" + x_min + " Hz", paddingLeft, canva1.height - paddingBottom + 20);
            ctx.textAlign = "right";
            ctx.fillText("" + x_max + " Hz", canva1.width - paddingRight, canva1.height - paddingBottom + 20);
            ctx.textAlign = "right";
            ctx.fillText("" + y_max.toFixed(5), paddingLeft - 5, paddingTop + 12);
            ctx.fillText("" + y_min.toFixed(5), paddingLeft - 5, canva1.height - paddingBottom - 5);

            var x_k = width_dia / x_length;
            var y_k = height_dia / y_length;

            ctx.beginPath()
            var h = canva1.height - paddingBottom;
            for (var i = 0; i < x_vals.length; i++) {
                var f_x = paddingLeft + (x_k * (x_vals[i] - x_min));
                var f_y = h - (y_k * (y_vals[i] - y_min));
                // console.log("x,y = ", f_x, f_y)
                if (i == 0) {
                    ctx.moveTo(f_x, f_y);
                } else {
                    ctx.lineTo(f_x, f_y);
                }
            }
            ctx.stroke();
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
