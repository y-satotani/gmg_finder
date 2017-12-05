library(readr)
library(dplyr)
library(ggplot2)

breaks <- c('basic', 'cycle', 'stree')
labels <- c('基本', '閉路', '全域木')
data <- read_csv('the-cmp-algo-full-lab.csv') %>%
  filter(mgr == 'basic', srt == 'basic') %>%
  mutate(mtd = bdr) %>%
  select(n, d, mtd, n_graph) %>%
  mutate(mtd = factor(mtd, levels = breaks),
         d = factor(d, levels = c(3, 4), labels = c('次数:3', '次数:4')))

gp <- ggplot(data, aes(n, n_graph, color=mtd)) +
  geom_line() +
  geom_point() +
  facet_wrap(c('d'), scales = 'free') +
  scale_x_continuous(name = '頂点数',
                     minor_breaks = NULL) +
  scale_y_continuous(name = '列挙されたグラフ数',
                     trans = 'log10') +
  scale_color_manual(name = '初期グラフ',
                     breaks = breaks,
                     labels = labels,
                     values = c('#F8766D', '#619CFF', '#00BA38')) +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey80'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80'),
        axis.ticks = element_line(colour = 'grey80'),
        strip.background = element_blank()
        )

ggsave('the-ginitr-full-graph.pdf', gp,
       width = 15, height = 6, units = 'cm',
       device = cairo_pdf)
