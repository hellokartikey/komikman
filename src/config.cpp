#include "config.hpp"

#include <QDebug>
#include <QString>

#include <libassert/assert.hpp>

#include "version.hpp"

using namespace Qt::Literals;

Config::Config(QObject* parent)
    : QObject(parent),
      m_theme(KColorSchemeManager::instance()) {
  auto aboutData = KAboutData{};

  aboutData.setComponentName(u"komikman"_s);
  aboutData.setDisplayName(u"Komikman"_s);
  aboutData.setShortDescription(u"Read your comics in style."_s);
  aboutData.setVersion(KOMIKMAN_VERSION_STRING);

  aboutData.setOrganizationDomain("https://github.com/hellokartikey");
  aboutData.setBugAddress("https://github.com/hellokartikey/komikman/issues");
  aboutData.setHomepage(u"https://github.com/hellokartikey/komikman"_s);

  aboutData.setCopyrightStatement(u"© 2025 Kartikey Subramanium"_s);
  aboutData.setDesktopFileName(u"com.github.hellokartikey.komikman"_s);
  aboutData.setLicense(KAboutLicense::GPL_V3);

  aboutData.addAuthor(u"hellokartikey"_s, u""_s, u""_s,
                      u"https://hellokartikey.github.io"_s);

  KAboutData::setApplicationData(aboutData);
}

Config* Config::the() {
  static auto inst = Config{};
  return &inst;
}

Config* Config::create(QQmlEngine*, QJSEngine*) {
  auto* ptr = ASSERT_VAL(Config::the());
  QJSEngine::setObjectOwnership(ptr, QJSEngine::CppOwnership);
  return ptr;
}

KAboutData Config::aboutData() const {
  return KAboutData::applicationData();
}

KColorSchemeManager* Config::themeManager() const {
  return ASSERT_VAL(m_theme);
}

QString Config::themeName() const {
  return themeManager()->activeSchemeName();
}

QAbstractItemModel* Config::themes() const {
  return themeManager()->model();
}

int Config::theme() const {
  return themeManager()
      ->indexForScheme(themeManager()->activeSchemeName())
      .row();
}

void Config::setTheme(int index) {
  if (index == theme()) {
    return;
  }

  themeManager()->activateScheme(themes()->index(index, 0));
  Q_EMIT themeChanged();
}

#include "moc_config.cpp"
