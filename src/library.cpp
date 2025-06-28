#include "library.hpp"

Library::Library(QString path, QObject* parent)
    : QObject(parent),
      m_root(path) {
  m_root.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
  for (const auto& entry : m_root.entryList()) {
    m_entries << new Entry(m_root.filePath(entry), this);
  }
}

const Entry::List& Library::entries() const {
  return m_entries;
}

const QDir& Library::root() const {
  return m_root;
}

#include "moc_library.cpp"
