library(readr)
library(dplyr)
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

hide_yaxis_and_legend <- function(gp) {
  return(gp + theme(
    plot.margin = unit(c(3, 1, 1, 0), 'mm'),
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
      p_height,
      unit(1, 'npc') - p_height - unit(3, 'mm')
    ),
    widths = unit.c(sum(gp$widths))
  )
  return(g)
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

breaks_full <- c('basic', 'cycle', 'stree')
labels_full <- c('基本', '閉路', '全域木')
data_full <- read_csv('../data/the-cmp-algo-full-lab.csv') %>%
  filter(mgr == 'basic', srt == 'basic') %>%
  mutate(mtd = bdr) %>%
  select(n, d, mtd, n_graph) %>%
  mutate(mtd = factor(mtd, levels = breaks_full),
         d = factor(d))

pf_time <- function(vd) {
  gp <- ggplot(data %>% filter(d == vd),
               aes(x = n, y = mean_time, color = mtd, shape = mtd, linetype = mtd)) +
    geom_line() +
    geom_point() +
    scale_x_continuous(name = '頂点数',
                       minor_breaks = NULL) +
    scale_y_continuous(name = '平均探索時間[s]',
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
    theme(
      text = element_text(size = 9),
      plot.margin = unit(c(3, 3, 1, 3), 'mm')
    )
  return(gp)
}
pf_state <- function(vd) {
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
    theme(
      text = element_text(size = 9),
      plot.margin = unit(c(3, 3, 1, 3), 'mm')
    )
  return(gp)
}
pf_ngraph <- function(vd) {
  gp <- ggplot(data_full %>% filter(d == vd), aes(n, n_graph, color = mtd)) +
    geom_line() +
    geom_point() +
    scale_x_continuous(name = '頂点数',
                       minor_breaks = NULL) +
    scale_y_continuous(name = '総グラフ数',
                       trans = 'log10') +
    scale_color_manual(name = '初期グラフ',
                       breaks = breaks_full,
                       labels = labels_full,
                       values = c('#F8766D', '#619CFF', '#00BA38')) +
    theme(
      text = element_text(size = 9),
      plot.margin = unit(c(3, 3, 1, 3), 'mm')
    )
  return(gp)
}

plot_height <- 2.5
cairo_pdf('ginitr.pdf', width = 3.6, height = plot_height)
pf_time(3)
seekViewport('panel.6-4-6-4')
#panel_width <- convertWidth(unit(1, 'npc'), 'inches')
panel_width <- unit(2, 'inches')
panel_height <- convertHeight(unit(1, 'npc'), 'inches')
seekViewport('layout')
dev.off()

gp_time_d3 <- pf_time(3)
gp_time_d4 <- pf_time(4)
gp_time_ylab <- g_grob(gp_time_d3, 'axis.title.y')
p_time_ylab <- make_margin(gp_time_ylab, panel_height)
gp_time_d3_yaxis <- g_filter(gp_time_d3, 'axis-l')
p_time_d3_yaxis <- make_margin(gp_time_d3_yaxis, panel_height)
p_time_d3 <- hide_yaxis_and_legend(gp_time_d3)
gp_time_d4_yaxis <- g_filter(gp_time_d4, 'axis-l')
p_time_d4_yaxis <- make_margin(gp_time_d4_yaxis, panel_height)
p_time_d4 <- hide_yaxis_and_legend(gp_time_d4)
gp_time_legend <- g_grob(gp_time_d3, 'guide-box')
p_time_legend <- make_margin(gp_time_legend, panel_height)

gp_state_d3 <- pf_state(3)
gp_state_d4 <- pf_state(4)
gp_state_ylab <- g_grob(gp_state_d3, 'axis.title.y')
p_state_ylab <- make_margin(gp_state_ylab, panel_height)
gp_state_d3_yaxis <- g_filter(gp_state_d3, 'axis-l')
p_state_d3_yaxis <- make_margin(gp_state_d3_yaxis, panel_height)
p_state_d3 <- hide_yaxis_and_legend(gp_state_d3)
gp_state_d4_yaxis <- g_filter(gp_state_d4, 'axis-l')
p_state_d4_yaxis <- make_margin(gp_state_d4_yaxis, panel_height)
p_state_d4 <- hide_yaxis_and_legend(gp_state_d4)
gp_state_legend <- g_grob(gp_state_d3, 'guide-box')
p_state_legend <- make_margin(gp_state_legend, panel_height)

gp_ngraph_d3 <- pf_ngraph(3)
gp_ngraph_d4 <- pf_ngraph(4)
gp_ngraph_ylab <- g_grob(gp_ngraph_d3, 'axis.title.y')
p_ngraph_ylab <- make_margin(gp_ngraph_ylab, panel_height)
gp_ngraph_d3_yaxis <- g_filter(gp_ngraph_d3, 'axis-l')
p_ngraph_d3_yaxis <- make_margin(gp_ngraph_d3_yaxis, panel_height)
p_ngraph_d3 <- hide_yaxis_and_legend(pf_ngraph(3))
gp_ngraph_d4_yaxis <- g_filter(gp_ngraph_d4, 'axis-l')
p_ngraph_d4_yaxis <- make_margin(gp_ngraph_d4_yaxis, panel_height)
p_ngraph_d4 <- hide_yaxis_and_legend(pf_ngraph(4))
gp_ngraph_legend <- g_grob(gp_ngraph_d3, 'guide-box')
p_ngraph_legend <- make_margin(gp_ngraph_legend, panel_height)

legend_width <- max(sum(p_time_legend$widths), sum(p_state_legend$widths), sum(p_ngraph_legend$widths))
ylab_width <- sum(p_time_ylab$widths)
yaxis_width <- sum(p_time_d3_yaxis$widths)

cairo_pdf('ginitr.pdf', width = 5.2, height = 7.5)
grid.arrange(
  blank, p_time_ylab, p_time_d3_yaxis, p_time_d3, p_time_d4_yaxis, p_time_d4, p_time_legend,
  blank, p_state_ylab, p_state_d3_yaxis, p_state_d3, p_state_d4_yaxis, p_state_d4, p_state_legend,
  blank, p_ngraph_ylab, p_ngraph_d3_yaxis, p_ngraph_d3, p_ngraph_d4_yaxis, p_ngraph_d4, p_ngraph_legend,
  ncol = 7,
  widths = unit.c(
    legend_width - ylab_width,
    ylab_width,
    yaxis_width,
    (unit(1, 'npc') - 2*legend_width - 2*yaxis_width) * 0.5,
    yaxis_width,
    (unit(1, 'npc') - 2*legend_width - 2*yaxis_width) * 0.5,
    legend_width
  ),
  padding = unit(0, 'npc')
)
dev.off()

# ginitr-time
cairo_pdf('ginitr-time-lpad.pdf',
          width = convertWidth(sum(p_time_legend$widths) - ylab_width - unit(2, 'mm'), 'inches', TRUE), height = plot_height)
grid.draw(blank)
dev.off()
cairo_pdf('ginitr-time-ylab.pdf', width = convertWidth(ylab_width + unit(2, 'mm'), 'inches', TRUE), height = plot_height)
grid.draw(p_time_ylab)
dev.off()
cairo_pdf('ginitr-time-d3-yaxis.pdf', width = convertWidth(yaxis_width, 'inches', TRUE), height = plot_height)
grid.draw(p_time_d3_yaxis)
dev.off()
cairo_pdf('ginitr-time-d3.pdf', width = convertWidth(panel_width, 'inches', TRUE), height = plot_height)
grid.draw(p_time_d3)
dev.off()
cairo_pdf('ginitr-time-d4-yaxis.pdf', width = convertWidth(yaxis_width, 'inches', TRUE), height = plot_height)
grid.draw(p_time_d4_yaxis)
dev.off()
cairo_pdf('ginitr-time-d4.pdf', width = convertWidth(panel_width, 'inches', TRUE), height = plot_height)
grid.draw(p_time_d4)
dev.off()
cairo_pdf('ginitr-time-legend.pdf', width = convertWidth(sum(p_time_legend$widths), 'inches', TRUE), height = plot_height)
grid.draw(p_time_legend)
dev.off()

# ginitr-state
cairo_pdf('ginitr-state-lpad.pdf',
          width = convertWidth(sum(p_state_legend$widths) - ylab_width - unit(2, 'mm'), 'inches', TRUE), height = plot_height)
grid.draw(blank)
dev.off()
cairo_pdf('ginitr-state-ylab.pdf', width = convertWidth(ylab_width + unit(2, 'mm'), 'inches', TRUE), height = plot_height)
grid.draw(p_state_ylab)
dev.off()
cairo_pdf('ginitr-state-d3-yaxis.pdf', width = convertWidth(yaxis_width, 'inches', TRUE), height = plot_height)
grid.draw(p_state_d3_yaxis)
dev.off()
cairo_pdf('ginitr-state-d3.pdf', width = convertWidth(panel_width, 'inches', TRUE), height = plot_height)
grid.draw(p_state_d3)
dev.off()
cairo_pdf('ginitr-state-d4-yaxis.pdf', width = convertWidth(yaxis_width, 'inches', TRUE), height = plot_height)
grid.draw(p_state_d4_yaxis)
dev.off()
cairo_pdf('ginitr-state-d4.pdf', width = convertWidth(panel_width, 'inches', TRUE), height = plot_height)
grid.draw(p_state_d4)
dev.off()
cairo_pdf('ginitr-state-legend.pdf', width = convertWidth(sum(p_state_legend$widths), 'inches', TRUE), height = plot_height)
grid.draw(p_state_legend)
dev.off()

# ginitr-ngraph
cairo_pdf('ginitr-ngraph-lpad.pdf',
          width = convertWidth(sum(p_ngraph_legend$widths) - ylab_width - unit(2, 'mm'), 'inches', TRUE), height = plot_height)
grid.draw(blank)
dev.off()
cairo_pdf('ginitr-ngraph-ylab.pdf', width = convertWidth(ylab_width + unit(2, 'mm'), 'inches', TRUE), height = plot_height)
grid.draw(p_ngraph_ylab)
dev.off()
cairo_pdf('ginitr-ngraph-d3-yaxis.pdf', width = convertWidth(yaxis_width, 'inches', TRUE), height = plot_height)
grid.draw(p_ngraph_d3_yaxis)
dev.off()
cairo_pdf('ginitr-ngraph-d3.pdf', width = convertWidth(panel_width, 'inches', TRUE), height = plot_height)
grid.draw(p_ngraph_d3)
dev.off()
cairo_pdf('ginitr-ngraph-d4-yaxis.pdf', width = convertWidth(yaxis_width, 'inches', TRUE), height = plot_height)
grid.draw(p_ngraph_d4_yaxis)
dev.off()
cairo_pdf('ginitr-ngraph-d4.pdf', width = convertWidth(panel_width, 'inches', TRUE), height = plot_height)
grid.draw(p_ngraph_d4)
dev.off()
cairo_pdf('ginitr-ngraph-legend.pdf', width = convertWidth(sum(p_ngraph_legend$widths), 'inches', TRUE), height = plot_height)
grid.draw(p_ngraph_legend)
dev.off()
