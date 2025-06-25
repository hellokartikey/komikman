import QtQuick
import QtQuick.Effects

import org.kde.kirigami as Kirigami

import Komikman

Rectangle {
  id: root

  required property url source
  property bool coverHoverEnabled: false

  height: width * 1.4
  radius: Kirigami.Units.gridUnit * 0.5
  layer.enabled: true

  border {
    color: {
      if (mouse.containsMouse && coverHoverEnabled) {
        Kirigami.Theme.highlightColor
      } else {
        if (coverHoverEnabled) {
          "transparent"
        } else {
          "black"
        }
      }
    }
    width: 1
  }

  Image {
    id: image

    anchors {
      fill: parent
      margins: parent.border.width
    }

    source: root.source

    sourceSize {
      width: image.width
      height: image.height
    }

    layer {
      enabled: true
      effect: MultiEffect {
        maskSource: parent
        maskEnabled: true
      }
    }
  }

  MouseArea {
    id: mouse

    anchors.fill: parent

    enabled: root.coverHoverEnabled
    hoverEnabled: root.coverHoverEnabled
    cursorShape: enabled ? Qt.PointingHandCursor : undefined

    onClicked: {
      Backend.openEntry(modelData)
      applicationWindow().pageStack.layers.push(entryPage)
    }
  }
}
