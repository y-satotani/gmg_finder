library(readr)
library(dplyr)
library(ggplot2)
library(extrafont)
library(grid)
library(gridExtra)

theme_set(theme_light())

g_grob <- function(gp, elem) {
  tmp <- ggplot_gtable(ggplot_build(gp))
  g <- grep(elem, sapply(tmp$grobs, function(x) x$name))
  grob <- tmp$grobs[[g]]
  return(grob)
}

breaks <- c('basic basic', 'cycle basic', 'cycle sorted', 'stree basic')
labels <- c('基本', '閉路', '閉路(並べ替えあり)', '全域木')
data <- read_csv('../data/the-cmp-algo-lab.csv') %>%
  filter(mgr == 'basic') %>%
  mutate(mtd = paste(bdr, srt)) %>%
  group_by(n, d, bdr, srt, mtd, node) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup() %>%
  mutate(mtd = factor(mtd, levels = breaks),
         d = factor(d))

pf <- function(vd) {
  gp <- ggplot(data %>% filter(d == vd),
               aes(x = n, y = node, color = mtd, shape = mtd, linetype = mtd)) +
    geom_line() +
    geom_point() +
    scale_x_continuous(name = '頂点数',
                       minor_breaks = NULL) +
    scale_y_continuous(name = '展開状態数',
                       trans = 'log10') +
    scale_color_manual(name = '初期グラフ',
                       breaks = breaks,
                       labels = labels,
                       values = c('#F8766D', '#619CFF', '#619CFF', '#00BA38')) +
    scale_shape_manual(name = '初期グラフ',
                       breaks = breaks,
                       labels = labels,
                       values = c(19, 19, 17, 19)) +
    scale_linetype_manual(name = '初期グラフ',
                          breaks = breaks,
                          labels = labels,
                          values = c(1, 1, 2, 1)) +
    theme(text = element_text(size = 10),
          plot.caption = element_text(family = 'TakaoPMincho', hjust = 0.5),
          axis.title.y = element_text(family = 'TakaoPGothic', angle = 90, hjust = 0.7),
          axis.title.x = element_text(family = 'TakaoPGothic', angle = 0, hjust = 0.5),
          legend.position = c(0, 0.8),
          legend.justification = c(0, 1)
    )
  return(gp)
}

p3 <- pf(3) + labs(caption = '(a) 次数 3') + theme(axis.title.y = element_blank(), legend.position = 'none')
p4 <- pf(4) + labs(caption = '(b) 次数 4') + theme(axis.title.y = element_blank(), legend.position = 'none')
gp <- arrangeGrob(p3, p4, ncol = 2)
ylab <- g_grob(pf(3), 'axis.title.y')
legend <- g_grob(pf(3), 'guide-box')

cairo_pdf('the-ginitr-node.pdf', width = 6.0, height = 2.5)
grid.arrange(
  ylab, gp, legend,
  ncol = 3,
  widths = unit.c(
    sum(ylab$width),
    unit(0.97, 'npc') - sum(ylab$width) - sum(legend$width),
    sum(legend$width))
)
dev.off()
