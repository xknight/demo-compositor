import QtQuick 2.1
import QtQuick.Compositor 1.0
import Compositor 1.0

Compositor {

    id: compositor

    ListView {
        anchors.fill: parent
        model: compositor.model
        delegate: WaylandSurfaceItem {
            surface: model.displayRole
        }
    }

}
