library(readr)
library(dplyr)
library(tidyr)
library(ggplot2)

theme_set(theme_light())

data <- read_csv('../data/miner.csv') %>%
  mutate(v = ifelse(sspl == sspl_lb, 1, 0)) %>%
  select(n, d, v) %>%
  mutate(v = as.factor(v))

gp <- ggplot(
  data,
  aes(
    d,
    #ordered(n, rev(sort(unique(n)))),
    n,
    fill = v
    )
  ) +
  geom_tile(
    width = 0.9,
    height = 0.9
  ) +
  scale_x_continuous(
    '次数',
    position = 'top',
    breaks = seq(min(data$d), max(data$d)),
    expand = c(0, 0)
    ) +
  scale_y_continuous(
    '頂点数',
    breaks = seq(min(data$n), max(data$n)),
    trans = 'reverse',
    expand = c(0, 0)
    ) +
  scale_fill_manual(
    #name = 'Exists?',
    name = NULL,
    values = c('grey50', 'royalblue'),
    breaks = c(1, 0),
    labels = c('存在する', '存在しない')
    ) +
  theme(
    text = element_text(size = 11),
    panel.grid = element_blank(),
    panel.border = element_blank(),
    #panel.background = element_blank(),
    plot.title = element_text(hjust = 0.5),
    #axis.line = element_blank(),
    axis.ticks = element_blank(),
    legend.position = 'bottom'
    )

cairo_pdf('gmg-existence.pdf', width = 2.5, height = 6.5)
gp
dev.off()
