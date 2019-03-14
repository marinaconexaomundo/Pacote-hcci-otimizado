#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

double is_wholenumber(NumericVector x, double tol){
  NumericVector rounding = round(x,0);
  NumericVector subtracao = x - rounding;
  NumericVector absol = abs(subtracao);
  
  // para avaliar se eh menor tenho como fazer dessa forma
  // int i = 1;
  double avaliando = absol[1] - tol;
  
  return avaliando;
}

/*** R
set.seed(2019)
s <- rnorm(1)
is_wholenumber(s, .Machine$double.eps)
*/