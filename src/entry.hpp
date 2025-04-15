#ifndef HK_KOMIKMAN_ENTRY_HPP
#define HK_KOMIKMAN_ENTRY_HPP

#include <QDir>
#include <QList>
#include <QObject>
#include <QUrl>

class Entry : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
  Q_PROPERTY(QUrl image READ image WRITE setImage NOTIFY imageChanged)

 public:
  explicit Entry(QString path, QObject* parent);

  const QString& title() const;
  void setTitle(QString title);
  Q_SIGNAL void titleChanged();

  const QUrl& image() const;
  void setImage(QUrl image);
  Q_SIGNAL void imageChanged();

 private:
  QDir m_path;
  QString m_title;
  QUrl m_image;
};

using EntryList = QList<Entry*>;

#endif
