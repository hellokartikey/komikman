#ifndef HK_KOMIKMAN_BACKEND_HPP
#define HK_KOMIKMAN_BACKEND_HPP

#include <QtQmlIntegration/qqmlintegration.h>
#include <QObject>
#include <QString>

class Backend : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(QString message READ message CONSTANT)

 public:
  explicit Backend(QObject *parent = nullptr);

  inline QString message() const {
    using namespace Qt::Literals;
    return u"Hello, Komikman"_s;
  }

 private:
};

#endif
