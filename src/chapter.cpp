#include "chapter.hpp"

#include <QCollator>
#include <QFileInfo>

#include "image.hpp"

Chapter::Chapter(QString path, QObject* parent)
    : QObject(parent),
      m_path(path) {
  auto ptr = openArchive();

  for (archive_entry* entry;
       archive_read_next_header(ptr.get(), &entry) == ARCHIVE_OK;) {
    m_pages << QString::fromLocal8Bit(archive_entry_pathname(entry));
  }

  // Sort pages
  auto collator = QCollator{};
  collator.setNumericMode(true);
  std::ranges::sort(m_pages, collator);
}

QString Chapter::title() const {
  return QFileInfo{m_path}.baseName();
}

QString Chapter::path() const {
  return m_path;
}

Chapter::ArchivePtr Chapter::openArchive() const {
  auto ptr = ArchivePtr(archive_read_new(), archive_read_free);

  archive_read_support_format_all(ptr.get());
  archive_read_support_filter_all(ptr.get());

  if (archive_read_open_filename(ptr.get(), m_path.toLocal8Bit().data(),
                                 10240) != ARCHIVE_OK) {
    qWarning() << archive_error_string(ptr.get());
  }

  return ptr;
}

qsizetype Chapter::length() const {
  return m_pages.length();
}

Chapter::Ptr Chapter::make(QString path, QObject* parent) {
  using namespace Qt::Literals;
  auto file = QFileInfo{path};
  return std::make_unique<Chapter>(path, parent);
}

QImage Chapter::cover() const {
  return get(0);
}

QImage Chapter::get(qsizetype index) const {
  auto ptr = openArchive();

  for (archive_entry* entry; !archive_read_next_header(ptr.get(), &entry);) {
    auto* pathname = archive_entry_pathname(entry);

    // Compare each entry with the indexed page
    if (m_pages[index].toLocal8Bit() == pathname) {
      auto buffer = QByteArray(archive_entry_size(entry), 0);
      archive_read_data(ptr.get(), buffer.data(), buffer.size());

      return QImage::fromData(std::move(buffer));
    }
  }

  return QImage{};
}

QUrl Chapter::url(qsizetype index) const {
  const auto fmt = QString{u"image://%1/%2"};
  if (index < length()) {
    return QUrl(fmt.arg(IMAGE_PREFIX, QString::number(index)));
  }
  return QUrl{};
}

QUrl Chapter::coverUrl() const {
  return url(0);
}

qsizetype Chapter::pageNumber() const {
  return index() + 1;
}

qsizetype Chapter::index() const {
  return m_index;
}

bool Chapter::hasNext() const {
  // Must not go above length()
  return pageNumber() < length();
}

bool Chapter::hasPrev() const {
  // Must not go below 0
  return 0 < index();
}

QUrl Chapter::currentPage() const {
  return url(index());
}

void Chapter::nextPage() {
  if (hasNext()) {
    m_index++;
    Q_EMIT indexChanged();
  }
}

void Chapter::prevPage() {
  if (hasPrev()) {
    m_index--;
    Q_EMIT indexChanged();
  }
}

#include "moc_chapter.cpp"
