library(readr)
library(dplyr)
library(tidyr)
library(ggplot2)
library(grid)
library(gridExtra)
library(gtable)

theme_set(theme_light())

g_grob <- function(gp, elem) {
  tmp <- ggplot_gtable(ggplot_build(gp))
  g <- grep(elem, sapply(tmp$grobs, function(x) x$name))
  grob <- tmp$grobs[[g]]
  return(grob)
}

g_filter <- function(gp, elem) {
  return(gtable_filter(ggplotGrob(gp), elem))
}

hide_title_and_yaxis_and_legend <- function(gp) {
  return(gp + theme(
    plot.margin = unit(c(3, 1, 1, 0), 'mm'),
    plot.title = element_blank(),
    axis.title.y = element_blank(),
    axis.ticks.length = unit(1, 'mm'),
    axis.text.y = element_blank(),
    legend.position = 'none'
  ))
}

blank <- grid.rect(gp = gpar(col = 'white'))

make_margin <- function(gp, p_height) {
  g <- arrangeGrob(
    blank, gp, blank,
    nrow = 3,
    heights = unit.c(
      unit(3, 'mm'),
      panel_height,
      unit(1, 'npc') - p_height - unit(3, 'mm')
    ),
    widths = unit.c(sum(gp$widths))
  )
  return(g)
}

type_breaks = c('random', 'scale-free')
alg_breaks = c('proposed', 'igraph')
data <- read_csv('../data/the-dist-delete-mws.csv') %>%
  select(-c(m, test, seed)) %>%
  rename(proposed = `time`, igraph = `time-igraph`) %>%
  gather(alg, time, c(proposed, igraph)) %>%
  group_by(n, type, `p-or-m`, alg) %>%
  summarise(time = mean(time)) %>%
  ungroup() %>%
  mutate(
    type = factor(type, levels = type_breaks),
    alg = factor(alg, levels = alg_breaks),
    p = ifelse(type == 'random', `p-or-m`, NA),
    m = ifelse(type == 'scale-free', `p-or-m`, NA)) %>%
  arrange(type, alg)

pf <- function(vtype, valg) {
  title <- ifelse(vtype == 'random', 'Erdős-Rényiモデル', 'Barabási-Albertモデル')
  title_ylab <- ifelse(valg == 'proposed', '提案手法[s]', 'igraphライブラリ[s]')
  title_xlab <- '頂点数'
  gp <- ggplot(
    filter(data, type == vtype, alg == valg),
    aes(n, time, colour = as.factor(ifelse(type == 'random', p, m)))
    ) +
    ggtitle(title) +
    geom_line() +
    geom_point() +
    scale_x_continuous(name = title_xlab) +
    scale_y_continuous(name = title_ylab, labels = function(y) format(y, nsmall = 2)) +
    labs(colour = ifelse(vtype == 'random', 'p', 'm')) +
    theme(
      text = element_text(size = 9),
      plot.title = element_text(hjust = 0.5),
      plot.margin = unit(c(3, 3, 1, 3), 'mm'),
      legend.position = 'bottom'
      )
  return(gp)
}

plot_height <- unit(2.5, 'inches')
cairo_pdf('dist-delete.pdf', width = 3, height = convertHeight(plot_height, 'inches', TRUE))
pf('random', 'igraph') + theme(plot.title = element_blank(), legend.position = 'none')
seekViewport('panel.6-4-6-4')
panel_width <- convertWidth(unit(1, 'npc'), 'inches')
panel_height <- convertHeight(unit(1, 'npc'), 'inches')
seekViewport('layout')
dev.off()

gp_igraph_random <- pf('random', 'igraph')
gp_igraph_scalefree <- pf('scale-free', 'igraph')
gp_proposed_random <- pf('random', 'proposed')
gp_proposed_scalefree <- pf('scale-free', 'proposed')

p_random_title <- g_grob(gp_igraph_random, 'plot.title')
p_scalefree_title <- g_grob(gp_igraph_scalefree, 'plot.title')
gp_igraph_ylab <- g_grob(gp_igraph_random, 'axis.title.y')
p_igraph_ylab <- make_margin(gp_igraph_ylab, panel_height)
gp_proposed_ylab <- g_grob(gp_proposed_random, 'axis.title.y')
p_proposed_ylab <- make_margin(gp_proposed_ylab, panel_height)

gp_igraph_random_yaxis <- g_filter(gp_igraph_random, 'axis-l')
p_igraph_random_yaxis <- make_margin(gp_igraph_random_yaxis, panel_height)
p_igraph_random <- hide_title_and_yaxis_and_legend(gp_igraph_random)
gp_igraph_scalefree_yaxis <- g_filter(gp_igraph_scalefree, 'axis-l')
p_igraph_scalefree_yaxis <- make_margin(gp_igraph_scalefree_yaxis, panel_height)
p_igraph_scalefree <- hide_title_and_yaxis_and_legend(gp_igraph_scalefree)

gp_proposed_random_yaxis <- g_filter(gp_proposed_random, 'axis-l')
p_proposed_random_yaxis <- make_margin(gp_proposed_random_yaxis, panel_height)
p_proposed_random <- hide_title_and_yaxis_and_legend(gp_proposed_random)
gp_proposed_scalefree_yaxis <- g_filter(gp_proposed_scalefree, 'axis-l')
p_proposed_scalefree_yaxis <- make_margin(gp_proposed_scalefree_yaxis, panel_height)
p_proposed_scalefree <- hide_title_and_yaxis_and_legend(gp_proposed_scalefree)

