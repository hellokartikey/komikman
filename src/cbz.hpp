#ifndef HK_KOMIKMAN_CBZ_HPP
#define HK_KOMIKMAN_CBZ_HPP

#include <QFile>

#include <KZip>

#include "chapter.hpp"

class CbzChapter : public Chapter {
  Q_OBJECT

 public:
  explicit CbzChapter(QString path, QObject* parent = nullptr);
  ~CbzChapter() = default;

  void open() override;
  void close() override;

 private:
  QFile m_file;
  KZip m_zip;
};

#endif
