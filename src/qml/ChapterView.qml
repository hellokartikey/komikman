import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami

import Komikman

Kirigami.Page {
  id: root

  title: Backend.chapter.title
  padding: 0

  footer: Controls.ToolBar {
    position: Controls.ToolBar.Footer

    RowLayout {
      anchors.centerIn: parent

      Controls.ToolButton {
        id: next

        enabled: Backend.chapter.hasNext
        icon.name: "arrow-left-symbolic"
        onClicked: Backend.chapter.nextPage()

        Shortcut {
          sequence: StandardKey.MoveToPreviousChar
          onActivated: next.click()
        }
      }

      Controls.Label {
        text: `${Backend.chapter.pageNumber} of ${Backend.chapter.length}`
      }

      Controls.ToolButton {
        id: prev

        enabled: Backend.chapter.hasPrev
        icon.name: "arrow-right-symbolic"
        onClicked: Backend.chapter.prevPage()

        Shortcut {
          sequence: StandardKey.MoveToNextChar
          onActivated: prev.click()
        }
      }
    }
  }

  Image {
    id: image

    anchors.fill: parent

    mipmap: true
    fillMode: Image.PreserveAspectFit
    source: Backend.chapter.currentPage
  }
}
