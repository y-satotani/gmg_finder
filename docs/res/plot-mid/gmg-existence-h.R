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
    n,
    d,
    fill = v
    )
  ) +
  geom_tile(
    width = 0.9,
    height = 0.9
  ) +
  scale_x_continuous(
    '頂点数',
    position = 'top',
    #breaks = seq(min(data$n), max(data$n)),
    expand = c(0, 0)
    ) +
  scale_y_continuous(
    '次数',
    trans = 'reverse',
    breaks = seq(min(data$d), max(data$d)),
    expand = c(0, 0),
    sec.axis = dup_axis(name = NULL)
    ) +
  scale_fill_manual(
    guide = guide_legend(
      title = NULL,
      keywidth = 0.5,
      keyheight = 0.5
      ),
    values = c('white', 'royalblue'),
    breaks = c(1, 0),
    labels = c('存在する', '存在しない')
    ) +
  theme(
    text = element_text(size = 9),
    panel.grid = element_blank(),
    panel.border = element_blank(),
    #panel.background = element_blank(),
    plot.title = element_text(hjust = 0.5),
    #axis.line = element_blank(),
    axis.ticks = element_blank(),
    #legend.position = 'bottom'
    legend.position = 'none'
    )

ggsave('gmg-existence-h.pdf', gp, cairo_pdf,
       width = 12.5, height = 3.2, units = 'cm')
