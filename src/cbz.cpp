#include "cbz.hpp"

Cbz::Cbz(QString path, QObject* parent)
    : Archive(new KZip(path), path, parent) {}

#include "moc_cbz.cpp"
