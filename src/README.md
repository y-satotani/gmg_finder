# gmg_finder マニュアル {#chap-experimental-program}
一般化ムーアグラフを探索するためのライブラリ

## 依存ライブラリ・ソフトウェア
- `gcc`
- `makefile`
- `igraph`
- `python` (一部)

## 実験プログラム
プログラムをビルドするには，`git`で
`https://github.com/y-satotani/gmg-finder`をクローンする．
すべての実験は`src/experiment`ディレクトリに含まれている．
`src`ディレクトリで`make ; make install`を実行すると，
以下の実行ファイルが`bin`ディレクトリに生成される．

- `exp_cmp_algo.out`
- `exp_cmp_algo_full.out`
- `exp_dist_delete.out`
- `exp_miner.out`
- `exp_cmp_algo_enum.out`
- `exp_enumer.out`

以下，各プログラムを順番に説明する．

### `exp_cmp_algo.out`
初期グラフと枝刈りの方法を変えて，性能を測定する．
実行例と結果例は以下のとおり．
```
src> experiment/exp_cmp_algo.out basic basic basic 10 3
```
```
10,3,2,0,150,basic,basic,basic,150,15,16,0.000144
```
結果は，次の値が`,`で区切られている．

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

次のコマンドで，複数の結果を含むcsvファイルを生成できる．
`--max-procs=x`の`x`の値だけ並列に実行する．
```
(echo n,d,Q,R,sspl_lb,ginitr,sorted,sinitr,sspl,edge,node,time ;\
 ./exp_cmp_algo_param.py |\
 xargs --max-lines=1 --max-procs=4 ./exp_cmp_algo.out) >\
cmp-algo.csv
```
パラメータは，`exp_cmp_algo_param.py`で生成される．
別のパラメータで実験する場合は，このファイルを編集する．

### `exp_cmp_algo_full.out`
`exp_cmp_algo.out`では探索開始から(もしあれば)最初の一個の
一般化ムーアグラフを得るまでの情報を計測したが，
`exp_cmp_algo_full.out`では探索開始からすべての一般化ムーアグラフ
を得るまでの情報を計測する．

```
./exp_cmp_algo_full.out basic basic basic 10 3
```
の実行例は次のとおり．
```
10,3,2,0,150,basic,basic,basic,4,150,150,15,75,0.00042
```
結果は，次の値が`,`で区切られている．

- 頂点数
- 次数
- `Q` (`gmgf::graph_config::Q()`)
- `R` (`gmgf::graph_config::R()`)
- 頂点間距離の総和の下界
- グラフ初期化子 (`exp_cmp_algo.out`と同じ)
- 候補辺ソート (`exp_cmp_algo.out`と同じ)
- 状態初期化子 (`exp_cmp_algo.out`と同じ)
- 結果のグラフの頂点間距離の総和
- 得られたグラフの数 (同型グラフを重複して数える)
- 最大の頂点間距離
- 最小の頂点間距離
- 候補辺の数
- 展開した状態数
- 実行時間

### `exp_dist_delete.out`
一辺削除時の頂点間距離の更新の実験を行う．次の項目を入力とする．

- ネットワークトポロジ
  - random=Erdős–Rényiモデル
  - scale-free=Barabási–Albertモデル
- 頂点数
- ネットワークパラメータ
- シード値 (ランダム関数の)

```
./exp_dist_delete.out random 1000 0.3 0
```
の実行例は以下のとおり．
```
1000,0.3,random,0,150422,1,0.827778,0.076536
```
結果は次の値が`,`で区切られている．

- 頂点数
- ネットワークパラメータ (トポロジにより，pかm)
- ネットワークトポロジ
  - `random`=Erdős–Rényiモデル
  - `scale-free`=Barabási–Albertモデル
- シード値
- 辺の数
- 結果が一致したかどうか (1なら一致)
- `igraph`ライブラリでの計算時間
- 提案手法の計算時間

