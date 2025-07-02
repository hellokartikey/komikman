#ifndef HK_KOMIKMAN_ARCHIVE_HPP
#define HK_KOMIKMAN_ARCHIVE_HPP

#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QString>

#include <KArchive>

#include "chapter.hpp"

/**
 * Read formats supported by KArchive
 */
class Archive : public Chapter {
  Q_OBJECT

 public:
  using IOPtr = std::unique_ptr<QIODevice>;

 public:
  explicit Archive(KArchive* archive, QString path, QObject* parent = nullptr);
  virtual ~Archive() = default;

  IOPtr getFile(qsizetype index) const;

  void open() override;
  void close() override;

  qsizetype length() const override;

  QImage get(qsizetype index) const override;

 private:
  QFile m_file;
  QStringList m_pages;
  std::unique_ptr<KArchive> m_archive;
};

#endif
