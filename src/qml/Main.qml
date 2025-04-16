import org.kde.kirigami as Kirigami

import QtQuick

import Komikman

Kirigami.ApplicationWindow {
  width: 500
  height: 500

  title: "Komikman"

  visible: true

  Connections {
    target: Backend
    function onEntryChanged() {
      if (Backend.entry) {
        pageStack.layers.push(entryPage)
      }
    }
  }

  pageStack.initialPage: Kirigami.ScrollablePage {
    title: "Library"

    GridView {
      clip: true

      cellWidth: Kirigami.Units.gridUnit * 16
      cellHeight: cellWidth * 1.4

      model: Backend.entries
      delegate: EntryDelegate {}
    }
  }

  Component {
    id: entryPage
    EntryPage {}
  }
}
