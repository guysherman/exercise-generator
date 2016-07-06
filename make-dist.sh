#! /bin/bash

mkdir -p dist/bin
mkdir -p dist/share

cp build/exercise-generator dist/bin/exercise-generator
cp -R res dist/share
cp src/install.sh dist
cp readme.md dist
tar -czvf exercise-generator.tar.gz dist
