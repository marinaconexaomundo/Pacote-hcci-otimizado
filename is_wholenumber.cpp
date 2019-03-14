#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

NumericVector is_wholenumber(NumericVector x, double tol){
  NumericVector rounding = round(x,0);
  NumericVector subtracao = x - rounding;
  NumericVector absol = abs(subtracao);
  
  // arma::vec y = x;
  
  NumericVector avaliando;
  for(int i = 0; i < x.size(); i++){
  avaliando[i] = absol[i] - tol;
  }
  return avaliando;
}

/*** R
set.seed(2019)
s <- rnorm(20,100,100)
is_wholenumber(s, .Machine$double.eps)
*/