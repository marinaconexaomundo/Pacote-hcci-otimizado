#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::vec vector_escalar(arma::vec x, double y) {
  arma::vec vetor = arma::zeros(x.size());
  for(int i = 0; i < x.size(); i++) vetor[i] = pow(x[i],y);
  return vetor;
}

