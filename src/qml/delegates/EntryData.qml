import QtQuick

import org.kde.kirigami as Kirigami

Row {
  id: root

  required property url icon
  required property string text

  spacing: Kirigami.Units.gridUnit * 0.25

  Kirigami.Icon {
    id: icon

    source: root.icon
    roundToIconSize: true
    width: height
    height: heading.height
  }

  Kirigami.Heading {
    id: heading

    level: 2
    text: root.text
    type: Kirigami.Heading.Type.Secondary
  }
}
