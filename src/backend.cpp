#include "backend.hpp"

#include <QDebug>

using namespace Qt::Literals;

Backend::Backend(QObject* parent)
    : QObject(parent),
      m_library(u"/home/kartikey/HDD/Manga/local"_s) {}

const EntryList& Backend::entries() const {
  return m_library.entries();
}

void Backend::openEntry(Entry* entry) {
  if (!entry) {
    return;
  }

  m_entry = entry;
  m_entry->loadChapters();
  Q_EMIT entryChanged();
}

void Backend::closeEntry() {
  if (!m_entry) {
    return;
  }

  m_entry = nullptr;
}

void Backend::openChapter(Chapter* chapter) {
  if (!chapter) {
    return;
  }

  m_chapter = chapter;
  m_chapter->open();
  Q_EMIT chapterChanged();
}

void Backend::closeChapter() {
  if (!m_chapter) {
    return;
  }

  m_chapter->close();
  m_chapter = nullptr;
  Q_EMIT chapterChanged();
}

#include "moc_backend.cpp"
