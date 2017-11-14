# gmg_finder ソースコード
一般化ムーアグラフを探索するためのライブラリです．

### 依存ライブラリ・ソフトウェア
- `gcc`
- `makefile`
- `igraph`
- `python` (一部)

### 基本的な使い方
そのうちかきます

### 実験
すべての実験は`src/experiment`ディレクトリに含まれています．
`src`ディレクトリで`make`を実行すると，以下の実行ファイルが生成されます．
- `exp_cmp_algo.out`
- `exp_cmp_algo_full.out`
- `exp_dist_delete.out`
- `exp_miner.out`

順番に説明します．

##### `exp_cmp_algo.out`
初期グラフと枝刈りの方法を変えて，性能を測定します．
実行例と結果例は以下です．
```
src> experiment/exp_cmp_algo.out basic basic basic 10 3
```
```
10,3,2,0,150,basic,basic,basic,150,15,16,0.000144
```
結果は，次の値が`,`で区切られています．
- 頂点数
- 次数
- `Q` (`gmgf::graph_config::Q()`)
- `R` (`gmgf::graph_config::R()`)
- 頂点間距離の総和の下界
- グラフ初期化子
  - `basic`=`gmgf::basic_graph_initr`
  - `cycle`=`gmgf::cycle_graph_initr`
  - `stree`=`gmgf::stree_graph_initr`
- 候補辺ソート
  - `basic`=ソートなし
  - `sorted`=`gmgf::sorted_graph_initr`でソート
- 状態初期化子
  - `basic`=`gmgf::basic_state_initr`
  - `minmax`=`gmgf::minmax_state_initr`
  - `matrix`=`gmgf::mmmtr_state_initr`
- 結果のグラフの頂点間距離の総和
- 候補辺の数
- 展開した状態数
- 実行時間 (`gmgf::dfs_finder::next()`の実行時間)

次のコマンドで，複数の結果を含むcsvファイルを生成できます．
`--max-procs=x`の`x`の値だけ並列に実行します．
```
(echo n,d,Q,R,sspl_lb,bdr,srt,mgr,sspl,edge,node,time ;\
 ./exp_cmp_algo_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_algo.out) >\
cmp-algo.csv
```
パラメータは，`exp_cmp_algo_param.py`で生成されます．
別のパラメータで実験する場合は，このファイルを編集してください．

##### `exp_cmp_algo_full.out`
TODO

##### `exp_dist_delete.out`
TODO

##### `exp_miner.out`
TODO
