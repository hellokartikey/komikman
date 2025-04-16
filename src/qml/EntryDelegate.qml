import QtQuick
import QtQuick.Effects
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami

CoverImage {
  id: image

  required property var modelData

  source: modelData.image
  coverHoverEnabled: true

  width: Kirigami.Units.gridUnit * 16

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

    hoverEnabled: coverHoverEnabled
    cursorShape: Qt.PointingHandCursor

    onClicked: Backend.openEntry(modelData)
  }

  Kirigami.Heading {
    anchors {
      bottom: image.bottom
      left: image.left
      right: image.right
      margins: Kirigami.Units.gridUnit
    }

    width: image.width

    color: "white"
    elide: Text.ElideRight

    text: modelData.title
  }

  Controls.Button {
    anchors {
      top: image.top
      right: image.right
      margins: Kirigami.Units.gridUnit * 0.5
    }

    icon.name: "media-playback-start-symbolic"
  }
}
