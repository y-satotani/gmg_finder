library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('the-cmp-algo-lab.csv') %>%
  filter(bdr == 'basic' & mgr == 'basic') %>%
  mutate(mtd = 'basic') %>%
  group_by(n, d, mtd, node) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup() %>%
  mutate(mtd = as.factor(mtd),
         d = factor(d, levels = c(3, 4), labels = c('次数:3', '次数:4')))

gp <- ggplot(data, aes(x = n, y = mean_time, color = mtd)) +
  geom_point() +
  geom_line() +
  facet_wrap(c('d'), scales = 'free') +
  scale_x_continuous(name = '頂点数',
                     minor_breaks = NULL) +
  scale_y_continuous(name = '平均探索時間[s]',
                     trans = 'log10') +
  theme(text = element_text(family = 'IPAexGothic', size = 10),
        panel.background = element_rect(fill = 'white', colour = 'grey80'),
        panel.grid.major = element_line(colour = 'grey80'),
        panel.grid.minor = element_line(colour = 'grey80'),
        axis.ticks = element_line(colour = 'grey80'),
        strip.background = element_blank(),
        legend.position = 'none'
  )

ggsave('the-basic-time.pdf', gp,
       width = 13, height = 6, units = 'cm',
       device = cairo_pdf)
