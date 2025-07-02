#include "archive.hpp"

#include <QCollator>

Archive::Archive(KArchive* archive, QString path, QObject* parent)
    : Chapter(path, parent),
      m_file(path),
      m_archive(archive) {}

Archive::IOPtr Archive::getFile(qsizetype index) const {
  return IOPtr(m_archive->directory()->file(m_pages[index])->createDevice());
}

void Archive::open() {
  m_archive->open(QFile::ReadOnly);
  m_pages = m_archive->directory()->entries();

  // Sort pages
  auto collator = QCollator{};
  collator.setNumericMode(true);
  std::ranges::sort(m_pages, collator);
}

qsizetype Archive::length() const {
  return m_pages.size();
}

void Archive::close() {
  m_archive->close();
  m_file.close();
}

QImage Archive::get(qsizetype index) const {
  return QImage::fromData(getFile(index)->readAll());
}

#include "moc_archive.cpp"
