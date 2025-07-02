#ifndef HK_KOMIKMAN_CBZ_HPP
#define HK_KOMIKMAN_CBZ_HPP

#include <KZip>

#include "archive.hpp"

/**
 * Read .cbz archives using KZip
 */
class Cbz final : public Archive {
  Q_OBJECT

 public:
  explicit Cbz(QString path, QObject* parent = nullptr);
  ~Cbz() = default;
};

#endif
