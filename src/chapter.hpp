#ifndef HK_KOMIKMAN_CHAPTER_HPP
#define HK_KOMIKMAN_CHAPTER_HPP

#include <QDebug>
#include <QImage>
#include <QList>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QtTypes>

#include <memory>

#include <archive.h>
#include <archive_entry.h>

/**
 * Handle for the open chapter.
 */
class Chapter : public QObject {
  Q_OBJECT

 public:
  using Ptr = std::unique_ptr<Chapter>;
  using List = QList<Chapter*>;
  using ArchivePtr = std::unique_ptr<archive, decltype(&archive_read_free)>;

 private:
  Q_PROPERTY(QString title READ title CONSTANT)
  Q_PROPERTY(QString path READ path CONSTANT)

  Q_PROPERTY(QUrl currentPage READ currentPage NOTIFY indexChanged)

  Q_PROPERTY(bool hasNext READ hasNext NOTIFY indexChanged)
  Q_PROPERTY(bool hasPrev READ hasPrev NOTIFY indexChanged)

  Q_PROPERTY(qsizetype pageNumber READ pageNumber NOTIFY indexChanged)
  Q_PROPERTY(qsizetype index MEMBER m_index NOTIFY indexChanged)

  Q_PROPERTY(qsizetype length READ length CONSTANT)

 public:
  explicit Chapter(QString path, QObject* parent = nullptr);
  ~Chapter() = default;

  QString title() const;
  QString path() const;

  ArchivePtr openArchive() const;

  qsizetype length() const;

  QImage get(qsizetype index) const;
  QImage cover() const;

  Q_INVOKABLE QUrl url(qsizetype index) const;
  Q_INVOKABLE QUrl coverUrl() const;

  qsizetype pageNumber() const;
  qsizetype index() const;
  Q_SIGNAL void indexChanged();

  bool hasNext() const;
  bool hasPrev() const;

  QUrl currentPage() const;
  Q_INVOKABLE void nextPage();
  Q_INVOKABLE void prevPage();

  static Ptr make(QString path, QObject* parent = nullptr);

 private:
  QString m_path;
  qsizetype m_index = 0;
  QStringList m_pages;
};

#endif