### `exp_miner.out`
`exp_cmp_algo.out`で，グラフ初期化子を`gmgf::stree_graph_initr`，
状態初期化子を`gmgf::minmax_state_initr`とし，
さらに(もしあれば)一般化ムーアグラフを出力する機能を付加したプログラム．

```
./exp_miner.out 10 3
```
の実行例は以下のとおり，
```
10,3,2,0,150,150,15,16,0.000452
```
結果は次の値が`,`で区切られている．

- 頂点数
- 次数
- `Q` (`gmgf::graph_config::Q()`)
- `R` (`gmgf::graph_config::R()`)
- 頂点間距離の総和の下界
- 結果のグラフの頂点間距離の総和
- 候補辺の数
- 展開した状態数
- 実行時間 (`gmgf::dfs_finder::next()`の実行時間)

さらに，`n<頂点数>-d<次数>-miner.elist`の形式で，一般化ムーアグラフの
辺リストを保存する．

#### `exp_miner.py`
`exp_miner.out`に並列計算とタイムアウト機能を追加したプログラム．
コマンドライン引数は以下のとおり．

- `-n`=頂点数((次数+1)...Nの範囲を対象とする)
- `-d`=次数(3...Dの範囲を対象とする)
- `-i`=結果ファイルリスト(これらの結果に含まれている頂点数次数組は計算しない)
- `-o`=結果ファイル(指定しなければ標準出力)
- `-t`=タイムアウト時間(単位:秒)

結果は，`exp_miner.out`の結果を列としたcsvファイルである．

### `exp_cmp_algo_enum.out`
初期グラフと枝刈りの方法を変えて，互いに非同型な一般化ムーアグラフを列挙する．
実行例と結果例は以下のとおり．
```
src> experiment/exp_cmp_algo_enum.out basic basic basic 10 3
```
```
10,3,2,0,150,basic,basic,basic,1,1,15,23,0.030401
```
結果は，次の値が`,`で区切られている．

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
- 列挙されたすべてのグラフの頂点間距離の総和が下界に一致したか
- 列挙されたグラフの数
- 候補辺の数
- 展開した状態数
- 実行時間 (`gmgf::fbs_enumer::enumerate()`の実行時間)

`exp_cmp_algo_enum_param.py`を用いて，複数のパラメータで実験することが
できる．方法は`exp_cmp_algo.out`の項を参照のこと．

### `exp_enumer.out`
`exp_cmp_algo_enum.out`で，グラフ初期化子を`gmgf::stree_graph_initr`，
状態初期化子を`gmgf::minmax_state_initr`とし，
さらに，列挙された一般化ムーアグラフを出力する機能を付加したプログラム．

```
./exp_enumer.out 10 3
```
の実行例は以下のとおり，
```
10,3,2,0,150,1,1,15,22,0.00152
```
結果は次の値が`,`で区切られている．

- 頂点数
- 次数
- `Q` (`gmgf::graph_config::Q()`)
- `R` (`gmgf::graph_config::R()`)
- 頂点間距離の総和の下界
- 列挙されたグラフすべての頂点間距離の総和が下界に一致したか
- 列挙されたグラフの数
- 候補辺の数
- 展開した状態数
- 実行時間 (`gmgf::fbs_enumer::enumerate()`の実行時間)

さらに，`n<頂点数>-d<次数>-g<グラフ番号>-enumer.elist`の形式で，
一般化ムーアグラフの辺リストを保存する．

#### `exp_enumer.py`
`exp_enumer.out`に並列計算とタイムアウト機能を追加したプログラム．
コマンドライン引数は以下のとおり．

- `-n`=頂点数((次数+1)...Nの範囲を対象とする)
- `-d`=次数(3...Dの範囲を対象とする)
- `-i`=結果ファイルリスト(これらの結果に含まれている頂点数次数組は計算しない)
- `-o`=結果ファイル(指定しなければ標準出力)
- `-t`=タイムアウト時間(単位:秒)

結果は，`exp_enumer.out`の結果を列としたcsvファイルである．
