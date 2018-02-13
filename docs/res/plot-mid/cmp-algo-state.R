library(readr)
library(dplyr)
library(ggplot2)

levels = c('basic', 'cycle', 'stree', 'minmax')
labels = c('基本', '閉路', '全域木', '枝刈り')

data <- read_csv('../data/the-cmp-algo-lab.csv') %>%
  filter(d == 3) %>%
  filter(ginitr == 'basic' | sinitr == 'basic', sorted == 'basic') %>%
  mutate(algo = ifelse(ginitr == 'basic', sinitr, ginitr)) %>%
  filter(algo == 'basic' | algo == 'cycle' | algo == 'stree' | algo == 'minmax') %>%
  mutate(algo = factor(algo, levels = levels, labels = labels)) %>%
  group_by(n, algo, n_state) %>%
  summarise(mean_time = mean(time), max_state = max(n_state)) %>%
  ungroup()

theme_set(theme_gray(base_size = 11))

gp <- ggplot(data, aes(n, max_state, color = algo)) +
  geom_line(size = 0.6) +
  geom_point(size = 1) +
  scale_x_continuous('頂点数') +
  scale_y_continuous('展開状態数', trans = 'log10') +
  scale_color_discrete(NULL)

ggsave('cmp-algo-state.pdf', gp, cairo_pdf, width = 10, height = 6, units = 'cm')
