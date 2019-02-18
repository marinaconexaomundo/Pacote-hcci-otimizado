#include <RcppArmadillo.h>
using namespace Rcpp;


// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]
arma::mat mats(arma::mat X, List model, int method, NumericVector h , double k) {
  
  arma::mat V = X.t() * X;
  arma::mat bread_1 = inv(V) * X.t(); 
  arma::mat bread_2 = X * V.i();
  
  // criando a matriz error_hat
  NumericVector residuals =  model["residuals"];
  int dim = residuals.size();
  arma::mat error_hat = arma::zeros(dim,dim);
  
  NumericVector resi_2 = pow(residuals,2);
  NumericVector h_1 = 1 - h;
  // ainda a questao da matriz error_hat
  
  // criando o h usando quando method é 2, 3, 4 ou 5 no r
  
  // Quando method = 0
  if(method == 0){
    // NumericVector resi = pow(residuals,2);
  
    for (int i = 0; i < dim; i++){
      error_hat(i,i) = resi_2[i];
    }
    arma::mat omega = error_hat;
    arma::mat hc = bread_1 * omega * bread_2;
    
    return hc;
  }
  
  // Quando method == 2
  if(method == 2){
    NumericVector vetor = resi_2/h_1;
    
    for (int i = 0; i < dim; i++){
      error_hat(i,i) = vetor[i];
    }
    
    arma::mat omega = error_hat;
    arma::mat hc = bread_1 * omega * bread_2;
    return hc;
  }
  
  // Quando method = 3
  if(method == 3){
    
    NumericVector h_2 = pow(h_1,2);
    NumericVector vetor = resi_2/h_2;
    
    for (int i = 0; i < dim; i++){
      error_hat(i,i) = vetor[i];
    }
    
    arma::mat omega = error_hat;
    arma::mat hc = bread_1 * omega * bread_2;
    
    return hc;
  }
  
  // Quando method = 4
   if(method == 4){
   
    double media_h = mean(h);
    
    NumericVector vec = h/media_h;
    NumericVector delta = pmin(4, vec);
    
    arma::vec h_1d = arma::zeros(dim);
    
    for(int i = 0; i < dim; i++){
     h_1d[i] = pow(h_1[i],delta[i]);
    }
    
    arma::vec re = pow(residuals,2);
    arma::vec vetor = re/h_1d;
    
    for (int i = 0; i < dim; i++){
      error_hat(i,i) = vetor[i];
    }

    arma::mat omega = error_hat;
    arma::mat hc = bread_1 * omega * bread_2;
    
    
    return hc;
  }
   
  // Quando method = 5
  if(method == 5){
    
    double media_h = mean(h);
    
    NumericVector vec = h/media_h;
    double max_h = max(h);
    
    double vec_h = max_h/media_h;
     double vec_h_k = k * vec_h;
   
    // double four = 4;
    
    arma::vec maxmum = {4, vec_h_k};
    
    double max_h_k = max(maxmum);
    NumericVector alpha = pmin(vec, max_h_k);
    
    arma::vec h_1d = arma::zeros(dim);
    
    for(int i = 0; i < dim; i++){
      h_1d[i] = pow(h_1[i],alpha[i]);
    }

    arma::vec re = pow(residuals,2);
    arma::vec raiz_for_omega = h_1d; 
    arma::vec vetor = re/raiz_for_omega;
    
    for (int i = 0; i < dim; i++){
      error_hat(i,i) = vetor[i];
    }
    
    arma::mat omega = error_hat;
    arma::mat hc = bread_1 * omega * bread_2;
    
    return hc;
  }
  
}


 /*** R
  k = 0.7
  mats(X = M, model = modelo, method = 5,  h = h, k = k)
*/
