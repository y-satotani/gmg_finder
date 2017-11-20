library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-full-mws.csv') %>%
  filter(d == 3, mgr == 'basic') %>%
  mutate(mtd = ifelse(bdr == 'cycle' & srt == 'sorted', 'sorted-cycle', bdr)) %>%
  mutate(time_per_graph = `time` / n_graph) %>%
  select(n, d, mtd, time_per_graph)

gp <- ggplot(data, aes(n, time_per_graph, color=mtd)) +
  geom_point() +
  geom_line() +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = 'グラフあたりの探索時間[s]',
                     trans = 'log10') +
  scale_color_discrete(name = '',
                       breaks = c('basic', 'cycle', 'sorted-cycle', 'stree'),
                       labels = c('基本', '閉路(並べ替えなし)', '閉路', '全域木')) +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey50'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80')
)

ggsave('the-ginitr-full-time.pdf', gp,
       width = 15, height = 10, units = 'cm',
       device = cairo_pdf)
