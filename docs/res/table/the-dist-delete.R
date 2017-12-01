library(readr)
library(tidyr)
library(dplyr)
library(ggplot2)
library(gridExtra)

type_breaks = c('random', 'scale-free')
alg_breaks = c('proposed', 'igraph')
data <- read_csv('dist-delete-mws.csv') %>%
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
  title <- ifelse(valg == 'igraph',
                  ifelse(vtype == 'random',
                         'ランダムネットワーク',
                         'スケールフリーネットワーク'),
                  '')
  title_ylab <- ifelse(vtype == 'random',
                       ifelse(valg == 'proposed',
                              '提案手法[s]',
                              'igraphライブラリ[s]'),
                       '')
  title_xlab <- ifelse(valg == 'proposed', '頂点数', '')
  gp <- ggplot(
    filter(data, type == vtype, alg == valg),
    aes(n, time, colour = as.factor(ifelse(type == 'random', p, m)))) +
    ggtitle(title) +
    geom_line() +
    geom_point() +
    scale_x_continuous(name = title_xlab) +
    scale_y_continuous(name = title_ylab, labels = function(y) format(y, nsmall = 2)) +
    labs(colour = ifelse(vtype == 'random', 'p', 'm')) +
    theme(text = element_text(family = 'IPAexGothic', size = 10),
          panel.background = element_rect(fill = 'white', colour = 'grey80'),
          panel.grid.major = element_line(colour = 'grey80'),
          panel.grid.minor = element_line(colour = 'grey80'),
          axis.ticks = element_line(colour = 'grey80'),
          axis.title.x = if(title_xlab == '') element_blank() else element_text(),
          axis.text.x = if(title_xlab == '') element_blank() else element_text(),
          axis.ticks.x = if(title_xlab == '') element_blank() else element_line(),
          legend.position = ifelse(valg == 'proposed', 'bottom', 'none'))
  return(gp)
}

cairo_pdf('the-dist-delete.pdf',
          width = 7, height = 5, pointsize = 10)
grid.arrange(
  pf('random', 'igraph'), pf('scale-free', 'igraph'),
  pf('random', 'proposed'), pf('scale-free', 'proposed'),
  ncol = 2)
dev.off()
