#ifndef HK_KOMIKMAN_CHAPTER_HPP
#define HK_KOMIKMAN_CHAPTER_HPP

#include <QDebug>
#include <QList>
#include <QObject>
#include <QString>

#include <memory>

class Chapter : public QObject {
  Q_OBJECT

 public:
  using Ptr = std::unique_ptr<Chapter>;
  using List = QList<Chapter*>;

 private:
  Q_PROPERTY(QString title MEMBER m_title CONSTANT)

 public:
  explicit Chapter(QString path, QObject* parent = nullptr);
  virtual ~Chapter() = default;

  const QString& title() const;

  virtual void open() {}
  virtual void close() {}

  static Ptr make(QString path, QObject* parent = nullptr);

 private:
  QString m_title;
};

#endif
