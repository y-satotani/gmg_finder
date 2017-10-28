library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('cmp-algo-time-lab.csv') %>%
  filter(d == 3, bdr == 'basic' | mgr == 'basic') %>%
  mutate(mtd = ifelse(mgr == 'basic', bdr, mgr)) %>%
  select(-c(bdr, mgr)) %>%
  group_by(n, d, mtd, node) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup() %>%
  mutate(mtd = as.factor(mtd))

gp <- ggplot(data, aes(x = n, y = mean_time, color = mtd)) +
  scale_y_log10() +
  geom_point() +
  labs(x = 'n', y = 'time(s)')
ggsave('cmp-algo-time.pdf', gp,
       width = 15, height = 10, units = 'cm')
