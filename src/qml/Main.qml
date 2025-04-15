import org.kde.kirigami as Kirigami

import QtQuick

import Komikman

Kirigami.ApplicationWindow {
  width: 500
  height: 500

  title: "Komikman"

  visible: true

  pageStack.initialPage: Kirigami.Page {
    Text {
      anchors.centerIn: parent
      text: Backend.message
    }
  }
}
