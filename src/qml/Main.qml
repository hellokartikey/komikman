import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Form

import QtQuick

import Komikman

Kirigami.ApplicationWindow {
  id: root

  width: 800
  height: 600

  minimumWidth: 500
  minimumHeight: 500

  title: "Komikman"

  visible: true

  globalDrawer: Kirigami.GlobalDrawer {
    isMenu: true

    actions: [
      Kirigami.Action {
        text: "Settings"
        icon.name: "settings-configure-symbolic"
        onTriggered: applicationWindow().pageStack.layers.push(settingsPage)
      },

      Kirigami.Action {
        text: "About"
        icon.name: "help-about-symbolic"
        onTriggered: applicationWindow().pageStack.layers.push(aboutPage)
      },

      Kirigami.Action {
        separator: true
        visible: ! Kirigami.Settings.isMobile
      },

      Kirigami.Action {
        text: "Quit"
        visible: ! Kirigami.Settings.isMobile
        icon.name: "application-exit-symbolic"
        onTriggered: Qt.quit()
      }
    ]
  }

  pageStack.initialPage: Kirigami.ScrollablePage {
    title: "Library"

    Flow {
      Repeater {
        model: Backend.entries
        delegate: EntryDelegate {}
      }
    }
  }

  Component {
    id: entryPage
    Entry {}
  }

  Component {
    id: settingsPage
    Settings {}
  }

  Component {
    id: aboutPage
    Form.AboutPage {
      aboutData: Config.aboutData
    }
  }
}
