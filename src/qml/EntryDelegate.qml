import QtQuick
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami

Item {
  id: root

  width: Kirigami.Units.gridUnit * 12
  height: width * 1.4

  CoverImage {
    id: image

    anchors.fill: parent
    anchors.margins: Kirigami.Units.gridUnit * 0.5

    source: modelData.image
    coverHoverEnabled: true
  }

  Rectangle {
    id: gradient

    anchors.fill: image

    radius: image.radius

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
