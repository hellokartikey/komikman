set(ICON_FILE com.github.hellokartikey.komikman.svg)
set(DESKTOP_FILE com.github.hellokartikey.komikman.desktop)

install(FILES ${ICON_FILE} DESTINATION ${KDE_INSTALL_ICONDIR}/hicolor/scalable/apps)
install(FILES ${DESKTOP_FILE} DESTINATION ${KDE_INSTALL_APPDIR})
