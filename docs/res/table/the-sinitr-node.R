library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-mws.csv') %>%
  filter(d == 3, bdr == 'basic') %>%
  mutate(mtd = mgr) %>%
  group_by(n, d, mtd, node) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup() %>%
  mutate(mtd = as.factor(mtd))

gp <- ggplot(data, aes(x = n, y = node, color = mtd)) +
  geom_point() +
  geom_line() +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = '展開状態数',
                     trans = 'log10') +
  scale_color_discrete(name = '',
                       breaks = c('basic', 'minmax', 'matrix'),
                       labels = c('基本', 'グラフ', '行列')) +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey50'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80'))

ggsave('the-sinitr-node.pdf', gp,
       width = 15, height = 10, units = 'cm',
       device = cairo_pdf)
