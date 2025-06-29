#include "chapter.hpp"

#include <QFileInfo>

#include "cbz.hpp"
#include "image.hpp"

Chapter::Chapter(QString path, QObject* parent)
    : QObject(parent),
      m_title(QFileInfo{path}.baseName()) {}

Chapter::~Chapter() {
  close();
}

const QString& Chapter::title() const {
  return m_title;
}

void Chapter::open() {}

void Chapter::close() {}

qsizetype Chapter::length() const {
  return 0;
}

Chapter::Ptr Chapter::make(QString path, QObject* parent) {
  using namespace Qt::Literals;
  auto file = QFileInfo{path};

  if (file.completeSuffix() == u"cbz"_s) {
    return std::make_unique<CbzChapter>(path, parent);
  }

  return std::make_unique<Chapter>(path, parent);
}

QImage Chapter::cover() const {
  return get(0);
}

QImage Chapter::get(qsizetype) const {
  return QImage{};
}

QUrl Chapter::url(qsizetype index) const {
  const auto fmt = QString{u"image://%1/%2"};
  if (index < length()) {
    return QUrl(fmt.arg(IMAGE_PREFIX, QString::number(index)));
  }
  return QUrl{};
}

QUrl Chapter::coverUrl() const {
  return url(0);
}

qsizetype Chapter::pageNumber() const {
  return index() + 1;
}

qsizetype Chapter::index() const {
  return m_index;
}

bool Chapter::hasNext() const {
  // Must not go above length()
  return pageNumber() < length();
}

bool Chapter::hasPrev() const {
  // Must not go below 0
  return 0 < index();
}

QUrl Chapter::currentPage() const {
  return url(index());
}

void Chapter::nextPage() {
  if (hasNext()) {
    m_index++;
    Q_EMIT indexChanged();
  }
}

void Chapter::prevPage() {
  if (hasPrev()) {
    m_index--;
    Q_EMIT indexChanged();
  }
}

#include "moc_chapter.cpp"
