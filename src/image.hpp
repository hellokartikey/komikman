#ifndef HK_KOMIKMAN_IMAGE_HPP
#define HK_KOMIKMAN_IMAGE_HPP

#include <QQuickImageProvider>
#include <QString>

inline const auto IMAGE_PREFIX = QString{u"page"};

class Provider : public QQuickImageProvider {
 public:
  Provider();

  QImage requestImage(const QString& id, QSize*, const QSize&) override;
};

#endif
