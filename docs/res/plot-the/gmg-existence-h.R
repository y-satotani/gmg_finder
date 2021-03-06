library(readr)
library(dplyr)
library(tidyr)
library(ggplot2)

theme_set(theme_light())

data <- read_csv('../data/miner.csv') %>%
  mutate(v = ifelse(sspl == sspl_lb, 1, 0)) %>%
  select(n, d, v)
data <- data %>%
  rbind(
    expand.grid(
      n = seq(min(data$n), max(data$n)),
      d = seq(min(data$d), max(data$d)),
      v = 2
    ) %>%
      filter(n > d, (n * d) %% 2 == 0)
  ) %>%
  distinct(n, d, .keep_all = TRUE) %>%
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
    expand = c(0, 0)
    ) +
  scale_fill_manual(
    name = NULL,
    values = c('grey80', 'royalblue', 'skyblue'),
    breaks = c(1, 0, 2),
    labels = c('存在する', '存在しない', '探索未完了')
    ) +
  theme(
    text = element_text(size = 9),
    panel.grid = element_blank(),
    panel.border = element_blank(),
    #panel.background = element_blank(),
    plot.title = element_text(hjust = 0.5),
    #axis.line = element_blank(),
    axis.ticks = element_blank(),
    legend.position = 'bottom'
    )

cairo_pdf('gmg-existence-h.pdf', width = 6, height = 2.5)
gp
dev.off()
