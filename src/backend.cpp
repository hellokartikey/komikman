#include "backend.hpp"

#include <QDebug>

using namespace Qt::Literals;

Backend::Backend(QObject* parent)
    : QObject(parent),
      m_library(u"/home/kartikey/HDD/Manga/local"_s) {
  m_entries = m_library.entries();
}

const EntryList& Backend::entries() const {
  return m_entries;
}

void Backend::openEntry(Entry* entry) {
  m_entry = entry;
  m_entry->load_chapters();
  Q_EMIT entryChanged();
}

#include "moc_backend.cpp"
