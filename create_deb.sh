#!/bin/bash

VERSION=0.2
BUILD="1"
DEB_DIR="qt5-freq-viewer_$VERSION-${BUILD}_amd64"
mkdir $DEB_DIR

mkdir -p $DEB_DIR/usr/local/bin
cp -rf qt5-freq-viewer $DEB_DIR/usr/local/bin

mkdir $DEB_DIR/DEBIAN

touch $DEB_DIR/DEBIAN/control

echo "Package: qt5-freq-viewer" > $DEB_DIR/DEBIAN/control
echo "Version: $VERSION-$BUILD" >> $DEB_DIR/DEBIAN/control
echo "Architecture: amd64" >> $DEB_DIR/DEBIAN/control
echo "Maintainer: Evgenii Sopov <mrseakg@gmail.com>" >> $DEB_DIR/DEBIAN/control
echo "Description: Viewer for files with frequerinsies and S11." >> $DEB_DIR/DEBIAN/control
echo "Depends: libqt5core5a, libqt5gui5, libqt5qml5, libqt5network5, libqt5dbus5, qml-module-qtquick-controls, qml-module-qtquick-controls2 " >> $DEB_DIR/DEBIAN/control

touch $DEB_DIR/DEBIAN/postinst
chmod 755 $DEB_DIR/DEBIAN/postinst

dpkg-deb --build $DEB_DIR