import QtQuick
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Form

import Komikman

Form.FormCardPage {
  id: root

  title: "Chapters"
  visible: false

  actions: [
    Kirigami.Action {
      text: "Refresh"
      icon.name: "view-refresh"
      onTriggered: Backend.entry.refreshChapters()
    }
  ]

  Form.FormHeader {}

  Form.FormCard {
    Form.FormButtonDelegate {
      enabled: false
      text: "No Chapters"
      visible: Backend.entry.chapters.length == 0
    }

    Repeater {
      model: Backend.entry.chapters
      delegate: Form.FormButtonDelegate {
        required property int index
        required property string modelData

        text: modelData
        onClicked: {
          Backend.openChapterIndex(index)
          applicationWindow().pageStack.layers.push(chapterView)
        }
      }
    }
  }

  Component {
    id: chapterView
    Reader {}
  }
}
