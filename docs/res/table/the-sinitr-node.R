library(readr)
library(dplyr)
library(ggplot2)

breaks <- c('basic', 'minmax')
labels <- c('なし', 'あり')
data <- read_csv('cmp-algo-mws.csv') %>%
  filter(d == 3, bdr == 'basic', mgr == 'basic' | mgr == 'minmax') %>%
  mutate(mtd = mgr) %>%
  group_by(n, d, mtd, node) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup() %>%
  mutate(mtd = factor(mtd, levels = breaks)) %>%
  arrange(mtd, n)

gp <- ggplot(data, aes(x = n, y = node, color = mtd)) +
  geom_line() +
  geom_point() +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = '展開状態数',
                     trans = 'log10') +
  scale_color_discrete(name = '枝刈り',
                       breaks = breaks,
                       labels = labels) +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey80'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80'),
        axis.ticks = element_line(colour = 'grey80'))

ggsave('the-sinitr-node.pdf', gp,
       width = 15, height = 10, units = 'cm',
       device = cairo_pdf)
