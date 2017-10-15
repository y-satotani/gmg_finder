#!/bin/bash
for svgfile in $(find figure | grep svg)
do
    pdffile=$(echo $svgfile | sed s/svg/pdf/g)
    inkscape -z -D -f $svgfile -A $pdffile --export-latex
done
