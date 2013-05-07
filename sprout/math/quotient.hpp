#ifndef SPROUT_MATH_QUOTIENT_HPP
#define SPROUT_MATH_QUOTIENT_HPP

#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/iround.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR T
			quotient_impl(T x, T y) {
				return sprout::math::iround<R>(x / y);
			}

			template<
				typename R = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<R>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR R
			quotient(FloatType x, FloatType y) {
				return sprout::math::isnan(y) || sprout::math::isnan(x) ? R(0)
					: x == 0 && y != 0 ? R(0)
					: x == std::numeric_limits<FloatType>::infinity() || x == -std::numeric_limits<FloatType>::infinity() || y == 0
						? R(0)
					: y == std::numeric_limits<FloatType>::infinity() || y == -std::numeric_limits<FloatType>::infinity() ? R(0)
					: static_cast<FloatType>(sprout::math::detail::quotient_impl<R>(
						static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x),
						static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(y)
						))
					;
			}
			template<
				typename R = int,
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value && std::is_integral<R>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR R
			quotient(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::quotient(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using sprout::math::detail::quotient;
	}	// namespace math

	using sprout::math::quotient;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUOTIENT_HPP
