#!/bin/bash
for svgfile in $(find figure | grep svg)
do
    pdffile=$(echo $svgfile | sed s/svg/pdf/g)
    inkscape -z -f $svgfile -A $pdffile --export-latex
done
