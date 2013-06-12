import QtQuick 2.1
import QtQuick.Compositor 1.0
import Compositor 1.0

Compositor {

    id: compositor

    Component.onCompleted: showFullScreen()

    Grid {
        id: grid
        anchors.fill: parent
        spacing: 50
        columns: 4
        rows: 3

        Repeater {
            model: compositor.model

            WaylandSurfaceItem {
                id: surfaceItem
                surface: model.display
                scale: 0.33

                states: [
                    State {
                        name: "open"
                        ParentChange { target: surfaceItem; parent: compositor.contentItem }
                        PropertyChanges { target: surfaceItem; scale: 1 }
                    }
                ]

                transitions: [
                    Transition {
                        to: "open"
                        SequentialAnimation {
                            NumberAnimation {
                                target: surfaceItem; properties: "x,y,width,height"; duration: 1000
                            }
                            ScriptAction { script: compositor.setDirectRenderSurface(model.display) }
                        }
                    },
                    Transition {
                        from: "open"
                        SequentialAnimation {
                            ScriptAction { script: compositor.setDirectRenderSurface(null) }
                            NumberAnimation {
                                target: surfaceItem; properties: "x,y,width,height"; duration: 1000
                            }
                        }
                    }
                ]

                MouseArea {
                    anchors { fill: parent }
                    height: 50
                    onClicked: surfaceItem.state = (surfaceItem.state == "open") ? "" : "open";
                }
            }
        }
    }

}
