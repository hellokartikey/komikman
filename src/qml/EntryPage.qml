import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami
import org.kde.kirigamiaddons.formcard as Form

Form.FormCardPage {
  id: detailsPage

  property var entry: Backend.entry

  title: entry.title
  visible: false

  Form.FormHeader {}

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

  Form.FormHeader {}

  Form.FormCard {
    Form.FormButtonDelegate {
      text: "Resume"
      icon.name: "media-playback-start-symbolic"
    }

    Form.FormDelegateSeparator {}

    Form.FormButtonDelegate {
      text: "Chapters"
      icon.name: "address-book-new-symbolic"

      onClicked: {
        if (! chaptersPage.visible) {
          applicationWindow().pageStack.layers.push(chaptersPage)
        }
      }
    }
  }

  Form.FormHeader {}

  Form.FormCard {
    Text {
      Layout.fillWidth: true
      Layout.margins: Kirigami.Units.gridUnit

      horizontalAlignment: Text.AlignJustify
      text: entry.description
      wrapMode: Text.WordWrap
    }
  }

  Component {
    id: chaptersPage
    Form.FormCardPage {

      title: "Chapters"
      visible: false

      actions: [
        Kirigami.Action {
          text: "Refresh"
          icon.name: "view-refresh"
          onTriggered: entry.refresh_chapters()
        }
      ]

      Form.FormHeader {}

      Form.FormCard {
        Repeater {
          model: entry.chapters
          delegate: Form.FormButtonDelegate {
            text: modelData.title
          }
        }
      }
    }
  }
}
