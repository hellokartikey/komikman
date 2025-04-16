import QtQuick

import org.kde.kirigami as Kirigami

Kirigami.ScrollablePage {
  id: root

  property var entry: Backend.entry

  title: entry.title

  Column {
    anchors.fill: parent

    spacing: Kirigami.Units.gridUnit

    Row {
      spacing: Kirigami.Units.gridUnit

      CoverImage {
        source: entry.image
        width: Kirigami.Units.gridUnit * 10
      }

      Column {
        spacing: Kirigami.Units.gridUnit * 0.25
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
      }
    }

    Grid {
      anchors {
        left: parent.left
        right: parent.right
      }

      spacing: Kirigami.Units.gridUnit * 0.5

      Repeater {
        model: entry.genre

        delegate: Kirigami.Chip {
          text: modelData
          closable: false
          checkable: false
        }
      }
    }

    Kirigami.Heading {
      text: "Description"
    }

    Text {
      text: entry.description
      width: parent.width
      wrapMode: Text.WordWrap
    }
  }
}
