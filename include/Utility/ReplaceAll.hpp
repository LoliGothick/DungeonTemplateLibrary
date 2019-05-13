﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_UTILITY_REPLACE_ALL_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_UTILITY_REPLACE_ALL_HPP

/* Character Code : UTF-8 (BOM) */
/* Bug Check : already checked */
/* Android NDK Compile (Clang 5.0) : already checked */

#include <cstdint>
#include <algorithm>
#include <vector>
#include <Base/Struct.hpp>
#include <Macros/constexpr.hpp>
#include <Macros/nodiscard.hpp>
#include <Type/Forward.hpp>
#include <Type/SizeT.hpp>

namespace dtl {
	inline namespace utility {

		//マスを指定した数値で埋める
		template<typename Matrix_Int_>
		class ReplaceAll {
		private:


			///// エイリアス /////

			using Index_Size = dtl::type::size;
			


			///// メンバ変数 /////

			Index_Size start_x{};
			Index_Size start_y{};
			Index_Size width{};
			Index_Size height{};
			Matrix_Int_ after_value{};
			std::vector<Matrix_Int_> before_value{};

			DTL_VERSIONING_CPP14_CONSTEXPR
				void string_String() const noexcept {}
			template<typename Int_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				void string_String(const Int_& first_, const Args_& ... args_) noexcept {
				this->before_value.emplace_back(static_cast<Matrix_Int_>(first_));
				this->string_String(args_...);
			}


			///// 代入処理 /////

			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionSTL(Matrix_&& matrix_, const Index_Size point_x_, const Index_Size point_y_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_][point_x_]) {
						matrix_[point_y_][point_x_] = this->after_value;
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_][point_x_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}
			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionArray(Matrix_&& matrix_, const Index_Size point_x_, const Index_Size point_y_, const Index_Size max_x_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_ * max_x_ + point_x_]) {
						matrix_[point_y_][point_x_] = this->after_value;
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_ * max_x_ + point_x_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}
			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionLayer(Matrix_&& matrix_, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_][point_x_][layer_]) {
						matrix_[point_y_][point_x_] = this->after_value;
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_][point_x_][layer_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}

			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionSTL(Matrix_&& matrix_, const Index_Size point_x_, const Index_Size point_y_, Function_&& function_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_][point_x_] && function_(matrix_[point_y_][point_x_])) {
						matrix_[point_y_][point_x_] = this->after_value;
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_][point_x_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}
			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionArray(Matrix_&& matrix_, const Index_Size point_x_, const Index_Size point_y_, const Index_Size max_x_, Function_&& function_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_ * max_x_ + point_x_] && function_(matrix_[point_y_ * max_x_ + point_x_])) {
						matrix_[point_y_][point_x_] = this->after_value;
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_ * max_x_ + point_x_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}
			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void substitutionLayer(Matrix_&& matrix_, const Index_Size layer_, const Index_Size point_x_, const Index_Size point_y_, Function_&& function_) const noexcept {
				for (std::int_fast32_t high_value{ static_cast<std::int_fast32_t>(this->before_value.size()) - 1 }, low_value{}, mid_value{}; low_value <= high_value;) {
					mid_value = (low_value + high_value) / 2;
					if (this->before_value[mid_value] == matrix_[point_y_][point_x_][layer_] && function_(matrix_[point_y_][point_x_][layer_])) {
						matrix_[point_y_][point_x_] = this->after_value;
						return;
					}
					else if (this->before_value[mid_value] < matrix_[point_y_][point_x_][layer_]) low_value = mid_value + 1;
					else high_value = mid_value - 1;
				}
			}


			///// 基本処理 /////

			//STL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawSTL(Matrix_&& matrix_, const Index_Size end_y_, Args_&& ... args_) const noexcept {
				if (this->before_value.size() == 0) return false;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < matrix_[row].size(); ++col)
						this->substitutionSTL(matrix_, col, row, args_...);
				return true;
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawWidthSTL(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (this->before_value.size() == 0) return false;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < matrix_[row].size() && col < end_x_; ++col)
						this->substitutionSTL(matrix_, col, row, args_...);
				return true;
			}

			//LayerSTL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (this->before_value.size() == 0) return false;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < matrix_[row].size(); ++col)
						this->substitutionLayer(matrix_, layer_, col, row, args_...);
				return true;
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerWidthSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (this->before_value.size() == 0) return false;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < matrix_[row].size() && col < end_x_; ++col)
						this->substitutionLayer(matrix_, layer_, col, row, args_...);
				return true;
			}

			//Normal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawNormal(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (this->before_value.size() == 0) return false;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < end_x_; ++col)
						this->substitutionSTL(matrix_, col, row, args_...);
				return true;
			}

			//LayerNormal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerNormal(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (this->before_value.size() == 0) return false;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < end_x_; ++col)
						this->substitutionLayer(matrix_, layer_, col, row, args_...);
				return true;
			}

			//Array
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawArray(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, const Index_Size max_x_, Args_ && ... args_) const noexcept {
				if (this->before_value.size() == 0) return false;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row)
					for (Index_Size col{ this->start_x }; col < end_x_; ++col)
						this->substitutionArray(matrix_, col, row, max_x_, args_...);
				return true;
			}

		public:


			///// 情報取得 /////

			DTL_VERSIONING_CPP17_NODISCARD
			constexpr Index_Size getPointX() const noexcept {
				return this->start_x;
			}
			DTL_VERSIONING_CPP17_NODISCARD
			constexpr Index_Size getPointY() const noexcept {
				return this->start_y;
			}
			DTL_VERSIONING_CPP17_NODISCARD
			constexpr Index_Size getWidth() const noexcept {
				return this->width;
			}
			DTL_VERSIONING_CPP17_NODISCARD
			constexpr Index_Size getHeight() const noexcept {
				return this->height;
			}
			DTL_VERSIONING_CPP17_NODISCARD
			constexpr Matrix_Int_ getValue() const noexcept {
				return this->after_value;
			}


			///// 生成呼び出し /////

			//STL
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_) const noexcept {
				return (this->width == 0) ? this->drawSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height) : this->drawWidthSTL(matrix_, this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, Function_ && function_) const noexcept {
				return (this->width == 0) ? this->drawSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height, function_) : this->drawWidthSTL(matrix_, this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height, function_);
			}

			//LayerSTL
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size layer_) const noexcept {
				return (this->width == 0) ? this->drawLayerSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height) : this->drawLayerWidthSTL(matrix_, layer_, this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size layer_, Function_ && function_) const noexcept {
				return (this->width == 0) ? this->drawLayerSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height, function_) : this->drawLayerWidthSTL(matrix_, layer_, this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= matrix_.size()) ? matrix_.size() : this->start_y + this->height, function_);
			}

			//Normal
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height, function_);
			}

			//LayerNormal
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawLayerNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawLayerNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height, function_);
			}

			//Array
			template<typename Matrix_>
			constexpr bool drawArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawArray(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height, max_x_);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperatorArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawArray(DTL_TYPE_FORWARD<Matrix_>(matrix_), (this->width == 0 || this->start_x + this->width >= max_x_) ? max_x_ : this->start_x + this->width, (this->height == 0 || this->start_y + this->height >= max_y_) ? max_y_ : this->start_y + this->height, max_x_, function_);
			}


			///// 生成呼び出しファンクタ /////

			template<typename Matrix_, typename ...Args_>
			constexpr bool operator()(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				return this->draw(DTL_TYPE_FORWARD<Matrix_>(matrix_), DTL_TYPE_FORWARD<Args_>(args_)...);
			}


			///// ダンジョン行列生成 /////

			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Matrix_&& create(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->draw(matrix_, DTL_TYPE_FORWARD<Args_>(args_)...);
				return DTL_TYPE_FORWARD<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Matrix_&& createArray(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawArray(matrix_, DTL_TYPE_FORWARD<Args_>(args_)...);
				return DTL_TYPE_FORWARD<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Matrix_&& createOperator(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawOperator(matrix_, DTL_TYPE_FORWARD<Args_>(args_)...);
				return DTL_TYPE_FORWARD<Matrix_>(matrix_);
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Matrix_&& createOperatorArray(Matrix_ && matrix_, Args_ && ... args_) const noexcept {
				this->drawOperatorArray(matrix_, DTL_TYPE_FORWARD<Args_>(args_)...);
				return DTL_TYPE_FORWARD<Matrix_>(matrix_);
			}


			///// 消去 /////

			//始点座標Xを初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& clearPointX() noexcept {
				this->start_x = 0;
				return *this;
			}
			//始点座標Yを初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& clearPointY() noexcept {
				this->start_y = 0;
				return *this;
			}
			//範囲の大きさ(X軸方向)を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& clearWidth() noexcept {
				this->width = 0;
				return *this;
			}
			//範囲の大きさ(Y軸方向)を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& clearHeight() noexcept {
				this->height = 0;
				return *this;
			}
			//始点座標(X,Y)を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& clearPoint() noexcept {
				this->clearPointX();
				this->clearPointY();
				return *this;
			}
			//描画範囲を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& clearRange() noexcept {
				this->clearPointX();
				this->clearPointY();
				this->clearWidth();
				this->clearHeight();
				return *this;
			}
			//全ての値を初期値に戻す
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& clear() noexcept {
				this->clearRange();
				return *this;
			}


			///// 代入 /////

			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setPointX(const Index_Size start_x_) noexcept {
				this->start_x = start_x_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setPointY(const Index_Size start_y_) noexcept {
				this->start_y = start_y_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setWidth(const Index_Size width_) noexcept {
				this->width = width_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setHeight(const Index_Size height_) noexcept {
				this->height = height_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setPoint(const Index_Size point_) noexcept {
				this->start_x = point_;
				this->start_y = point_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setPoint(const Index_Size start_x_, const Index_Size start_y_) noexcept {
				this->start_x = start_x_;
				this->start_y = start_y_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setRange(const Index_Size start_x_, const Index_Size start_y_, const Index_Size length_) noexcept {
				this->start_x = start_x_;
				this->start_y = start_y_;
				this->width = length_;
				this->height = length_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setRange(const Index_Size start_x_, const Index_Size start_y_, const Index_Size width_, const Index_Size height_) noexcept {
				this->start_x = start_x_;
				this->start_y = start_y_;
				this->width = width_;
				this->height = height_;
				return *this;
			}
			DTL_VERSIONING_CPP14_CONSTEXPR
				ReplaceAll& setRange(const dtl::base::MatrixRange& matrix_range_) noexcept {
				this->start_x = matrix_range_.x;
				this->start_y = matrix_range_.y;
				this->width = matrix_range_.w;
				this->height = matrix_range_.h;
				return *this;
			}


			///// コンストラクタ /////

			constexpr ReplaceAll() noexcept = default;
			constexpr explicit ReplaceAll(const Matrix_Int_ & after_value_) noexcept
				:after_value(after_value_) {}
			template<typename ...Args_>
			explicit ReplaceAll(const Matrix_Int_& after_value_, const Matrix_Int_& first_before_value_, const Args_& ... second_and_subsequent_before_value_) noexcept
				:after_value(after_value_) {
				this->string_String(first_before_value_, second_and_subsequent_before_value_...);
				std::sort(before_value.begin(), before_value.end());
			}
			constexpr explicit ReplaceAll(const dtl::base::MatrixRange & matrix_range_) noexcept
				:start_x(matrix_range_.x), start_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h) {}
			constexpr explicit ReplaceAll(const dtl::base::MatrixRange & matrix_range_, const Matrix_Int_ & after_value_) noexcept
				:start_x(matrix_range_.x), start_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h),
				after_value(after_value_) {}
			template<typename ...Args_>
			explicit ReplaceAll(const dtl::base::MatrixRange& matrix_range_, const Matrix_Int_& after_value_, const Matrix_Int_& first_before_value_, const Args_& ... second_and_subsequent_before_value_) noexcept
				:start_x(matrix_range_.x), start_y(matrix_range_.y),
				width(matrix_range_.w), height(matrix_range_.h),
				after_value(after_value_) {
				this->string_String(first_before_value_, second_and_subsequent_before_value_...);
				std::sort(before_value.begin(), before_value.end());
			}

		};
	}
}

#endif //Included Dungeon Template Library