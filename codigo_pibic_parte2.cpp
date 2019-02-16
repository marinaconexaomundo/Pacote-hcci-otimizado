#include <RcppArmadillo.h>
using namespace Rcpp;


// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::mat mats(arma::mat X, List model, int method, NumericVector h ) {
  
  arma::mat V = X.t() * X;
  arma::mat bread_1 = inv(V) * X.t(); 
  arma::mat bread_2 = X * V.i();
  
  

  
  // criando o h usando quando method é 2, 3, 4 ou 5 no r
  
  // Quando method = 0
  if(method == 0){
    
    // criando a matriz error_hat
    NumericVector residuals =  model["residuals"];
    int dim = residuals.size();
    arma::mat error_hat = arma::zeros(dim,dim);
    // ainda a questao da matriz error_hat
    
    NumericVector resi = pow(residuals,2);
  
    for (int i = 0; i < dim; i++){
      error_hat(i,i) = resi[i];
    }
    arma::mat omega = error_hat;
    arma::mat hc = bread_1 * omega * bread_2;
    
    return hc;
  }
  
  // Quando method == 2
  if(method == 2){
    // criando a matriz error_hat
    NumericVector residuals =  model["residuals"];
    int dim = residuals.size();
    arma::mat error_hat = arma::zeros(dim,dim);
    // ainda a questao da matriz error_hat
    
    // nao eh vetoriazado ou seja, passar um for aqui
    NumericVector resi_2 = pow(residuals,2);
    NumericVector h_1 = 1 - h;
    
    NumericVector vetor = resi_2/h_1;
    
    for (int i = 0; i < dim; i++){
      error_hat(i,i) = vetor[i];
    }
    
    arma::mat omega = error_hat;
    arma::mat hc = bread_1 * omega * bread_2;
    return hc;
  }
  
  
  // return hc;
  
}


 /*** R
  mats(X = M, model = modelo, method = 2,  h = h)
*/
