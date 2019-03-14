#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

double is_wholenumber(NumericVector x, double tol){
  NumericVector rounding = round(x,0);
  NumericVector subtracao = x - rounding;
  NumericVector absol = abs(subtracao);
  
  double first = absol[1];
  double avaliando = first - tol;
  
  return avaliando;
}
 