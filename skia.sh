#!/bin/bash
cd subprojects
mkdir -p skia && cd skia
mkdir -p skia && cd skia

mkdir -p include && cd include
wget -q https://github.com/EclipseLinux/Skia/releases/latest/download/skia-includes.zip -O include.zip
unzip -qo include.zip

cd ..

mkdir -p src && cd src
wget -q https://github.com/EclipseLinux/Skia/releases/latest/download/skia-src.zip -O src.zip
unzip -qo src.zip

cd ..

mkdir -p modules && cd modules
wget -q https://github.com/EclipseLinux/Skia/releases/latest/download/skia-modules.zip -O modules.zip
unzip -qo modules.zip

cd ../..

wget -q https://github.com/EclipseLinux/Skia/releases/latest/download/skia-$1-$2.zip -O bin.zip
unzip -qo bin.zip

rm skia/include/include.zip
rm skia/modules/modules.zip
rm bin.zip

# remove unneeded files
rm -f libpathkit.a
