
NOT WORKED FOR ME:

## Preapre deploy

```sh
$ sudo apt install patchelf zip
$ git clone https://github.com/probonopd/linuxdeployqt
$ cd linuxdeployqt
$ qmake
$ make
$ cd bin
$ ./linuxdeployqt ../../qt5-freq-viewer -qmldir=../../src/qml/ -always-overwrite
```
*note: linuxdeployqt can be freezed. So... just Ctrl+С and continue*
```
$ rm -rf Qt5FreqViewer.zip
$ zip Qt5FreqViewer.zip -r qt5-freq-viewer AppRun qml/ lib/ doc/

```