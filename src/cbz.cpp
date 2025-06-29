#include "cbz.hpp"

#include <ranges>

#include <QCollator>
#include <QDebug>

CbzChapter::CbzChapter(QString path, QObject* parent)
    : Chapter(path, parent),
      m_file(path),
      m_zip(&m_file) {}

CbzChapter::IOPtr CbzChapter::getFile(qsizetype index) const {
  return IOPtr(m_zip.directory()->file(m_pages[index])->createDevice());
}

void CbzChapter::open() {
  if (m_zip.isOpen()) {
    return;
  }

  m_zip.open(QFile::ReadOnly);
  m_file.reset();  // Reset cursor to the beginning

  m_pages = m_zip.directory()->entries();

  // Sort pages
  auto collator = QCollator{};
  collator.setNumericMode(true);
  std::ranges::sort(m_pages, collator);
}

qsizetype CbzChapter::length() const {
  return m_pages.size();
}

void CbzChapter::close() {
  m_zip.close();
  m_file.close();
}

QImage CbzChapter::get(qsizetype index) const {
  return QImage::fromData(getFile(index)->readAll());
}

#include "moc_cbz.cpp"
