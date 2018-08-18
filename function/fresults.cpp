#include "fresults.h"

#include <string>
#include <iostream>
#include <limits>

namespace function
{
  fresults::fresults( const std::string& name_
                    , double start_
                    , double end_
                    , double delta_
                    , func func_
                    )
    : m_name(name_)
    , m_start(start_)
    , m_end(end_)
    , m_delta(delta_)
    , m_function(func_)
    , m_results()
  {}

  void fresults::calculate( double start_
                          , double end_
                          , double delta_
                          , const func& function_
                          )
  {
    m_start = start_;
    m_end = end_;
    m_delta = delta_;
    m_function = function_;

    calculate_internal();
  }

  void fresults::calculate(double start_, double end_, double delta_)
  {
    m_start = start_;
    m_end = end_;
    m_delta = delta_;

    calculate_internal();
  }

  void fresults::calculate(double start_, double end_)
  {
    m_start = start_;
    m_end = end_;

    calculate_internal();
  }

  void fresults::calculate()
  {
    calculate_internal();
  }

  void fresults::set_start(double start_)
  {
    m_start = start_;
  }

  double fresults::start() const
  {
    return m_start;
  }

  void fresults::set_end(double end_)
  {
    m_end = end_;
  }

  double fresults::end() const
  {
    return m_end;
  }

  void fresults::set_delta(double delta_)
  {
    m_delta = delta_;
  }

  double fresults::delta() const
  {
    return m_delta;
  }

  void fresults::set_function(const func& function_)
  {
    m_function = function_;
  }

  fresults::func fresults::function() const
  {
    return m_function;
  }

  const std::string& fresults::name() const
  {
    return m_name;
  }

  void fresults::set_name(const std::string& name_)
  {
    m_name = name_;
  }

  void fresults::clear()
  {
    m_results.clear();
  }

  void fresults::calculate_internal()
  {
    clear();

    for (double x = m_start; x < m_end; x += m_delta)
    {
      const result r{x, m_function(x)};
      m_results.push_back(r);
    }
  }

  void fresults::print(std::ostream& os) const
  {
    for (const auto& r : m_results)
    {
      os << r.first << "\t"
         << r.second << std::endl;
    }
  }

  fresults::results fresults::get_results() const
  {
    return m_results;
  }

} // ! namespace function

std::ostream& operator<<(std::ostream& os, const function::fresults& results)
{
  const std::string n =results.name();
  const std::string::size_type sz = n.size();

  // header

  for (std::size_t i = 0; i < sz+4; ++i)
  {
    os << "#";
  }
  os << std::endl;

  os << "# " << n << " #" << std::endl;

  // footer
  for (std::size_t i = 0; i < sz+4; ++i)
  {
    os << "#";
  }
  os << std::endl;

  os << "# x\ty" << std::endl;

  results.print(os);
  return os;
}
