#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

bool is_wholenumber(NumericVector x, double tol){
  NumericVector rounding = round(x,0);
  return wrap(abs(x - rounding) < tol);
}

/*** R
set.seed(2019)
s <- rnorm(1)
is_wholenumber(s, .Machine$double.eps)
*/