#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::mat mats2(arma::mat X) {
  
  arma::mat V = X.t() * X;
  arma::mat bread2 = X * V.i();
  
  return bread2;
  
}


// /*** R
// mats2(M)
// */