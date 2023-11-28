#pragma once

#include <algorithm> // std::sort
#include <numeric>   // std::iota
#include <string>
#include <vector>

namespace slope {

template<typename T>
void
sort(T& v, const bool descending = false)
{
  if (descending) {
    std::sort(v.data(), v.data() + v.size(), std::greater<double>());
  } else {
    std::sort(v.data(), v.data() + v.size(), std::less<double>());
  }
}

template<typename T>
std::vector<int>
sortIndex(T& v, const bool descending = false)
{
  using namespace std;

  vector<int> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  if (descending) {
    sort(idx.begin(), idx.end(), [&v](int i, int j) { return v[i] > v[j]; });
  } else {
    sort(idx.begin(), idx.end(), [&v](int i, int j) { return v[i] < v[j]; });
  }

  return idx;
}

template<typename T>
void
permute(T& values, const std::vector<int>& ind)
{
  T out(values.size());

  for (int i = 0; i < values.size(); ++i)
    out[i] = std::move(values[ind[i]]);

  values = std::move(out);
}

template<typename T>
void
inversePermute(T& values, const std::vector<int>& ind)
{
  T out(values.size());

  for (int i = 0; i < values.size(); ++i)
    out[ind[i]] = std::move(values[i]);

  values = std::move(out);
}

template<typename T>
void
move_elements(std::vector<T>& v, const int from, const int to, const int size)
{
  // if (from > to)
  //   std::rotate(v.rend() - from - size, v.rend() - from, v.rend() - to);
  // else
  //   std::rotate(
  //     v.begin() + from, v.begin() + from + size, v.begin() + to + size);

  if (from > to) {
    std::rotate(v.begin() + to, v.begin() + from, v.begin() + from + size);
  } else {
    std::rotate(v.begin() + from, v.begin() + from + size, v.begin() + to + 1);
  }
}
}
