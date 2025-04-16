import QtQuick

import org.kde.kirigami as Kirigami

Kirigami.ScrollablePage {
  id: root

  title: Backend.entry.title

  Column {
    anchors.fill: parent

    Kirigami.Heading {
      text: "Description"
    }

    Text {
      text: Backend.entry.description
      width: parent.width
      wrapMode: Text.WordWrap
    }
  }
}
