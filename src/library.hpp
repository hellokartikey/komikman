#ifndef HK_KOMIKMAN_LIBRARY_HPP
#define HK_KOMIKMAN_LIBRARY_HPP

#include <QDir>
#include <QObject>

#include "entry.hpp"

class Library : public QObject {
  Q_OBJECT

  Q_PROPERTY(Entry::List entries READ entries NOTIFY entriesChanged)

 public:
  explicit Library(QString path, QObject* parent = nullptr);

  const Entry::List& entries() const;
  Q_SIGNAL void entriesChanged();

  const QDir& root() const;

 private:
  QDir m_root;
  Entry::List m_entries;
};

#endif
