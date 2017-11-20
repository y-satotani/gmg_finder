library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-full-mws.csv') %>%
  filter(d == 3, bdr == 'basic') %>%
  mutate(mtd = mgr) %>%
  mutate(node_per_graph = node / n_graph) %>%
  select(n, d, mtd, node_per_graph)

gp <- ggplot(data, aes(n, node_per_graph, color=mtd)) +
  geom_point() +
  geom_line() +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = 'グラフあたりの展開状態数',
                     trans = 'log10') +
  scale_color_discrete(name = '',
                       breaks = c('basic', 'minmax', 'matrix'),
                       labels = c('基本', 'グラフ', '行列')) +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey50'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80')

  )

ggsave('the-sinitr-full-node.pdf', gp,
       width = 15, height = 10, units = 'cm',
       device = cairo_pdf)
