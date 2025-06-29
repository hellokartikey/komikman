#include "image.hpp"

#include "backend.hpp"

Provider::Provider()
    : QQuickImageProvider(Image) {}

QImage Provider::requestImage(const QString& id, QSize*, const QSize&) {
  auto index = id.toUInt();

  if (auto* ptr = Backend::the()->currentChapter(); ptr) {
    if (index < ptr->length()) {
      return ptr->get(index);
    }
  }

  return QImage{};
}
