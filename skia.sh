#!/bin/bash
cd subprojects
mkdir -p skia && cd skia
mkdir -p skia && cd skia
mkdir -p include && cd include
wget -q https://github.com/EclipseLinux/Skia/releases/latest/download/skia-includes.zip -O include.zip
unzip -qo include.zip
cd ../..
wget -q https://github.com/EclipseLinux/Skia/releases/latest/download/skia-$1-$2.zip -O bin.zip
unzip -qo bin.zip
rm include/include.zip
rm bin.zip

# remove unneeded files
rm -f libpathkit.a
