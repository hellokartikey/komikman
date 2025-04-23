#ifndef HK_KOMIKMAN_CONFIG_HPP
#define HK_KOMIKMAN_CONFIG_HPP

#include <QtQmlIntegration/qqmlintegration.h>
#include <QObject>

#include <KAboutData>

class Config : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(KAboutData aboutData READ aboutData CONSTANT)

 public:
  explicit Config(QObject* parent = nullptr);

  KAboutData aboutData() const;
};

#endif
