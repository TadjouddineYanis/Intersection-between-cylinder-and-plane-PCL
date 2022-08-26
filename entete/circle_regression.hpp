std::vector<double> random_randn(int taille, int min, int max);
std::vector<double> soustraction(std::vector<double> x, std::vector<double> y);
std::vector<double> PowerVector(std::vector<double> vec, int power);
std::vector<double> circle_model(std::vector<double> x, std::vector<double> r);
double cost_function(std::vector<double> x, std::vector<double> r, std::vector<double> y);
std::vector<double> gradient(std::vector<double> x, std::vector<double> r, std::vector<double> y);
std::vector<double> gradient_desc(std::vector<double> x, std::vector<double> r, std::vector<double> y, int iter);
void print_vector(std::vector<double> vect);
std::vector<double> linspace (double x_start, double x_end, double n_points);




