library(dplyr)
library(ggplot2)

files <- list.files("bench/results", pattern = "*.rds")

readResults <- function(filename) {
  df <- readRDS(paste0("bench/results/", filename))
  df$file <- filename
  if (!("commit_idx" %in% colnames(df)))
    df$commit_idx <- -1
  df
}

results <- do.call(rbind, lapply(files, readResults))

results <- results %>%
  mutate(
    method = as.factor(attr(expression, "description")),
    result = as.integer(result),
    median = as.numeric(median),
    min = as.numeric(min)
  )

results %>%
  group_by(method, name) %>%
  arrange(file) %>%
  mutate(idx = seq(n())) %>%
  ungroup() %>%
  ggplot(aes(x = idx, y = median, color = method, group = method)) +
  geom_line() +
  facet_wrap(vars(name), scales = "free") +
  scale_y_log10()

metadata <- read.csv("bench/data/metadata.csv")
