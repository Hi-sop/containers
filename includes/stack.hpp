#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template <typename _T, typename _Container = vector<_T> >
	class stack
	{
		public:
			typedef _Container container_type;
			typedef typename container_type::value_type value_type;
			typedef typename container_type::size_type size_type;

		protected:
			container_type c;


		public:
			explicit stack(const container_type& __c = container_type())
				: c(__c) 
			{
			}

			bool empty() const
			{
				return c.empty();
			}

			size_type size() const
			{
				return c.size();
			}

			value_type& top()
			{
				return c.back();
			}

			const value_type& top() const
			{
				return c.back();
			}

			void push(const value_type& val)
			{
				return c.push_back(val);
			}

			void pop() 
			{
				c.pop_back();
			}

			template <typename T, typename C>
			friend bool operator==
			(const stack<T, C>& lhs, const stack<T, C>& rhs);
  
			template <typename T, typename C>
			friend bool operator<
			(const stack<T, C>& lhs, const stack<T, C>& rhs);
	};


	template <typename T, typename C>
	inline bool operator==(const stack<T, C>& lhs, const stack<T, C>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template <typename T, typename C>
	inline bool operator!=(const stack<T, C>& lhs, const stack<T, C>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename C>
	inline bool operator<(const stack<T, C>& lhs, const stack<T, C>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <typename T, typename C>
	inline bool operator<=(const stack<T, C>& lhs, const stack<T, C>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename C>
	inline bool operator>(const stack<T, C>& lhs, const stack<T, C>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename C>
	inline bool operator>=(const stack<T, C>& lhs, const stack<T, C>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
