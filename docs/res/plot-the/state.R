library(readr)
library(dplyr)
library(ggplot2)
library(extrafont)
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

breaks <- c('basic', 'cycle', 'stree', 'minmax')
labels <- c('基本', '閉路', '全域木', '枝刈り')
data <- read_csv('../data/the-cmp-algo-lab.csv') %>%
  filter(sorted == 'basic', ginitr == 'basic' | sinitr == 'basic') %>%
  mutate(mtd = ifelse(ginitr == 'basic', sinitr, ginitr)) %>%
  filter(is.element(mtd, breaks)) %>%
  group_by(n, d, mtd, n_state) %>%
  summarise(mean_time = mean(time)) %>%
  ungroup() %>%
  mutate(mtd = factor(mtd, levels = breaks),
         d = factor(d))

pf_state <- function(vd) {
  gp <- ggplot(data %>% filter(d == vd),
               aes(x = n, y = n_state, color = mtd)) +
    geom_line() +
    geom_point() +
    scale_x_continuous(name = '頂点数',
                       minor_breaks = NULL) +
    scale_y_continuous(name = '展開状態数',
                       trans = 'log10') +
    scale_color_discrete(name = NULL,
                         breaks = breaks,
                         labels = labels) +
    theme(
      text = element_text(size = 9),
      plot.margin = unit(c(3, 3, 1, 3), 'mm')
    )
  return(gp)
}

plot_height <- 3
cairo_pdf('state.pdf', width = 4.2, height = plot_height)
pf_state(3)
seekViewport('panel.6-4-6-4')
panel_width <- convertWidth(unit(1, 'npc'), 'inches')
#panel_width <- unit(2, 'inches')
panel_height <- convertHeight(unit(1, 'npc'), 'inches')
seekViewport('layout')
dev.off()

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

legend_width <- sum(p_state_legend$widths)
ylab_width <- sum(p_state_ylab$widths)
yaxis_width <- sum(p_state_d3_yaxis$widths)

# state
cairo_pdf('state-lpad.pdf',
          width = convertWidth(sum(p_state_legend$widths) - ylab_width - unit(2, 'mm'), 'inches', TRUE), height = plot_height)
grid.draw(blank)
dev.off()
cairo_pdf('state-ylab.pdf', width = convertWidth(ylab_width + unit(2, 'mm'), 'inches', TRUE), height = plot_height)
grid.draw(p_state_ylab)
dev.off()
cairo_pdf('state-d3-yaxis.pdf', width = convertWidth(yaxis_width, 'inches', TRUE), height = plot_height)
grid.draw(p_state_d3_yaxis)
dev.off()
cairo_pdf('state-d3.pdf', width = convertWidth(panel_width, 'inches', TRUE), height = plot_height)
grid.draw(p_state_d3)
dev.off()
cairo_pdf('state-d4-yaxis.pdf', width = convertWidth(yaxis_width, 'inches', TRUE), height = plot_height)
grid.draw(p_state_d4_yaxis)
dev.off()
cairo_pdf('state-d4.pdf', width = convertWidth(panel_width, 'inches', TRUE), height = plot_height)
grid.draw(p_state_d4)
dev.off()
cairo_pdf('state-legend.pdf', width = convertWidth(sum(p_state_legend$widths), 'inches', TRUE), height = plot_height)
grid.draw(p_state_legend)
dev.off()
