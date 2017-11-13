研究全体の目的
==============

与えられた頂点数と次数をもつ正則グラフのうち，Cerfらの平均頂点間距離の下界 \[1\]と一致する 平均頂点間距離をもつグラフが存在するかを判定する方法を開発する． また，既存の方法 \[2\]と比較することにより，新方法の有用性を検証する．

前回打ち合わせ時に定めた短期目標
================================

1.  深さ優先探索によるグラフの発見
2.  命題
    1.  グラフ*G*に長さ2*Q*以下の閉路が存在せず，直径が*Q* + 1ならば， *G*はCerfらの下界を達成する．
    2.  グラフ*G*に長さ2*Q*以下の閉路が存在しないならば，直径が*Q* + 1である．

の検証

本日までの進捗状況
==================

1.  プログラムが完成した．
    -   <https://gist.github.com/arity-r/21ded374488645fec6c3d1de9e6d3a83> (Python)
    -   <https://github.com/y-satotani/cerfcheck> (C言語)

    にて公開している．

    さらに，いくつかの頂点数と次数の組み合わせで実験を行った． 結果を表1に示す．

2.  二番目の命題が偽になるグラフを発見した． 図1に示す． 頂点数が14で，次数が3であるこのグラフは， 最小の閉路長が5(&gt;2*Q*)であるが，直径は4(≠*Q* + 1)である． さらに，このグラフはCerfらの下界を満足しない．

<table style="width:89%;">
<caption>表 1 探索結果 (continued below)</caption>
<colgroup>
<col width="5%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
</colgroup>
<thead>
<tr class="header">
<th>d</th>
<th>4</th>
<th>5</th>
<th>6</th>
<th>7</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>3</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="even">
<td><p>4</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="odd">
<td><p>5</p></td>
<td><pre><code> NA</code></pre></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
</tbody>
</table>

<table>
<caption>Table continues below</caption>
<colgroup>
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
</colgroup>
<thead>
<tr class="header">
<th>8</th>
<th>9</th>
<th>10</th>
<th>11</th>
<th>12</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="odd">
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
</tbody>
</table>

<table style="width:90%;">
<caption>Table continues below</caption>
<colgroup>
<col width="20%" />
<col width="20%" />
<col width="20%" />
<col width="6%" />
<col width="20%" />
</colgroup>
<thead>
<tr class="header">
<th>14</th>
<th>16</th>
<th>18</th>
<th>22</th>
<th>24</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><pre><code> NA</code></pre></td>
<td><pre><code> NA</code></pre></td>
<td><pre><code> NA</code></pre></td>
<td><p>NA</p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><pre><code> NA</code></pre></td>
<td><pre><code> NA</code></pre></td>
<td><pre><code> NA</code></pre></td>
<td><p>NA</p></td>
<td><pre><code> NA</code></pre></td>
</tr>
</tbody>
</table>

<table style="width:42%;">
<colgroup>
<col width="20%" />
<col width="20%" />
</colgroup>
<thead>
<tr class="header">
<th>26</th>
<th>28</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><pre><code> NA</code></pre></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><pre><code> NA</code></pre></td>
<td><pre><code> NA</code></pre></td>
</tr>
</tbody>
</table>

<img src="week02_files/figure-markdown_github/fig:cycle-diam-1.png" alt="図 1 命題の反例" width="70%" />
<p class="caption">
図 1 命題の反例
</p>

girthとdiameter

``` r
iG = read_graph('../res/graph/n14-d3-nogmg.elist')
paste(girth(iG)$girth, diameter(iG))
```

    ## [1] "5 3"

参考文献
========

\[1\] V. G. Cerf, D. D. Cowan, R. C. Mullin, and R. G. Stanton, Networks **4**, 335 (1974).

\[2\] 康隆山. and 規一高., (2016).
