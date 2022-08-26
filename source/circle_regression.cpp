#include<iostream>
#include<vector>
#include <random>
#include <cmath>

#include "figures.hpp"

using namespace std;

//function to generate a random vector like linspace with python
vector<double> linspace (double x_start, double x_end, double n_points){
	vector<double> vec;
	if (n_points == 0) return vec;
	if (n_points == 1){
		vec.push_back(x_start);
		return vec;
	}
	double pas = (x_end - x_start)/(n_points - 1);
	for(int i=0;i<n_points-1;i++){
		vec.push_back(x_start + pas*i);
	}
	vec.push_back(x_end);
	return vec;
}
//Function to generate a random vector between a min and a max value
vector<double> random_randn(int taille, int min, int max){
	vector<double> vec;
	random_device theta;
	default_random_engine eng(theta());
	uniform_real_distribution<double> distr(min, max);
    	for (int n=0; n<taille; ++n) {
    		vec.push_back(distr(eng));
    	}
    	return vec;
}
//Function to soustract two vectors
vector<double> soustraction(vector<double> x, vector<double> y){
	vector<double> soust;
	for(int q=0;q<x.size();q++){
		soust.push_back(x[q] - y[q]);
	}
	return soust;
}
//Function to calcule the power of vector
vector<double> PowerVector(vector<double> vec, int power){
	vector<double> ress;
	for(int i=0;i<vec.size();i++){
		ress.push_back(pow(vec[i],power));
	}
	return ress;
}
//Function circle model : (n,1) - (n,1)
vector<double> circle_model(vector<double> x, vector<double> r){
	vector<double> vec, res;
	vec = soustraction(PowerVector(r,2), PowerVector(x,2));
	for(int i=0;i<vec.size();i++){
		res.push_back(sqrt(abs(vec[i])));
	}
	return res;
}
//Cost Function to return the error
double cost_function(vector<double> x, vector<double> r, vector<double> y){
	int m=y.size(); vector<double> vec; double erreur(0);
	vec = PowerVector((soustraction(circle_model(x, r), y)), 2);
	for(int i=0;i<vec.size();i++){
		erreur = erreur + vec[i];
	}
	return erreur/(2*m);
}
//Gradient function 
vector<double> gradient(vector<double> x, vector<double> r, vector<double> y){
	int m=y.size(); vector<double> vec, vec2, mod, res; double somme(0);
	mod = circle_model(x, r);
	for(int i=0;i<r.size();i++){
		somme = somme + r[i]*y[i];
	}
	for(int j=0;j<mod.size();j++){
		vec.push_back(somme/mod[j]);
	}
	vec2 = soustraction(r, vec);
	for(int q=0;q<r.size();q++){
		res.push_back(vec2[q]/m);
	}
	return res;
}
//Descente of the gradient
vector<double> gradient_desc(vector<double> x, vector<double> r, vector<double> y, int iter){
	vector<double> r_final, err; int i(0);
	double erreur; int rouge[3] = {1, 0, 0};
	while(i<iter){
		//erreur = 4 - cost_function(x, r, y);
		//cout << "error: " << erreur << endl;
		//err.push_back(erreur);
		r_final = soustraction(r, gradient(x, r, y));
		r = r_final;
		i++;
	}
	//plot(linspace (0.0, 10.0, err.size()), err, rouge, L"Learning graph", L"X axis", L"Erreur(%)", "erreur"); //if we want to plot the error
	return r_final;
}
//Function to print a vector type double on the screen
void print_vector(vector<double> vect){
	cout << "size : " << vect.size() << endl;
	for(double n : vect){
		cout << n << " ";
	}
	cout << endl;
}


