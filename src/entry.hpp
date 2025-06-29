#ifndef HK_KOMIKMAN_ENTRY_HPP
#define HK_KOMIKMAN_ENTRY_HPP

#include <QDir>
#include <QList>
#include <QObject>
#include <QUrl>

#include <nlohmann/json.hpp>

#include "chapter.hpp"

enum Status {
  Unknown = 0,
  Ongoing = 1,
  Completed = 2,
  Licensed = 3,
  PublishingFinished = 4,
  Cancelled = 5,
  OnHiatus = 6
};

NLOHMANN_JSON_SERIALIZE_ENUM(Status, {
                                         {Unknown, "0"},
                                         {Ongoing, "1"},
                                         {Completed, "2"},
                                         {Licensed, "3"},
                                         {PublishingFinished, "4"},
                                         {Cancelled, "5"},
                                         {OnHiatus, "6"},
                                     })

class Entry : public QObject {
  Q_OBJECT

 public:
  using List = QList<Entry*>;

 private:
  Q_PROPERTY(QString title MEMBER m_title CONSTANT)
  Q_PROPERTY(QString description MEMBER m_description CONSTANT)

  Q_PROPERTY(QString author MEMBER m_author CONSTANT)
  Q_PROPERTY(QString artist MEMBER m_artist CONSTANT)

  Q_PROPERTY(QStringList genre MEMBER m_genre CONSTANT)
  Q_PROPERTY(Status status MEMBER m_status CONSTANT)
  Q_PROPERTY(QString status_string READ statusString CONSTANT)

  Q_PROPERTY(QUrl image MEMBER m_image CONSTANT)

  Q_PROPERTY(QStringList chapters READ chapterNames NOTIFY chaptersChanged)

 public:
  Q_ENUM(Status)

  explicit Entry(QString path, QObject* parent);

  QString statusString() const;

  bool isChaptersLoaded() const;
  void loadChapters();
  Q_INVOKABLE void refreshChapters();
  Q_SIGNAL void chaptersChanged();

  QStringList chapterNames() const;
  QStringList chapterPaths() const;

 private:
  QDir m_path;

  QString m_title;
  QString m_description;

  QString m_author;
  QString m_artist;

  QStringList m_genre;
  Status m_status = Status::Unknown;

  QUrl m_image;

  QStringList m_chapters_path;
  bool m_is_chapters_loaded = false;
};

#endif
