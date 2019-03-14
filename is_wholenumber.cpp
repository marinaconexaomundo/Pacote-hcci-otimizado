#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

float is_wholenumber(NumericVector x, double tol){
  NumericVector rounding = round(x,0);
  NumericVector subtracao = x - rounding;
  NumericVector absol = abs(subtracao);
  
  float avaliando = absol[1] - tol;
  
  return avaliando;
}