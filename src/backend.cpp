#include "backend.hpp"

#include <libassert/assert.hpp>

#include "config.hpp"

using namespace Qt::Literals;

Backend::Backend(QObject* parent)
    : QObject(parent),
      m_library(u"/home/kartikey/HDD/Manga/local"_s) {
  Config::the();  // Instantiate config at startup
}

Backend* Backend::the() {
  static auto inst = Backend{};
  return &inst;
}

Backend* Backend::create(QQmlEngine*, QJSEngine*) {
  auto* ptr = ASSERT_VAL(Backend::the());
  QJSEngine::setObjectOwnership(ptr, QJSEngine::CppOwnership);
  return ptr;
}

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
  if (m_chapter && m_chapter->path() == path) {
    return;
  }

  m_chapter = Chapter::make(path);
  m_chapter->open();
  Q_EMIT chapterChanged();
}

void Backend::openChapterIndex(int index) {
  openChapter(ASSERT_VAL(m_entry)->chapterPaths().at(index));
}

Chapter* Backend::currentChapter() {
  ASSERT(m_chapter);
  return m_chapter.get();
}

#include "moc_backend.cpp"
