#!/bin/bash
pandoc --chapters -o AppManual.tex ../../src/README.md
sed -i s/section/section*/g AppManual.tex
