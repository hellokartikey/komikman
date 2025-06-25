import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami

import Komikman

Kirigami.Page {
  id: root

  title: Backend.chapter.title

  Component.onDestruction: Backend.closeChapter()
}
