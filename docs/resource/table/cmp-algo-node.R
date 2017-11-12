library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-node-lab.csv') %>%
  filter(d == 3, bdr == 'basic' | mgr == 'basic') %>%
  mutate(mtd = ifelse(mgr == 'basic', bdr, mgr)) %>%
  select(-c(bdr, mgr)) %>%
  group_by(n, d, mtd, node) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup() %>%
  mutate(mtd = as.factor(mtd))

gp <- ggplot(data, aes(x = n, y = node, color = mtd)) +
  scale_y_log10() +
  geom_point() +
  geom_line() +
  labs(x = 'n', y = 'graph')
ggsave('cmp-algo-node.pdf', gp,
       width = 15, height = 10, units = 'cm')
