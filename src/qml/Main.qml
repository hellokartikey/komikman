import org.kde.kirigami as Kirigami

import QtQuick

import Komikman

Kirigami.ApplicationWindow {
  width: 500
  height: 500

  title: "Komikman"

  visible: true

  pageStack.initialPage: Kirigami.ScrollablePage {
    title: "Library"

    GridView {
      clip: true

      cellWidth: Kirigami.Units.gridUnit * 16
      cellHeight: Kirigami.Units.gridUnit * 22

      model: Backend.entries
      delegate: EntryDelegate {}
    }
  }
}
