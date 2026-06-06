Rscript -e 'Rcpp::compileAttributes(".")'
Rscript -e 'roxygen2::roxygenise()'
R CMD INSTALL .
