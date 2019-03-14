#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

bool is_wholenumber(NumericVector x, double tol){
  // for(int i = 0; i < x.size(); i++)
  return wrap(abs(x - round(x,0)) < tol);
}

/*** R
s <- rnorm(1)
is_wholenumber(s, .Machine$double.eps)
*/