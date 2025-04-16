import QtQuick
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Form

Form.FormCardPage {
  id: root

  property var entry: Backend.entry

  title: entry.title

  actions: [
    Kirigami.Action {
      text: "Resume"
      icon.name: "media-playback-start-symbolic"
    }
  ]

  Form.FormHeader {
    title: "Details"
  }

  Form.FormCard {
    topPadding: Kirigami.Units.gridUnit
    bottomPadding: Kirigami.Units.gridUnit

    clip: true

    Row {
      spacing: Kirigami.Units.gridUnit

      anchors {
        centerIn: parent
        margins: Kirigami.Units.gridUnit
      }

      CoverImage {
        source: entry.image
        width: Kirigami.Units.gridUnit * 10
      }

      Column {
        spacing: Kirigami.Units.gridUnit * 0.5
        anchors {
          verticalCenter: parent.verticalCenter
        }

        Kirigami.Heading {
          text: entry.title
          type: Kirigami.Heading.Type.Primary
          level: 1
        }

        EntryData {
          icon: "im-user-symbolic"
          text: entry.author
        }

        EntryData {
          icon: "draw-brush-symbolic"
          text: entry.artist
        }

        EntryData {
          icon: "clock-symbolic"
          text: entry.status_string
        }

        Flow {
          spacing: Kirigami.Units.gridUnit * 0.25

          width: parent.width

          Repeater {
            model: entry.genre
            delegate: Kirigami.Chip {
              text: modelData
              icon.name: "tag-symbolic"
              closable: false
              checkable: false
            }
          }
        }
      }
    }
  }

  Form.FormHeader {
    title: "Description"
  }

  Form.FormCard {
    topPadding: Kirigami.Units.gridUnit
    bottomPadding: Kirigami.Units.gridUnit

    Form.FormSectionText {
      text: entry.description
      width: parent.width
      wrapMode: Text.WordWrap
    }
  }
}
