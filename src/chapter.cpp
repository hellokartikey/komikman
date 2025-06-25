#include "chapter.hpp"

#include <QFileInfo>

#include "cbz.hpp"

Chapter::Chapter(QString path, QObject* parent)
    : QObject(parent),
      m_title(QFileInfo{path}.baseName()) {}

const QString& Chapter::title() const {
  return m_title;
}

Chapter* Chapter::make(QString path, QObject* parent) {
  using namespace Qt::Literals;
  auto file = QFileInfo{path};

  if (file.completeSuffix() == u"cbz"_s) {
    return new CbzChapter(path, parent);
  }

  return new Chapter(path, parent);
}
