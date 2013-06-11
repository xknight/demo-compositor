import QtQuick 2.1
import QtQuick.Compositor 1.0
import Compositor 1.0

Compositor {

    id: compositor

    Component.onCompleted: showFullScreen()

    /*ListView {
        anchors.fill: parent
        model: compositor.model
        onCountChanged: console.log('count', count)
        delegate: MouseArea {
            height: 100
            anchors { left: parent.left; right: parent.right }
            Rectangle {
                anchors.fill: parent
                color: "#ccc"
            }
            WaylandSurfaceItem {
                anchors.fill: parent
                touchEventsEnabled: true
                surface: model.display
                resizeSurfaceToItem: true
            }
            onClicked: console.log('click!')
        }
    }*/

    Column {
        anchors.fill: parent
        spacing: 50
        Repeater {
            model: compositor.model

            WaylandSurfaceItem {
                surface: model.display

                Rectangle {
                    anchors { left: parent.left; right: parent.right; top: parent.bottom }
                    height: 50
                    color: "green";
                    MouseArea {
                        anchors.fill: parent
                        onClicked: compositor.setDirectRenderSurface(model.display)
                    }
                }
            }
        }
    }

}
