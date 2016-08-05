#! /bin/bash

mkdir -p dist/bin
mkdir -p dist/share

cp build/exercise-generator dist/bin/exercise-generator
cp -R res dist/share
cp src/install.sh dist
chmod +x dist/install.sh
cp readme.md dist
tar -pczvf exercise-generator.tar.gz dist
