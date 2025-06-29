#include <QApplication>
#include <QDebug>
#include <QIcon>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QString>

#include <KLocalizedContext>

#include "image.hpp"

using namespace Qt::Literals;

int main(int argc, char *argv[]) {
  auto app = QApplication{argc, argv};
  auto qml = QQmlApplicationEngine{};

  QApplication::setWindowIcon(
      QIcon::fromTheme(u"com.github.hellokartikey.komikman"_s));

  QObject::connect(
      &qml, &QQmlApplicationEngine::objectCreationFailed, &app,
      [] { QApplication::exit(-1); }, Qt::QueuedConnection);

  if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
    QApplication::setStyle(u"Breeze"_s);
    QQuickStyle::setStyle(u"org.kde.desktop"_s);
    QIcon::setThemeName(u"breeze"_s);
  }

  qml.addImageProvider(IMAGE_PREFIX, new Provider());
  qml.rootContext()->setContextObject(new KLocalizedContext(&qml));
  qml.loadFromModule(u"Komikman"_s, u"Main"_s);

  return app.exec();
}
