#ifndef HK_KOMIKMAN_CBZ_HPP
#define HK_KOMIKMAN_CBZ_HPP

#include <memory>

#include <QFile>
#include <QIODevice>
#include <QString>
#include <QUrl>

#include <KZip>

#include "chapter.hpp"

class CbzChapter : public Chapter {
  Q_OBJECT

 public:
  using IOPtr = std::unique_ptr<QIODevice>;

 public:
  explicit CbzChapter(QString path, QObject* parent = nullptr);
  ~CbzChapter() = default;

  IOPtr getFile(qsizetype index) const;

  void open() override;
  void close() override;

  qsizetype length() const override;

  QImage get(qsizetype index) const override;

 private:
  QFile m_file;
  KZip m_zip;
  QStringList m_pages;
};

#endif
