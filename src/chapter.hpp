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

class Chapter : public QObject {
  Q_OBJECT

 public:
  using Ptr = std::unique_ptr<Chapter>;
  using List = QList<Chapter*>;

 private:
  Q_PROPERTY(QString title MEMBER m_title CONSTANT)
  Q_PROPERTY(QUrl currentPage READ currentPage NOTIFY indexChanged)
  Q_PROPERTY(qsizetype index MEMBER m_index NOTIFY indexChanged)
  Q_PROPERTY(qsizetype length READ length CONSTANT)

 public:
  explicit Chapter(QString path, QObject* parent = nullptr);
  virtual ~Chapter();

  const QString& title() const;

  virtual void open();
  virtual void close();

  virtual qsizetype length() const;

  virtual QImage get(qsizetype) const;
  QImage cover() const;

  Q_INVOKABLE QUrl url(qsizetype index) const;
  Q_INVOKABLE QUrl coverUrl() const;

  qsizetype index() const;
  Q_SIGNAL void indexChanged();

  QUrl currentPage() const;
  Q_INVOKABLE void nextPage();
  Q_INVOKABLE void prevPage();

  static Ptr make(QString path, QObject* parent = nullptr);

 private:
  QString m_title;
  qsizetype m_index = 0;
};

#endif
