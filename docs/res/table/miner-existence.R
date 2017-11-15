library(readr)
library(dplyr)
library(tidyr)
library(ggplot2)

data <- read_csv('miner.csv') %>%
  mutate(v = ifelse(sspl == sspl_lb, 1, 0)) %>%
  select(-c(Q, R, sspl_lb, sspl, edge, node, `time`)) %>%
  mutate(n = as.factor(n), d = as.factor(d), v = as.factor(v))

gp <- ggplot(
  data,
  aes(
    d,
    ordered(n, rev(sort(unique(n)))),
    fill = v
    )
  ) +
  ggtitle('G-Moore graph existence') +
  scale_x_discrete('Degree', position = 'top') +
  scale_y_discrete('Order') +
  scale_fill_manual(
    name ='Exists?',
    values = c('grey50', 'royalblue'),
    breaks = c(1, 0),
    labels = c('yes', 'no')
    ) +
  geom_tile(color = 'white') +
  theme(
    panel.grid = element_blank(),
    axis.line = element_blank(),
    axis.ticks = element_blank()
    )
ggsave('miner-existence.pdf', gp,
       width = 8, height = 16, units = 'cm')
