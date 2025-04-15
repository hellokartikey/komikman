#include <QApplication>
#include <QDebug>
#include <QIcon>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QString>

using namespace Qt::Literals;

int main(int argc, char *argv[]) {
  auto app = QApplication{argc, argv};
  auto qml = QQmlApplicationEngine{};

  QObject::connect(
      &qml, &QQmlApplicationEngine::objectCreationFailed, &app,
      [] { QApplication::exit(-1); }, Qt::QueuedConnection);

  if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
    QApplication::setStyle(u"Breeze"_s);
    QQuickStyle::setStyle(u"org.kde.desktop"_s);
    QIcon::setThemeName(u"breeze"_s);
  }

  qml.loadFromModule(u"Komikman"_s, u"Main"_s);

  return app.exec();
}
