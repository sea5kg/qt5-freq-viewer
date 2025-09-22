# qt5-freq-viewer

Example of qml diagram rendering.

![screen](https://raw.githubusercontent.com/sea5kg/qt5-freq-viewer/main/misc/screen.png)

## Ubuntu

Requirements for build:
```
$ sudo apt update
$ sudo apt install -y build-essential cmake qtbase5-dev qtdeclarative5-dev qtquickcontrols2-5-dev
```

## build in docker

1. Build docker environment

```sh
$ docker build --rm=true -t "sea5kg/qt5-freq-viewer:build-env" .
```

2. Run command line docker

```sh
$ docker run -it --rm -v $(pwd):/opt/src "sea5kg/qt5-freq-viewer:build-env" bash
```

3. And run inside a docker command for build project:

```sh
# ./build_simple.sh
```

## Run from command line:

Run with filepath with data:
```
$ ./qt5-freq-viewer testdata/test1.txt
```

## References

https://github.com/tlanc007/qt5-qml-cpp-cmake-helloworld/tree/master