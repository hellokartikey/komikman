#ifndef HK_KOMIKMAN_BACKEND_HPP
#define HK_KOMIKMAN_BACKEND_HPP

#include <QtQmlIntegration/qqmlintegration.h>
#include <QObject>
#include <QString>

#include "library.hpp"

class Backend : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(EntryList entries READ entries CONSTANT)
  Q_PROPERTY(Entry* entry MEMBER m_entry NOTIFY entryChanged)

 public:
  explicit Backend(QObject* parent = nullptr);

  const EntryList& entries() const;

  Q_INVOKABLE void openEntry(Entry* entry);
  Q_SIGNAL void entryChanged();

 private:
  Library m_library;

  EntryList m_entries;
  Entry* m_entry = nullptr;
};

#endif
