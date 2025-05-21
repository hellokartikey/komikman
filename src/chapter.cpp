#include "chapter.hpp"

Chapter::Chapter(QString title, QObject* parent)
    : QObject(parent),
      m_title(title) {}

const QString& Chapter::title() const {
  return m_title;
}
