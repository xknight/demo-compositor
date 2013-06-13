import QtQuick 2.1
import QtQuick.Compositor 1.0
import Compositor 1.0

Compositor {

    id: compositor

    visibility: Compositor.FullScreen

    Grid {
        id: grid
        property var transformOrigins: [
            Item.TopLeft, Item.Top, Item.TopRight,
            Item.Left, Item.Center, Item.Right,
            Item.BottomLeft, Item.Bottom, Item.BottomRight
        ]

        z: -1

        anchors.fill: parent

        Repeater {
            model: compositor.model
            MouseArea {
                id: mouseArea
                width: grid.width / 3
                height: grid.height / 3

                onClicked: surfaceItem.state = (surfaceItem.state == "open") ? "" : "open";

                Rectangle {
                    anchors.fill: parent
                    color: "red"
                    z: -2
                }

                WaylandSurfaceItem {
                    id: surfaceItem
                    surface: model.display
                    enabled: false
                    clientRenderingEnabled: (compositor.directRenderSurface == null)
                                            || (compositor.directRenderSurface == model.display)
                    onClientRenderingEnabledChanged: console.log(surfaceItem, clientRenderingEnabled)

                    transformOrigin: Item.Center
                    anchors.centerIn: parent
                    scale: 0.33

                    states: [
                        State {
                            name: "open"
                            ParentChange { target: surfaceItem; parent: compositor.contentItem; scale: 1 }
                        }
                    ]

                    transitions: [
                        Transition {
                            to: "open"
                            SequentialAnimation {
                                NumberAnimation { properties: "x,y,scale"; duration: 1000 }
                                ScriptAction { script: compositor.directRenderSurface = model.display }
                            }
                        },
                        Transition {
                            from: "open"
                            SequentialAnimation {
                                ScriptAction { script: compositor.directRenderSurface = null }
                                NumberAnimation { properties: "x,y,scale"; duration: 1000 }
                            }
                        }
                    ]
                }
            }
        }
    }
}
