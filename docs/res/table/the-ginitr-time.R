library(readr)
library(dplyr)
library(ggplot2)

breaks <- c('basic basic', 'cycle basic', 'cycle sorted', 'stree basic')
labels <- c('基本', '閉路', '閉路(並べ替えあり)', '全域木')
data <- read_csv('cmp-algo-mws.csv') %>%
  filter(d == 3, mgr == 'basic') %>%
  mutate(mtd = paste(bdr, srt)) %>%
  group_by(n, d, bdr, srt, mtd, node) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup() %>%
  mutate(mtd = factor(mtd, levels = breaks)) %>%
  arrange(mtd, n)

gp <- ggplot(data, aes(x = n, y = mean_time, color = mtd, shape = mtd, linetype = mtd)) +
  geom_line() +
  geom_point() +
  scale_x_continuous(name = '頂点数',
                     breaks = data$n,
                     minor_breaks = NULL,
                     labels = as.character(data$n)) +
  scale_y_continuous(name = '平均探索時間[s]',
                     trans = 'log10') +
  scale_color_manual(name = '初期グラフ',
                     breaks = breaks,
                     labels = labels,
                     values = c('#F8766D', '#619CFF', '#619CFF', '#00BA38')) +
  scale_shape_manual(name = '初期グラフ',
                     breaks = breaks,
                     labels = labels,
                     values = c(19, 19, 17, 19)) +
  scale_linetype_manual(name = '初期グラフ',
                        breaks = breaks,
                        labels = labels,
                        values = c(1, 1, 2, 1)) +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey80'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80'),
        axis.ticks = element_line(colour = 'grey80')
  )

ggsave('the-ginitr-time.pdf', gp,
       width = 15, height = 10, units = 'cm',
       device = cairo_pdf)
