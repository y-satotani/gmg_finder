library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-full-mws.csv') %>%
  filter(d == 3, bdr == 'basic' | mgr == 'basic') %>%
  mutate(mtd = ifelse(mgr == 'basic', bdr, mgr)) %>%
  mutate(time_per_graph = `time` / n_graph) %>%
  select(n, d, mtd, time_per_graph)
gp <- ggplot(data, aes(n, time_per_graph, color=mtd)) +
  scale_y_log10() +
  geom_point() +
  geom_line() +
  labs(x = 'n', y = 'time / graph (s)')
ggsave('cmp-algo-full-time.pdf', gp,
       width = 15, height = 10, units = 'cm')
