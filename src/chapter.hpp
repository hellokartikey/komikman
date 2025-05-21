#ifndef HK_KOMIKMAN_CHAPTER_HPP
#define HK_KOMIKMAN_CHAPTER_HPP

#include <QList>
#include <QObject>
#include <QString>

class Chapter : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString title MEMBER m_title CONSTANT)

 public:
  explicit Chapter(QString title, QObject* parent = nullptr);

  const QString& title() const;

 private:
  QString m_title;
};

using ChapterList = QList<Chapter*>;

#endif
