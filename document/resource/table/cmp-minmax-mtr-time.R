library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-minmax-mtr-mws.csv') %>%
  filter(d == 3) %>%
  mutate(mtd = as.factor(mgr))

gp <- ggplot(data, aes(x = n, y = `time`, color = mtd)) +
  scale_y_log10() +
  geom_point() +
  geom_line() +
  labs(x = 'n', y = 'time(s)')
ggsave('cmp-minmax-mtr-time.pdf', gp,
       width = 15, height = 10, units = 'cm')
