#include "entry.hpp"

#include <ranges>

#include <QCollator>
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

  auto json = json::json({});

  if (m_path.exists(u"details.json"_s)) {
    auto details = QFile{m_path.filePath(u"details.json"_s)};
    details.open(QIODevice::ReadOnly | QIODevice::Text);
    auto text = details.readAll();
    json = json::json::parse(text.toStdString());
  }

  // Load individual fields
  m_title = QString::fromStdString(
      json.value<std::string>("title", m_title.toStdString()));

  m_description = QString::fromStdString(
      json.value<std::string>("description", "No Description"));

  m_author =
      QString::fromStdString(json.value<std::string>("author", "Unknown"));

  m_artist =
      QString::fromStdString(json.value<std::string>("artist", "Unknown"));

  m_genre = {};
  if (auto genres = json["genre"]; genres.is_array()) {
    for (const auto& genre : genres) {
      m_genre << QString::fromStdString(genre.get<std::string>());
    }
  }

  m_status = json.value("status", Unknown);
}

QString Entry::statusString() const {
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

bool Entry::isChaptersLoaded() const {
  return m_is_chapters_loaded;
}

void Entry::loadChapters() {
  if (!isChaptersLoaded()) {
    refreshChapters();
  }
}

void Entry::refreshChapters() {
  auto chapters_list = QStringList{};
  m_path.refresh();

  if (auto chapters = m_path.entryInfoList(); !chapters.empty()) {
    for (const auto& chapter : chapters) {
      if (chapter.baseName() == u"cover"_s) {
        continue;
      }

      if (chapter.fileName() == u"details.json"_s) {
        continue;
      }

      chapters_list << chapter.absoluteFilePath();
    }

    // Sort chapters
    auto collator = QCollator{};
    collator.setNumericMode(true);
    std::ranges::sort(chapters_list, collator);
  }

  m_chapters_path = chapters_list;
  m_is_chapters_loaded = true;
  Q_EMIT chaptersChanged();
}

QStringList Entry::chapterNames() const {
  auto list = QStringList{};

  for (auto chapter : m_chapters_path) {
    list << QFileInfo{chapter}.baseName();
  }

  return list;
}

QStringList Entry::chapterPaths() const {
  return m_chapters_path;
}

#include "moc_entry.cpp"
