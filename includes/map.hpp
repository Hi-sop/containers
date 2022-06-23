#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

#include "__tree.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{

	template <typename _Key, typename _T, typename _Compare = std::less<_Key>,
			 typename _Alloc = std::allocator<ft::pair<const _Key, _T> > >
	class map
	{
		public:
			typedef _Key key_type;
			typedef _T mapped_type;
			typedef _Compare key_compare;
			typedef _Alloc allocator_type;
			typedef ft::pair<const key_type, mapped_type> value_type;

		private:
			typedef __tree<key_type, value_type, ft::select_first<value_type>,
					key_compare, allocator_type>
			__base;

		public:
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;

			typedef typename __base::iterator iterator;
			typedef typename __base::const_iterator const_iterator;
			typedef typename __base::reverse_iterator reverse_iterator;
			typedef typename __base::const_reverse_iterator const_reverse_iterator;
			typedef typename __base::difference_type difference_type;
			typedef typename __base::size_type size_type;

		class value_compare 
			: public std::binary_function<value_type, value_type, bool>
		{
    		friend class map<_Key, _T, _Compare, _Alloc>;

			protected:
			_Compare comp;
			value_compare(_Compare c) : comp(c) 
			{
			}

			public:
			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		private:
			__base __tree_;

		public:
		
		explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: __tree_(comp, alloc)
		{
		}

		template <typename _InputIterator>
		map(_InputIterator first, _InputIterator last, 
		const key_compare& comp = key_compare(), 
		const allocator_type& alloc = allocator_type())
		: __tree_(comp, alloc)
		{
			__tree_.insert_range(first, last);
		}

		map(const map& other) : __tree_(other.__tree_) 
		{
		}

		map& operator=(const map& other)
		{
			if (this != &other)
			{
				__tree_ = other.__tree_;
			}
			return *this;
		}

		~map()
		{
		}


 
		iterator begin() throw() 
		{ 
			return iterator(__tree_.begin());
		}

		const_iterator begin() const throw()
		{
			return const_iterator(__tree_.begin());
		}

		iterator end() throw()
		{
			return iterator(__tree_.end());
		}

		const_iterator end() const throw()
		{
			return const_iterator(__tree_.end());
		}

		reverse_iterator rbegin() throw()
		{
			return __tree_.rbegin();
		}

		const_reverse_iterator rbegin() const throw()
		{
			return __tree_.rbegin();
		}

		reverse_iterator rend() throw()
		{
			return __tree_.rend();
		}

		const_reverse_iterator rend() const throw()
		{
			return __tree_.rend();
		}

		bool empty() const throw() 
		{
			return __tree_.empty();
		}

		size_type size() const throw()
		{
			return __tree_.size();
		}

		size_type max_size() const throw()
		{
			return __tree_.max_size();
		}

		mapped_type& operator[](const key_type& k)
		{
			iterator __it = lower_bound(k);

			if (__it == end() || key_compare()(k, (*__it).first))
				__it = insert(__it, value_type(k, mapped_type()));
			return (*__it).second;
		}

		mapped_type& at(const key_type& k)
		{
			iterator __it = lower_bound(k);

			if (__it == end() || key_compare()(k, (*__it).first))
				throw std::out_of_range("map: out of range");
			return (*__it).second;
		}

		const mapped_type& at(const key_type& k) const 
		{
			iterator __it = lower_bound(k);
			
			if (__it == end() || key_compare()(k, (*__it).first))
				throw std::out_of_range("map: out of range");
			return (*__it).second;
		}

		pair<iterator, bool> insert(const value_type& val)
		{
			return __tree_.insert_unique(val);
		}

		iterator insert(iterator position, const value_type& val)
		{
			return __tree_.insert_unique_with_hint(position, val);
		}

		template <typename _InputIterator>
		void insert(_InputIterator first, _InputIterator last) 
		{
			__tree_.insert_range(first, last);
		}

		void erase(iterator position)
		{
			__tree_.erase(position);
		}

		size_type erase(const key_type& k)
		{
			return __tree_.erase(k);
		}

		void erase(iterator first, iterator last)
		{
			__tree_.erase(first, last);
		}

		void swap(map& other)
		{
			__tree_.swap(other.__tree_);
		}

		void clear()
		{
			__tree_.clear();
		}

		key_compare key_comp() const
		{
			return __tree_.key_comp();
		}

		value_compare value_comp() const
		{
			return value_compare(__tree_.key_comp());
		}

		iterator find(const key_type& k)
		{
			return __tree_.find(k);
		}

		const_iterator find(const key_type& k) const
		{
			return __tree_.find(k);
		}

		size_type count(const key_type& k) const
		{
			return __tree_.count(k);
		}

		iterator lower_bound(const key_type& k)
		{
			return __tree_.lower_bound(k);
		}

		const_iterator lower_bound(const key_type& k) const
		{
			return __tree_.lower_bound(k);
		}

		iterator upper_bound(const key_type& k) 
		{
			return __tree_.upper_bound(k);
		}

		const_iterator upper_bound(const key_type& k) const
		{
			return __tree_.upper_bound(k);
		}

		pair<const_iterator, const_iterator> 
			equal_range(const key_type& k) const 
		{
			return __tree_.equal_range(k);
		}

		pair<iterator, iterator> equal_range(const key_type& k) 
		{
			return __tree_.equal_range(k);
		}

		allocator_type get_allocator() const
		{
			return allocator_type(__tree_.get_allocator());
		}
	};

	template <typename _Key, typename _T, typename _Compare, typename _Alloc>
	bool operator==(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
                const ft::map<_Key, _T, _Compare, _Alloc>& rhs) 
	{
		return (lhs.size() == rhs.size() &&
				ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename _Key, typename _T, typename _Compare, typename _Alloc>
	bool operator!=(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
			const ft::map<_Key, _T, _Compare, _Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename _Key, typename _T, typename _Compare, typename _Alloc>
	bool operator<(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
			const ft::map<_Key, _T, _Compare, _Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(),
				rhs.begin(), rhs.end());
	}

	template <typename _Key, typename _T, typename _Compare, typename _Alloc>
	bool operator>(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
               const ft::map<_Key, _T, _Compare, _Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <typename _Key, typename _T, typename _Compare, typename _Alloc>
	bool operator<=(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
			const ft::map<_Key, _T, _Compare, _Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename _Key, typename _T, typename _Compare, typename _Alloc>
	bool operator>=(const ft::map<_Key, _T, _Compare, _Alloc>& lhs,
			const ft::map<_Key, _T, _Compare, _Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename _Key, typename _T, typename _Compare, typename _Alloc>
	void swap(ft::map<_Key, _T, _Compare, _Alloc>& lhs,
			ft::map<_Key, _T, _Compare, _Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
} 

#endif
