#pragma once

#include "utils.h"
#include <Eigen/Core>
#include <algorithm>
#include <numeric>
#include <vector>

namespace slope {

class Clusters
{
public:
  Clusters(const Eigen::VectorXd& beta);

  std::vector<int>::iterator begin(const int i);
  std::vector<int>::iterator end(const int i);
  std::vector<int>::const_iterator cbegin(const int i) const;
  std::vector<int>::const_iterator cend(const int i) const;
  int cluster_size(const int i) const;
  int pointer(const int i) const;
  int n_clusters() const;
  double coeff(const int i) const;
  void setCoeff(const int i, const double x);
  std::vector<double> coeffs() const;
  std::vector<int> indices() const;
  std::vector<int> pointers() const;
  void update(const int old_index, const int new_index, const double c_new);
  void update(const Eigen::VectorXd& beta);

private:
  std::vector<double> c;
  std::vector<int> c_ind;
  std::vector<int> c_ptr;

  void reorder(const int old_index, const int new_index);
  void merge(const int old_index, const int new_index);
};

} // namespace slope
