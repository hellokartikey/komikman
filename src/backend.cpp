#include "backend.hpp"

#include <QDebug>

#include <libassert/assert.hpp>

using namespace Qt::Literals;

Backend::Backend(QObject* parent)
    : QObject(parent),
      m_library(u"/home/kartikey/HDD/Manga/local"_s) {}

const Entry::List& Backend::entries() const {
  return m_library.entries();
}

void Backend::openEntry(Entry* entry) {
  ASSERT(entry);
  m_entry = entry;
  m_entry->loadChapters();
  Q_EMIT entryChanged();
}

void Backend::openChapter(QString path) {
  m_chapter = Chapter::make(path);
  m_chapter->open();
  Q_EMIT chapterChanged();
}

Chapter* Backend::currentChapter() {
  ASSERT(m_chapter);
  return m_chapter.get();
}

#include "moc_backend.cpp"
