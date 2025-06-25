import QtQuick

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Form

import Komikman

Form.FormCardPage {
  id: root

  title: "Chapters"
  visible: false

  Component.onDestruction: Backend.closeChapter();

  actions: [
    Kirigami.Action {
      text: "Refresh"
      icon.name: "view-refresh"
      onTriggered: Backend.entry.refresh_chapters()
    }
  ]

  Form.FormHeader {}

  Form.FormCard {
    Repeater {
      model: Backend.entry.chapters
      delegate: Form.FormButtonDelegate {
        text: modelData.title
        onClicked: {
          Backend.openChapter(modelData)
          applicationWindow().pageStack.layers.push(root.chapterView)
        }
      }
    }
  }

  Component {
    id: chapterView
    ChapterView {}
  }
}
