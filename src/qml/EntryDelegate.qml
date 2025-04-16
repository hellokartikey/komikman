import QtQuick
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami

Rectangle {
  id: root

  required property url image
  required property string title

  width: Kirigami.Units.gridUnit * 16
  height: Kirigami.Units.gridUnit * 22

  Rectangle {
    id: image

    anchors.centerIn: parent

    width: Kirigami.Units.gridUnit * 15
    height: Kirigami.Units.gridUnit * 20

    border {
      color: mouse.containsMouse ? Kirigami.Theme.highlightColor : "transparent"
      width: 1
    }

    Image {
      anchors {
        fill: parent
        margins: parent.border.width
      }

      source: root.image

      sourceSize {
        width: width
        height: height
      }
    }

    Rectangle {
      id: gradient

      anchors.fill: parent

      radius: root.radius

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

      onClicked: console.log(title)
    }
  }

  Kirigami.Heading {
    anchors {
      bottom: image.bottom
      left: image.left
      right: image.right
      bottomMargin: Kirigami.Units.gridUnit
      leftMargin: Kirigami.Units.gridUnit
      rightMargin: Kirigami.Units.gridUnit
    }

    width: image.width

    color: "white"
    elide: Text.ElideRight

    text: root.title
  }

  Controls.Button {
    anchors {
      top: image.top
      right: image.right
      topMargin: Kirigami.Units.gridUnit * 0.5
      rightMargin: Kirigami.Units.gridUnit * 0.5
    }

    icon.name: "media-playback-start-symbolic"
  }
}
