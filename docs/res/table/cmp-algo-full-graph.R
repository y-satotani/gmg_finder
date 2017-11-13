library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-full-mws.csv') %>%
  filter(d == 3, bdr == 'basic' | mgr == 'basic') %>%
  mutate(mtd = ifelse(mgr == 'basic', bdr, mgr)) %>%
  select(n, d, mtd, n_graph)
gp <- ggplot(data, aes(n, n_graph, color=mtd)) +
  scale_y_log10() +
  geom_point() +
  geom_line() +
  labs(x = 'n', y = '# of graphs')
ggsave('cmp-algo-full-graph.pdf', gp,
       width = 15, height = 10, units = 'cm')
