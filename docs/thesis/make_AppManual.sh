#!/bin/bash
pandoc --chapters -o AppManual.tex ../../src/README.md
sed -i s/section/section*/g AppManual.tex
sed -i 's/ő/\\H{o}/g' AppManual.tex
sed -i "s/é/{\\\'e\}/g" AppManual.tex
sed -i "s/á/{\\\'a}/g" AppManual.tex
