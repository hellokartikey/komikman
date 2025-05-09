#include "entry.hpp"

#include <QDebug>
#include <QTextStream>

#include <libassert/assert.hpp>

namespace json = nlohmann;
using namespace Qt::Literals;

const auto COVER_FILTER = QStringList{u"cover.*"_s};

Entry::Entry(QString path, QObject* parent)
    : QObject(parent),
      m_path(path) {
  m_title = m_path.dirName();

  m_path.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
  if (auto covers = m_path.entryList(COVER_FILTER); !covers.isEmpty()) {
    m_image = QUrl::fromLocalFile(m_path.filePath(covers.first()));
  }

  if (m_path.exists(u"details.json"_s)) {
    auto details = QFile{m_path.filePath(u"details.json"_s)};
    details.open(QIODevice::ReadOnly | QIODevice::Text);
    auto text = details.readAll();
    auto json = json::json::parse(text.toStdString());

    // Load individual fields
    if (auto title = json["title"]; title.is_string()) {
      m_title = QString::fromStdString(title.get<std::string>());
    }

    if (auto description = json["description"]; description.is_string()) {
      m_description = QString::fromStdString(description.get<std::string>());
    }

    if (auto author = json["author"]; author.is_string()) {
      m_author = QString::fromStdString(author.get<std::string>());
    }

    if (auto artist = json["artist"]; artist.is_string()) {
      m_artist = QString::fromStdString(artist.get<std::string>());
    }

    if (auto genres = json["genre"]; genres.is_array()) {
      for (const auto& genre : genres) {
        m_genre << QString::fromStdString(genre.get<std::string>());
      }
    }

    if (auto status = json["status"]; status.is_string()) {
      m_status = status.get<Status>();
    }
  }
}

QString Entry::status_string() const {
  using namespace Qt::Literals;

  switch (m_status) {
    case Unknown:
      return u"Unknown"_s;
    case Ongoing:
      return u"Ongoing"_s;
    case Completed:
      return u"Completed"_s;
    case Licensed:
      return u"Licensed"_s;
    case PublishingFinished:
      return u"Publishing Finished"_s;
    case Cancelled:
      return u"Cancelled"_s;
    case OnHiatus:
      return u"On Hiatus"_s;
    default:
      UNREACHABLE();
  }
}

#include "moc_entry.cpp"
