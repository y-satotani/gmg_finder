library(readr)
library(tidyr)
library(dplyr)
library(xtable)

data <- read_csv('../data/cmp-algo-enum-mws.csv') %>%
  filter(sorted == 'basic', sinitr == 'basic') %>%
  mutate(nd = paste0('(', n, ',', d, ')')) %>%
  mutate(ginitr = factor(ginitr, levels = c('basic', 'cycle', 'stree'))) %>%
  select(n, d, nd, ginitr, n_graph) %>%
  spread(ginitr, n_graph) %>%
  arrange(d, n) %>%
  select(-c(n, d))
names(data) <- c('$(n,d)$', '基本初期グラフ', '閉路初期グラフ', '全域木初期グラフ')
print(
  xtable(data,
         caption = '初期グラフを変更したときの互いに非同型な一般化ムーアグラフの数',
         label = 'tab:ginitr-ngraph-iso'
         ),
  caption.placement = 'top',
  sanitize.text.function = function(x) {x},
  include.rownames = FALSE,
  file = 'ginitr-ngraph-iso.tex'
  )
