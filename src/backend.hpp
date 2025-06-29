#ifndef HK_KOMIKMAN_BACKEND_HPP
#define HK_KOMIKMAN_BACKEND_HPP

#include <QtQmlIntegration/qqmlintegration.h>
#include <QObject>
#include <QString>

#include "chapter.hpp"
#include "library.hpp"

class Backend : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(Entry::List entries READ entries CONSTANT)
  Q_PROPERTY(Entry* entry MEMBER m_entry NOTIFY entryChanged)
  Q_PROPERTY(Chapter* chapter READ currentChapter NOTIFY chapterChanged)

 public:
  explicit Backend(QObject* parent = nullptr);

  const Entry::List& entries() const;

  Q_INVOKABLE void openEntry(Entry* entry);
  Q_SIGNAL void entryChanged();

  Q_INVOKABLE void openChapter(QString path);
  Q_INVOKABLE void openChapterIndex(int index);
  Q_SIGNAL void chapterChanged();

  Chapter* currentChapter();

 private:
  Library m_library;

  Entry* m_entry = nullptr;
  Chapter::Ptr m_chapter;
};

#endif
