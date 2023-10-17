/*
 * Copyright 2023 Snap One, LLC. All Rights Reserved.
*/

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import PerfModule 1.0

Window
{
    width: 480
    height: 800
    visible: true
    title: qsTr("Hello World")

    property var randSentences: ["Delegate", "Delegato", "Item", "Row",
        "Generic Title", "Big Title Text", "Really Really Huge Title Text",
        "MUSCULAR TEXT", "small text", "LIIIIIIIIIIIINEEEEEEE"]

    Rectangle
    {
        id: header
        width: parent.width
        height: 80

        color: "black"
        z: 1

        Loader
         {
            anchors.centerIn: parent

             sourceComponent: fpsCounterComponent

             width: 100
             height: 70

             active: useFpsCounter
         }

        Image
        {
            id: chevron
            source: "qrc:/arrow.svg"

            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            anchors.rightMargin: 30

            width: 70
            height: 70
            sourceSize: Qt.size(70, 70)

            rotation: 180

            visible: stackView.depth > 1

            MouseArea
            {
                anchors.fill: parent
                onClicked: stackView.pop()
            }
        }
    }

    Component
    {
        id: fpsCounterComponent
        FpsCounter
        {
            id: fps_text
            x:0
            y: 0;
            width: 100
            height: 70
            Text
            {
                anchors.centerIn: parent
                text: "fps: " + fps_text.fps.toFixed(2)
                color: "yellow"

                font.pixelSize: 30

                font.weight: Font.Bold
            }
        }
    }

    StackView
    {
        id: stackView
        focus: true
        background: Image
        {
            source: "qrc:/bg.svg"
            cache: false
        }

        initialItem: mainList

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header.bottom
    }

    Component
    {
        id: mainList

        ListView
        {
            id: list
            focus: true
            keyNavigationEnabled: true
            model: listSize
            spacing: 20

            highlightRangeMode: ListView.StrictlyEnforceRange

            Timer
            {
                interval: scrollSpeed

                repeat: list.currentIndex != list.count
                running: autoScroll

                onTriggered:
                {
                    if (autoScrollExit && list.currentIndex == list.count - 1)
                    {
                        Qt.quit()
                    }
                    list.incrementCurrentIndex();
                }
            }

            delegate: Rectangle
            {
                anchors.horizontalCenter: parent != null ? parent.horizontalCenter : undefined

                width: activeFocus ? 420 : 380
                height: 100

                color: "#121d36"
                radius: 30


                Keys.onReleased:
                {
                    if (event.key === Qt.Key_Return)
                    {
                        stackView.push(grid);
                    }
                }

                opacity: transparentDelegates && index % 2 == 0 ? 0.5 : 1

                Image
                {
                    id: icon
                    source: "qrc:/" + String(1 + (index % 10)) + ".svg";

                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.leftMargin: 20
                    asynchronous: true
                    sourceSize: Qt.size(32, 32)
                }

                Image
                {
                    id: chevron
                    source: "qrc:/arrow.svg"

                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.rightMargin: 20
                    asynchronous: true
                    sourceSize: Qt.size(32, 32)
                }

                Text
                {
                    id: title
                    text: randSentences[index % randSentences.length];

                    anchors.left: icon.right
                    anchors.right: chevron.left
                    anchors.top: parent.top

                    anchors.rightMargin: 20
                    anchors.leftMargin: 20
                    anchors.topMargin: 10

                    verticalAlignment: Text.AlignVCenter

                    color: "white"

                    font.pixelSize: 30
                    font.weight: Font.DemiBold
                    elide: Text.ElideRight
                }

                Text
                {
                    id: subtitle
                    text: randSentences[index % randSentences.length];

                    anchors.left: icon.right
                    anchors.right: chevron.left
                    anchors.top: title.bottom

                    anchors.topMargin: 10
                    anchors.rightMargin: 20
                    anchors.leftMargin: 20

                    color: "silver"

                    font.pixelSize: 22
                    font.weight: Font.Medium
                    elide: Text.ElideRight
                }
            }
        }
    }

    Component
    {
        id: grid
        GridView
        {
            focus: true
            model: 10000

            cellWidth: 146
            cellHeight: 183
            keyNavigationEnabled: true

            delegate: Item
            {
                width: 140
                height: 160

                Rectangle
                {
                    id: rect
                    width: parent.activeFocus ? 140 : 112
                    height: parent.activeFocus ? 140 : 112
                    color: "#121d36"

                    Image
                    {
                        id: chevron
                        source: "qrc:/" + String(1 + (index % 10)) + ".svg";
                        sourceSize: Qt.size(width, height);

                        anchors.centerIn: parent

                        width: 90
                        height: 90

                    }
                }

                Text
                {
                    text: randSentences[index % randSentences.length];

                    anchors.top: rect.bottom
                    anchors.topMargin: 15
                    width: 140
                    height: 30

                    verticalAlignment: Text.AlignVCenter

                    color: "white"

                    font.pixelSize: 12
                    font.weight: Font.DemiBold
                    elide: Text.ElideRight
                }
            }

            Keys.onReleased:
            {
                if (event.key === Qt.Key_Escape)
                {
                    stackView.pop();
                }
            }
        }
    }
}
