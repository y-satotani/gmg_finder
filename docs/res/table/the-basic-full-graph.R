library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('the-cmp-algo-full-lab.csv') %>%
  filter(bdr == 'basic' & mgr == 'basic') %>%
  mutate(mtd = 'basic') %>%
  mutate(node_per_graph = node / n_graph) %>%
  select(n, d, mtd, n_graph) %>%
  mutate(d = factor(d, levels = c(3, 4), labels = c('次数:3', '次数:4')))

gp <- ggplot(data, aes(n, n_graph, color=mtd)) +
  geom_point() +
  geom_line() +
  facet_wrap(c('d'), scales = 'free') +
  scale_x_continuous(name = '頂点数',
                     minor_breaks = NULL) +
  scale_y_continuous(name = '列挙されたグラフ数',
                     trans = 'log10') +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey80'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80'),
        axis.ticks = element_line(colour = 'grey80'),
        strip.background = element_blank(),
        legend.position = 'none'
        )

ggsave('the-basic-full-graph.pdf', gp,
       width = 13, height = 6, units = 'cm',
       device = cairo_pdf)
