import QtQuick
import QtQuick.Effects
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami

Item {
  id: root

  width: Kirigami.Units.gridUnit * 16
  height: width * 1.4

  Rectangle {
    id: entry_rect

    anchors {
      fill: parent
      margins: Kirigami.Units.gridUnit * 0.5
    }

    border {
      color: {
        if (mouse.containsMouse) {
          Kirigami.Theme.highlightColor
        } else {
          "transparent"
        }
      }
      width: 1
    }

    layer.enabled: true

    radius: Kirigami.Units.gridUnit * 0.5

    Image {
      id: image

      anchors {
        fill: parent
        margins: parent.border.width
      }

      source: modelData.image

      sourceSize {
        width: width
        height: height
      }

      layer {
        enabled: true
        effect: MultiEffect {
          maskSource: parent
          maskEnabled: true
        }
      }
    }

    Rectangle {
      id: gradient

      anchors.fill: parent

      radius: parent.radius

      gradient: Gradient {
        GradientStop {
          position: 0.8
          color: "transparent"
        }

        GradientStop {
          position: 1.0
          color: "black"
        }
      }
    }

    MouseArea {
      id: mouse

      anchors.fill: parent

      hoverEnabled: true
      cursorShape: Qt.PointingHandCursor

      onClicked: Backend.openEntry(modelData)
    }
  }

  Kirigami.Heading {
    anchors {
      bottom: entry_rect.bottom
      left: entry_rect.left
      right: entry_rect.right
      margins: Kirigami.Units.gridUnit
    }

    width: entry_rect.width

    color: "white"
    elide: Text.ElideRight

    text: modelData.title
  }

  Controls.Button {
    anchors {
      top: entry_rect.top
      right: entry_rect.right
      margins: Kirigami.Units.gridUnit * 0.5
    }

    icon.name: "media-playback-start-symbolic"
  }
}
