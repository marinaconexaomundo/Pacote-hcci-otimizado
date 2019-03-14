#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

bool is_wholenumber(NumericVector x, double tol){
  NumericVector rounding = round(x,0);
  NumericVector subtracao = x - rounding;
  NumericVector absol = abs(subtracao);
  
  bool booliano = is_true(absol < tol);
  return wrap(booliano);
}

/*** R
set.seed(2019)
s <- rnorm(1)
is_wholenumber(s, .Machine$double.eps)
*/