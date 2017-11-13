library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-full-mws.csv') %>%
  filter(d == 3, mgr == 'basic') %>%
  mutate(mtd = bdr) %>%
  select(-c(bdr, mgr)) %>%
  mutate(mtd = as.factor(mtd))

gp <- ggplot(data, aes(x = n, y = n_graph, color = mtd)) +
  geom_point(size = 2.1) +
  geom_line(size = .7) +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = 'グラフ数',
                     trans = 'log10') +
  scale_color_discrete(name = '初期グラフ',
                       breaks = c('basic', 'cycle', 'stree'),
                       labels = c('基本', '閉路', '全域木')) +
  theme(text = element_text(family = 'IPAexGothic', size = 18))

ggsave('mid-cmp-algo-full-graph.pdf', gp,
       width = 15, height = 10, units = 'cm',
       device = cairo_pdf)
