#include "config.hpp"

#include <QString>

#include "version.hpp"

using namespace Qt::Literals;

Config::Config(QObject* parent)
    : QObject(parent) {
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
                      u"https://github.com/hellokartikey"_s);

  KAboutData::setApplicationData(aboutData);
}

KAboutData Config::aboutData() const {
  return KAboutData::applicationData();
}
