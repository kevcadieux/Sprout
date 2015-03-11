/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_PARTITION_POINT_HPP
#define SPROUT_ALGORITHM_PARTITION_POINT_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>

namespace sprout {
#ifdef SPROUT_CONFIG_DISABLE_CXX14_CONSTEXPR
	namespace detail {
		template<typename ForwardIterator, typename Predicate>
		inline SPROUT_CONSTEXPR ForwardIterator
		partition_point_impl(ForwardIterator first, ForwardIterator last, Predicate pred, ForwardIterator mid) {
			return mid == last ? mid
				: pred(*mid) ? sprout::detail::partition_point_impl(
					sprout::next(mid), last, pred,
					sprout::next(mid, 1 + (sprout::distance(mid, last) - 1) / 2)
					)
				: sprout::detail::partition_point_impl(
					first, mid, pred,
					sprout::next(first, sprout::distance(first, mid) / 2)
					)
				;
		}
	}	// namespace detail

	// 25.3.13 Partitions
	//
	//	recursion depth:
	//		O(log N)
	//
	template<typename ForwardIterator, typename Predicate>
	inline SPROUT_CONSTEXPR ForwardIterator
	partition_point(ForwardIterator first, ForwardIterator last, Predicate pred) {
		return sprout::detail::partition_point_impl(
			first, last, pred,
			sprout::next(first, sprout::distance(first, last) / 2)
			);
	}
#else
	// 25.3.13 Partitions
	//
	//	recursion depth:
	//		0
	//
	template<typename ForwardIterator, typename Predicate>
	inline SPROUT_CONSTEXPR ForwardIterator
	partition_point(ForwardIterator first, ForwardIterator last, Predicate pred) {
		typedef typename std::iterator_traits<ForwardIterator>::difference_type difference_type;
		for (difference_type len = sprout::distance(first, last); len != 0; ) {
			const difference_type half = len / 2;
			const ForwardIterator mid = sprout::next(first, half);
			if (pred(*mid)) {
				first = sprout::next(mid);
				len -= half + 1;
			} else {
				len = half;
			}
		}
		return first;
	}
#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_PARTITION_POINT_HPP