p_random_legend <- g_grob(gp_igraph_random, 'guide-box')
p_scalefree_legend <- g_grob(gp_igraph_scalefree, 'guide-box')

ylab_width <- max(sum(p_igraph_ylab$widths), sum(p_proposed_ylab$widths)) + unit(1, 'mm')
yaxis_width <- sum(p_igraph_random_yaxis$widths) + unit(1, 'mm')
title_width <- (unit(1, 'npc') - 2*ylab_width - 2*yaxis_width) * 0.5
title_height <- max(sum(p_random_title$heights), sum(p_scalefree_title$heights)) + unit(1, 'mm')
legend_height <- sum(p_random_legend$heights)

cairo_pdf('dist-delete.pdf', width = 7,
          height = convertHeight(title_height+unit(5.0, 'inches')+legend_height, 'inches', TRUE))
grid.arrange(
  blank, blank, p_random_title, blank, p_scalefree_title, blank,
  p_igraph_ylab, p_igraph_random_yaxis, p_igraph_random, p_igraph_scalefree_yaxis, p_igraph_scalefree, blank,
  p_proposed_ylab, p_proposed_random_yaxis, p_proposed_random, p_proposed_scalefree_yaxis, p_proposed_scalefree, blank,
  blank, blank, p_random_legend, blank, p_scalefree_legend, blank,
  ncol = 6,
  nrow = 4,
  widths = unit.c(ylab_width, yaxis_width, title_width, yaxis_width, title_width, ylab_width),
  heights = unit.c(title_height, plot_height, plot_height, legend_height)
)
dev.off()

# padding
cairo_pdf('dist-delete-1-1.pdf',
          width  = convertWidth(ylab_width, 'inches', TRUE),
          height = convertHeight(title_height, 'inches', TRUE))
grid.draw(blank)
dev.off()
cairo_pdf('dist-delete-1-2.pdf',
          width  = convertWidth(yaxis_width, 'inches', TRUE),
          height = convertHeight(title_height, 'inches', TRUE))
grid.draw(blank)
dev.off()
cairo_pdf('dist-delete-2-1.pdf',
          width  = convertWidth(ylab_width, 'inches', TRUE),
          height = convertHeight(legend_height, 'inches', TRUE))
grid.draw(blank)
dev.off()
cairo_pdf('dist-delete-2-2.pdf',
          width  = convertWidth(yaxis_width, 'inches', TRUE),
          height = convertHeight(legend_height, 'inches', TRUE))
grid.draw(blank)
dev.off()
cairo_pdf('dist-delete-3-6.pdf',
          width  = convertWidth(ylab_width, 'inches', TRUE),
          height = convertHeight(panel_height, 'inches', TRUE))
grid.draw(blank)
dev.off()

# row 1 title
cairo_pdf('dist-delete-random-title.pdf',
          width = convertWidth(panel_width, 'inches', TRUE),
          height = convertHeight(title_height, 'inches', TRUE))
grid.draw(p_random_title)
dev.off()
cairo_pdf('dist-delete-scalefree-title.pdf',
          width = convertWidth(panel_width, 'inches', TRUE),
          height = convertHeight(title_height, 'inches', TRUE))
grid.draw(p_scalefree_title)
dev.off()

# row 2 legend
cairo_pdf('dist-delete-random-legend.pdf',
          width = convertWidth(panel_width, 'inches', TRUE),
          height = convertHeight(legend_height, 'inches', TRUE))
grid.draw(p_random_legend)
dev.off()
cairo_pdf('dist-delete-scalefree-legend.pdf',
          width = convertWidth(panel_width, 'inches', TRUE),
          height = convertHeight(legend_height, 'inches', TRUE))
grid.draw(p_scalefree_legend)
dev.off()

# row 3 igraph
cairo_pdf('dist-delete-igraph-ylab.pdf',
          width = convertWidth(ylab_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_igraph_ylab)
dev.off()
cairo_pdf('dist-delete-igraph-random-yaxis.pdf',
          width = convertWidth(yaxis_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_igraph_random_yaxis)
dev.off()
cairo_pdf('dist-delete-igraph-random.pdf',
          width = convertWidth(panel_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_igraph_random)
dev.off()
cairo_pdf('dist-delete-igraph-scalefree-yaxis.pdf',
          width = convertWidth(yaxis_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_igraph_scalefree_yaxis)
dev.off()
cairo_pdf('dist-delete-igraph-scalefree.pdf',
          width = convertWidth(panel_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_igraph_scalefree)
dev.off()

# row 4 proposed method
cairo_pdf('dist-delete-proposed-ylab.pdf',
          width = convertWidth(ylab_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_proposed_ylab)
dev.off()
cairo_pdf('dist-delete-proposed-ylab.pdf',
          width = convertWidth(ylab_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_proposed_ylab)
dev.off()
cairo_pdf('dist-delete-proposed-random-yaxis.pdf',
          width = convertWidth(yaxis_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_proposed_random_yaxis)
dev.off()
cairo_pdf('dist-delete-proposed-random.pdf',
          width = convertWidth(panel_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_proposed_random)
dev.off()
cairo_pdf('dist-delete-proposed-scalefree-yaxis.pdf',
          width = convertWidth(yaxis_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_proposed_scalefree_yaxis)
dev.off()
cairo_pdf('dist-delete-proposed-scalefree.pdf',
          width = convertWidth(panel_width, 'inches', TRUE),
          height = convertHeight(plot_height, 'inches', TRUE))
grid.draw(p_proposed_scalefree)
dev.off()
