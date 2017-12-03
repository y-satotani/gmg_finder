library(readr)
library(dplyr)
library(tidyr)
library(ggplot2)

data <- read_csv('miner.csv') %>%
  mutate(v = ifelse(sspl == sspl_lb, 1, 0)) %>%
  select(-c(Q, R, sspl_lb, sspl, edge, node, `time`)) %>%
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
  ggtitle('G-Moore graph existence') +
  geom_tile(
    width = 0.9,
    height = 0.9
  ) +
  scale_x_continuous(
    'Degree',
    position = 'top',
    breaks = seq(min(data$d), max(data$d)),
    expand = c(0, 0)
    ) +
  scale_y_continuous(
    'Order',
    breaks = seq(min(data$n), max(data$n)),
    trans = 'reverse',
    expand = c(0, 0)
    ) +
  scale_fill_manual(
    name ='Exists?',
    values = c('grey50', 'coral'),
    #values = c('grey50', 'royalblue'),
    breaks = c(1, 0),
    labels = c('yes', 'no')
    ) +
  theme(
    panel.grid = element_blank(),
    panel.background = element_blank(),
    plot.title = element_text(hjust = 0.5),
    axis.line = element_blank(),
    axis.ticks = element_blank()
    )
ggsave('miner-existence.pdf', gp,
       width = 7, height = 15, units = 'cm')
