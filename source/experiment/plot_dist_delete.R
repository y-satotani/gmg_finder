library(readr)
library(tidyr)
library(dplyr)
library(ggplot2)

data <- read_csv('exp_dist_delete_result.csv') %>%
  select(-c(test, seed)) %>%
  rename(proposed = `time`) %>%
  rename(igraph = `time-igraph`) %>%
  gather(alg, time, c(proposed, igraph)) %>%
  mutate(alg = as.factor(alg),
         `p-or-m` = as.factor(`p-or-m`))

time_by_params <- data %>%
  select(-c(m)) %>%
  group_by(n, `p-or-m`, type, alg) %>%
  summarise(time = mean(time)) %>%
  ungroup()

time_by_params_random = time_by_params %>%
  filter(type == 'random') %>%
  rename(p = `p-or-m`)
gp <- ggplot(time_by_params_random,
             aes(n, time, colour = p, linetype = alg)) +
  geom_point() +
  geom_line()
ggsave('exp_dist_delete_result_random.pdf', gp,
       width = 15, height= 10, units = 'cm')
gp <- ggplot(time_by_params_random %>% filter(p == 0.1),
             aes(n, time, colour = p, linetype = alg)) +
  geom_point() +
  geom_line()
ggsave('exp_dist_delete_result_random_p0.1.pdf', gp,
       width = 15, height= 10, units = 'cm')

time_by_params_scale_free = time_by_params %>%
  filter(type == 'scale-free') %>%
  rename(m = `p-or-m`)
gp <- ggplot(time_by_params_scale_free,
             aes(n, time, colour = m, linetype = alg)) +
  geom_point() +
  geom_line()
ggsave('exp_dist_delete_result_scale_free.pdf', gp,
       width = 15, height= 10, units = 'cm')
