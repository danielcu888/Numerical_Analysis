#include <cstdlib>
#include <iostream>
#include "algorithm.h" /// @todo - do not structure libraries like this. We need to be able to say #include "algorithm/algorithm.h" here
#include <deque>
#include <memory>
#include <stdexcept>
#include <iomanip>

/// @todo - make this part of NumericalAnalysis library
namespace sequence
{
  template<typename T>
  class Sequence final /// @todo - rubbish name. Needs recurrence in it or something
  {
  public:

    explicit Sequence( const T& zeroth_term
                     , std::unique_ptr<algorithm::Algorithm<T>>&& algorithm
                     )
      : m_algorithm(std::move(algorithm))
      , m_terms({zeroth_term})
    {}

    Sequence(const Sequence&) = delete;
    Sequence& operator=(const Sequence&) = delete;
    Sequence(Sequence&&) = default;
    Sequence& operator=(Sequence&&) = default;
    ~Sequence() = default;

    void calculate_term(std::size_t n)
    {
      while (num_terms() < n+1)
      {
        calculate_next_term();
      }
    }

    const T& term(std::size_t n)
    {
      if (num_terms() < n+1)
      {
        throw std::out_of_range("Not in range!");
      }

      return m_terms.at(n);
    }

    std::size_t num_terms() const
    {
      return m_terms.size();
    }

    void print(std::ostream& os, std::size_t start_term = 0) const
    {
      os << "\"" << m_algorithm->name() << "\" sequence "
         << "(first " << num_terms() << " terms): "
         << std::endl;
      for (std::size_t i = start_term; i < num_terms(); ++i)
      {
        os << "Term #" << i << ": " << m_terms.at(i) << std::endl;
      }
    }

  private:

    void calculate_next_term()
    {
      m_terms.push_back(m_algorithm->execute(m_terms.back()));
    }

    std::unique_ptr<algorithm::Algorithm<T>> m_algorithm;
    std::deque<T> m_terms;

  }; // ! class Sequence

} // ! namespace sequence

template<typename T>
std::ostream& operator<<(std::ostream& os, const sequence::Sequence<T>& seq)
{
  seq.print(os);
  return os;
}

namespace test
{
  class MayAlgorithm final : public algorithm::Algorithm<double>
  {
  public:
    explicit MayAlgorithm(double k)
      : m_k(k)
    {}

    double execute(const double& in) const
    {
      return m_k*in*(1.0 - in);
    }

    const char* name() const
    {
      return "Robert May";
    }

  private:

    const double m_k;

  }; // ! class MayAlgorithm
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: <program name> <k>" << std::endl;
    return EXIT_FAILURE;
  }

  std::unique_ptr<algorithm::Algorithm<double>> a
    = std::make_unique<test::MayAlgorithm>(atof(argv[1]));

  sequence::Sequence<double> seq(0.2, std::move(a));
  seq.calculate_term(10000);
  seq.print(std::cout << std::setprecision(3), 9900);

  return EXIT_SUCCESS;
}
