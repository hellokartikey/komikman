import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Form

import QtQuick

import Komikman

Kirigami.ApplicationWindow {
  width: 800
  height: 600

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

  globalDrawer: Kirigami.GlobalDrawer {
    isMenu: true

    actions: [
      Kirigami.Action {
        text: "Settings"
        icon.name: "settings-configure-symbolic"
        onTriggered: console.log("settings")
      },

      Kirigami.Action {
        text: "About"
        icon.name: "help-about-symbolic"
        onTriggered: pageStack.layers.push(aboutPage)
      },

      Kirigami.Action { separator: true },

      Kirigami.Action {
        text: "Quit"
        icon.name: "application-exit-symbolic"
        onTriggered: Qt.quit()
      }
    ]
  }

  pageStack.initialPage: Kirigami.ScrollablePage {
    title: "Library"

    GridView {
      clip: true

      cellWidth: Kirigami.Units.gridUnit * 12
      cellHeight: cellWidth * 1.4

      model: Backend.entries
      delegate: EntryDelegate {}
    }
  }

  Component {
    id: entryPage
    EntryPage {}
  }

  Component {
    id: aboutPage
    Form.AboutPage {
      aboutData: Config.aboutData
    }
  }
}
