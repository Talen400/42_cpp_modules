#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>

class SpanFullException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "Span is full";
		}
};

class NoSpanException : public std::exception {
	public:
		virtual const char* what() const throw() {
			return "not enough numbers to find a span";
		}
};

class Span {
	private:
		unsigned int _maxSize;
		std::vector<int> _numbers;

		Span();

	public:
		Span(unsigned int n);
		Span(const Span& other);
		~Span();
		Span& operator=(const Span& other);

		void addNumber(int num);

		template <typename InputIterator>
		void addNumber(InputIterator begin, InputIterator end) {
			while (begin != end) {
				addNumber(*begin);
				++begin;
			}
		}

		int shortestSpan() const;
		int longestSpan() const;

		unsigned int size() const;
};

#endif
