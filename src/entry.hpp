#ifndef HK_KOMIKMAN_ENTRY_HPP
#define HK_KOMIKMAN_ENTRY_HPP

#include <QDir>
#include <QList>
#include <QObject>
#include <QUrl>

#include <nlohmann/json.hpp>

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

  Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged)
  Q_PROPERTY(QString description MEMBER m_description NOTIFY descriptionChanged)

  Q_PROPERTY(QString author MEMBER m_author NOTIFY authorChanged)
  Q_PROPERTY(QString artist MEMBER m_artist NOTIFY artistChanged)

  Q_PROPERTY(QStringList genre MEMBER m_genre NOTIFY genreChanged)
  Q_PROPERTY(Status status MEMBER m_status NOTIFY statusChanged)
  Q_PROPERTY(QString status_string READ status_string NOTIFY statusChanged)

  Q_PROPERTY(QUrl image MEMBER m_image NOTIFY imageChanged)

 public:
  Q_ENUM(Status)

  explicit Entry(QString path, QObject* parent);

  QString status_string() const;

 Q_SIGNALS:
  void titleChanged();
  void descriptionChanged();

  void authorChanged();
  void artistChanged();

  void genreChanged();
  void statusChanged();

  void imageChanged();

 private:
  QDir m_path;

  QString m_title;
  QString m_description;

  QString m_author;
  QString m_artist;

  QStringList m_genre;
  Status m_status = Status::Unknown;

  QUrl m_image;
};

using EntryList = QList<Entry*>;

#endif
