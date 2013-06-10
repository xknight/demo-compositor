import QtQuick 2.1
import QtQuick.Compositor 1.0
import Compositor 1.0

Compositor {

    id: compositor

    ListView {
        anchors.fill: parent
        model: compositor.model
        onCountChanged: console.log('count', count)
        delegate: MouseArea {
            height: 100
            anchors { left: parent.left; right: parent.right }
            WaylandSurfaceItem {
                surface: model.display
            }
            onClicked: console.log('click!')
        }
    }

}
