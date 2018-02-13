library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('../data/fin-order-aspl.csv') %>%
  mutate(degree = factor(degree))

theme_set(theme_gray(base_size = 11))

gp <- ggplot(data, aes(order, aspl, colour = degree)) +
  geom_line(size = 0.5) +
  scale_x_continuous(name = '頂点数') +
  scale_y_continuous(name = '平均頂点間距離の下界', limits = c(0, 8)) +
  guides(color = guide_legend(title = '次数'))

ggsave('order-aspl.pdf', gp, cairo_pdf, width = 10, height = 6, units = 'cm')
