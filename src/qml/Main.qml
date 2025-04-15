import org.kde.kirigami as Kirigami

import QtQuick

import Komikman

Kirigami.ApplicationWindow {
  width: 500
  height: 500

  title: "Komikman"

  visible: true

  pageStack.initialPage: Kirigami.Page {
    title: "Library"

    GridView {
      anchors.fill: parent

      clip: true

      cellWidth: 260
      cellHeight: 360

      model: Backend.entries

      delegate: Item {
        required property url image

        width: 260
        height: 360

        Image {
          anchors.centerIn: parent

          width: 250
          height: 350

          sourceSize {
            width: 250
            height: 350
          }

          source: image
        }
      }
    }
  }
}
