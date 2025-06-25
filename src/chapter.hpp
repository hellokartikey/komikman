#ifndef HK_KOMIKMAN_CHAPTER_HPP
#define HK_KOMIKMAN_CHAPTER_HPP

#include <QList>
#include <QObject>
#include <QString>

class Chapter : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString title MEMBER m_title CONSTANT)

 public:
  explicit Chapter(QString path, QObject* parent = nullptr);
  virtual ~Chapter() = default;

  const QString& title() const;

  virtual void open() {}
  virtual void close() {}

  static Chapter* make(QString path, QObject* parent = nullptr);

 private:
  QString m_title;
};

using ChapterList = QList<Chapter*>;

#endif
