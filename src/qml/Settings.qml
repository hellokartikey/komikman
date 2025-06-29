import QtQuick

import org.kde.kirigamiaddons.formcard as Form

import Komikman

Form.FormCardPage {
  id: root

  title: "Settings"

  Form.FormHeader {
    title: "Interface"
  }

  Form.FormCard {
    Form.FormComboBoxDelegate {
      text: "Color Scheme"
      textRole: "display"
      displayText: Config.themeName
      model: Config.themes
      currentIndex: Config.theme
      onActivated: {
        Config.setTheme(currentIndex)
      }
    }
  }
}
