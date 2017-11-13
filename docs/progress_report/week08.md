研究全体の目的
==============

深さ優先探索をベースにした，一般化ムーアグラフを発見するアルゴリズムを開発する． さらに，初期グラフの改良や枝刈りを導入する，更なる改良案を提案する． 同時に，これらの改良を評価する．

前回打ち合わせ時に定めた短期目標
================================

1.  中間報告のための資料作成
2.  実験の継続
3.  辺削除に対する直径の高速更新を使った探索の高速化
4.  証明，アルゴリズムの文書化

本日までの進捗状況
==================

1.  完成した．
2.  一般化ムーアグラフが存在する組を求める実験を継続している． 現在までに発見した一般化ムーアグラフの頂点数と次数の組を 表1に示す．
3.  プログラムが完成し，実験を行った． 結果を図1に示す．
4.  正則グラフが一般化ムーアグラフであることの条件の証明を書いた．

<table style="width:69%;">
<caption>表 1 発見した一般化ムーアグラフの頂点数と次数の組</caption>
<colgroup>
<col width="6%" />
<col width="20%" />
<col width="20%" />
<col width="20%" />
</colgroup>
<thead>
<tr class="header">
<th>n</th>
<th>3</th>
<th>4</th>
<th>5</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>4</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="even">
<td><p>5</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>6</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>7</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>8</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>9</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>10</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>11</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>12</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>13</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>14</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>15</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>16</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>17</p></td>
<td><pre><code> NA</code></pre></td>
<td></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>18</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>19</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>20</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>21</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>22</p></td>
<td></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>23</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>24</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>25</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>26</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td></td>
</tr>
<tr class="even">
<td><p>27</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>28</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="even">
<td><p>29</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>30</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>31</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>32</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
</tr>
<tr class="even">
<td><p>33</p></td>
<td><pre><code> NA</code></pre></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
<tr class="odd">
<td><p>34</p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><p><span class="math inline">✓</span></p></td>
<td><pre><code> NA</code></pre></td>
</tr>
</tbody>
</table>

<img src="week08_files/figure-markdown_github/fig:mmmtr-1.png" alt="図 1 辺挿入と辺削除のアルゴリズムを利用した一般化ムーアグラフの探索時間" width="70%" />
<p class="caption">
図 1 辺挿入と辺削除のアルゴリズムを利用した一般化ムーアグラフの探索時間
</p>
