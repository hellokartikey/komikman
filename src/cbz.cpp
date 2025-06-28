#include "cbz.hpp"

CbzChapter::CbzChapter(QString path, QObject* parent)
    : Chapter(path, parent),
      m_file(path),
      m_zip(&m_file) {}

void CbzChapter::open() {
  if (m_zip.isOpen()) {
    return;
  }

  m_zip.open(QFile::ReadOnly);
  m_file.reset();
}

void CbzChapter::close() {
  m_zip.close();
  m_file.close();
}

#include "moc_cbz.cpp"
