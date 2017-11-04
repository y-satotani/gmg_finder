library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-full-mws.csv') %>%
  filter(d == 3, mgr == 'basic') %>%
  mutate(mtd = bdr) %>%
  select(-c(bdr, mgr)) %>%
  mutate(mtd = as.factor(mtd)) %>%
  mutate(mean_time = `time` / n_graph)

gp <- ggplot(data, aes(x = n, y = mean_time, color = mtd)) +
  geom_point(size = 2.1) +
  geom_line(size = .7) +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = '平均時間[s]',
                     trans = 'log10') +
  scale_color_discrete(name = '初期グラフ',
                       breaks = c('basic', 'cycle', 'stree'),
                       labels = c('基本', '閉路', '全域木')) +
  theme(text = element_text(family = 'IPAexGothic', size = 18))

ggsave('mid-cmp-algo-full-time.pdf', gp,
       width = 15, height = 10, units = 'cm',
       device = cairo_pdf)
