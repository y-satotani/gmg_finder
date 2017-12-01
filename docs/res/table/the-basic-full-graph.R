library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-full-mws.csv') %>%
  filter(d == 3, bdr == 'basic' & mgr == 'basic') %>%
  mutate(mtd = 'basic') %>%
  mutate(node_per_graph = node / n_graph) %>%
  select(n, d, mtd, n_graph)

gp <- ggplot(data, aes(n, n_graph, color=mtd)) +
  geom_point() +
  geom_line() +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = '発見グラフ数',
                     trans = 'log10') +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey80'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80'),
        axis.ticks = element_line(colour = 'grey80'),
        legend.position = 'none'
        )

ggsave('the-basic-full-graph.pdf', gp,
       width = 13, height = 10, units = 'cm',
       device = cairo_pdf)
