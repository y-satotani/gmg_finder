library(readr)
library(dplyr)
library(ggplot2)

breaks <- c('basic', 'cycle', 'stree')
labels <- c('基本', '閉路', '全域木')
data <- read_csv('cmp-algo-full-mws.csv') %>%
  filter(d == 3, mgr == 'basic', srt == 'basic') %>%
  mutate(mtd = bdr) %>%
  select(n, mtd, n_graph) %>%
  mutate(mtd = factor(mtd, levels = breaks)) %>%
  arrange(mtd, n)

gp <- ggplot(data, aes(n, n_graph, color=mtd)) +
  geom_line() +
  geom_point() +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = '発見グラフ数',
                     trans = 'log10') +
  scale_color_discrete(name = '',
                       breaks = breaks,
                       labels = labels) +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey80'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80'),
        axis.ticks = element_line(colour = 'grey80')
        )

ggsave('the-ginitr-full-graph.pdf', gp,
       width = 15, height = 10, units = 'cm',
       device = cairo_pdf)
