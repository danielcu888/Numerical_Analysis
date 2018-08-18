#ifndef GUARD_FRESULTS_H_
#define GUARD_FRESULTS_H_

#include <string>
#include <functional>
#include <vector>
#include <utility>
#include <iosfwd>

namespace function
{

  class fresults final
  {
    using result = std::pair<double, double>;
    using results = std::vector<result>;
    using func = std::function<double(double)>;

  public:
    fresults( const std::string& name_ = ""
            , double start_ = 0.0
            , double end_ = 0.0
            , double delta_ = 0.0
            , func func_ = nullptr
            );
    fresults(const fresults&) = default;
    fresults& operator=(const fresults&) = default;
    fresults(fresults&&) = default;
    fresults& operator=(fresults&&) = default;
    ~fresults() = default;

    void calculate(double start_, double end_, double delta_, const func& func_);
    void calculate(double start_, double end_, double delta_);
    void calculate(double start_, double end_);
    void calculate();

    void set_start(double start_);
    double start() const;

    void set_end(double end_);
    double end() const;

    void set_delta(double delta_);
    double delta() const;

    void set_function(const func& function_);
    func function() const;

    const std::string& name() const;
    void set_name(const std::string& name_);

    results get_results() const;
    void calculate_internal();

    void print(std::ostream& os) const;

  private:
    void clear();

    std::string m_name;
    double m_start;
    double m_end;
    double m_delta;
    func m_function;
    results m_results;

  }; // ! class fresults

} // ! namespace function

std::ostream& operator<<(std::ostream& os, const function::fresults& results);

#endif
