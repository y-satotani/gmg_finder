library(readr)
library(tidyr)
library(dplyr)
library(ggplot2)

data <- read_csv('dist-delete-mws.csv') %>%
  filter(type == 'random') %>%
  select(-c(type, m, test, seed)) %>%
  rename(m = `p-or-m`) %>%
  rename(proposed = `time`) %>%
  rename(igraph = `time-igraph`) %>%
  gather(alg, time, c(proposed, igraph)) %>%
  mutate(alg = as.factor(alg), m = as.factor(m)) %>%
  group_by(n, m, alg) %>%
  summarise(time = mean(time)) %>%
  ungroup()

gp <- ggplot(data,
             aes(n, time, colour = m, linetype = alg)) +
  geom_point() +
  geom_line() +
  labs(x = 'n', y = 'time(s)')
ggsave('dist-delete-scale-free.pdf', plot = gp,
       width = 15, height = 10, units = 'cm')
