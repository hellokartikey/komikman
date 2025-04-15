#include "entry.hpp"

#include <QDebug>
#include <QTextStream>

#include <nlohmann/json.hpp>

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

    auto content = QTextStream(&details);
    auto text = content.readAll();

    auto json = json::json::parse(text.toStdString());

    if (auto title = json["title"]; title.is_string()) {
      m_title = QString::fromStdString(title.get<std::string>());
    }
  }
}

const QString& Entry::title() const {
  return m_title;
}

void Entry::setTitle(QString title) {
  if (m_title == title) {
    return;
  }

  m_title = title;
  Q_EMIT titleChanged();
}

const QUrl& Entry::image() const {
  return m_image;
}

void Entry::setImage(QUrl image) {
  if (m_image == image) {
    return;
  }

  m_image = image;
  Q_EMIT imageChanged();
}

#include "moc_entry.cpp"
