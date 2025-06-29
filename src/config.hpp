#ifndef HK_KOMIKMAN_CONFIG_HPP
#define HK_KOMIKMAN_CONFIG_HPP

#include <QtQmlIntegration/qqmlintegration.h>
#include <QAbstractItemModel>
#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>

#include <KAboutData>
#include <KColorSchemeManager>

class Config : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  // About data
  Q_PROPERTY(KAboutData aboutData READ aboutData CONSTANT)

  // Color schemes
  Q_PROPERTY(QAbstractItemModel* themes READ themes CONSTANT)
  Q_PROPERTY(QString themeName READ themeName NOTIFY themeChanged)
  Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)

 private:
  explicit Config(QObject* parent = nullptr);

 public:
  static Config* the();
  static Config* create(QQmlEngine*, QJSEngine*);

  KAboutData aboutData() const;

  QAbstractItemModel* themes() const;
  KColorSchemeManager* themeManager() const;
  int theme() const;
  QString themeName() const;
  Q_INVOKABLE void setTheme(int index);
  Q_SIGNAL void themeChanged();

 private:
  KColorSchemeManager* m_theme = nullptr;
};

#endif
