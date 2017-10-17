library(readr)
library(dplyr)
library(ggplot2)

data <- read_csv('exp_cmp_algo_result.csv') %>%
  group_by(n, d, bdr, mgr, node) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup()

data_to_be_plot <- data %>%
  filter(d == 3, bdr == 'basic' | mgr == 'basic') %>%
  mutate(mtd = ifelse(mgr == 'basic', bdr ,mgr)) %>%
  mutate(mtd = as.factor(mtd))

gp <- ggplot(data_to_be_plot,
             aes(x = n, y = node, color = mtd)) +
  scale_y_log10() +
  geom_point()
ggsave('exp_cmp_algo_result_node.pdf', gp,
       width = 13, height = 10, units = 'cm')

gp <- ggplot(data_to_be_plot,
             aes(x = n, y = mean_time, color = mtd)) +
  scale_y_log10() +
  geom_point()
ggsave('exp_cmp_algo_result_time.pdf', gp,
       width = 13, height = 10, units = 'cm')
