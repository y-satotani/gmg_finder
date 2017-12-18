library(readr)
library(dplyr)
library(ggplot2)
library(extrafont)
library(gridExtra)

theme_set(theme_light())

g_grob <- function(gp, elem) {
  tmp <- ggplot_gtable(ggplot_build(gp))
  g <- grep(elem, sapply(tmp$grobs, function(x) x$name))
  grob <- tmp$grobs[[g]]
  return(grob)
}

data <- read_csv('../data/the-cmp-algo-full-lab.csv') %>%
  filter(bdr == 'basic' & mgr == 'basic') %>%
  mutate(mtd = 'basic') %>%
  mutate(node_per_graph = node / n_graph) %>%
  select(n, d, mtd, n_graph) %>%
  mutate(d = factor(d, levels = c(3, 4)))

pf <- function(vd) {
  gp <- ggplot(data %>% filter(d == vd), aes(n, n_graph, color = mtd)) +
    geom_point() +
    geom_line() +
    scale_x_continuous(name = '頂点数',
                       minor_breaks = NULL) +
    scale_y_continuous(name = '列挙されたグラフ数',
                       trans = 'log10') +
    theme(text = element_text(size = 10),
          plot.caption = element_text(family = 'TakaoPMincho', hjust = 0.5),
          axis.title.y = element_text(family = 'TakaoPGothic', angle = 90, hjust = 0.7),
          axis.title.x = element_text(family = 'TakaoPGothic', angle = 0, hjust = 0.5),
          legend.position = 'none'
    )
  return(gp)
}

cairo_pdf('the-basic-full-graph.pdf', width = 5.2, height = 2.5)
grid.arrange(
  pf(3) + labs(caption = '(a) 次数 3') + theme(axis.title.y = element_blank(), legend.position = 'none'),
  pf(4) + labs(caption = '(b) 次数 4') + theme(axis.title.y = element_blank(), legend.position = 'none'),
  ncol = 2, left = g_grob(pf(3), 'axis.title.y')
  )
dev.off()
