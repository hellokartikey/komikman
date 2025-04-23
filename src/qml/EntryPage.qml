import QtQuick
import QtQuick.Layouts
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
    clip: true

    RowLayout {
      spacing: Kirigami.Units.gridUnit

      Layout.margins: Kirigami.Units.gridUnit
      Layout.fillWidth: true

      CoverImage {
        source: entry.image
        width: Kirigami.Units.gridUnit * 10
      }

      ColumnLayout {
        spacing: Kirigami.Units.gridUnit * 0.5

        Layout.fillWidth: true

        Kirigami.Heading {
          Layout.fillWidth: true
          text: entry.title
          type: Kirigami.Heading.Type.Primary
          elide: Text.ElideRight
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

          Layout.fillWidth: true

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
    Text {
      Layout.fillWidth: true
      Layout.margins: Kirigami.Units.gridUnit

      horizontalAlignment: Text.AlignJustify
      text: entry.description
      wrapMode: Text.WordWrap
    }
  }
}
