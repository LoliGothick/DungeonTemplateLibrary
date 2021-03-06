﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_SHAPE_BORDER_ODD_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_SHAPE_BORDER_ODD_HPP

/*#######################################################################################
	日本語リファレンス (Reference-JP)
	https://github.com/Kasugaccho/DungeonTemplateLibrary/wiki/dtl::shape::BorderOdd-(%E5%BD%A2%E7%8A%B6%E3%82%AF%E3%83%A9%E3%82%B9)/
#######################################################################################*/

#include <DTL/Base/Struct.hpp>
#include <DTL/Macros/nodiscard.hpp>
#include <DTL/Macros/constexpr.hpp>
#include <DTL/Type/Forward.hpp>
#include <DTL/Type/SizeT.hpp>
#include <DTL/Range/RectBaseWithValue.hpp>

namespace dtl {
	inline namespace shape { //"dtl::shape"名前空間に属する

/*#######################################################################################
	[概要] BorderOddとは "Matrixの描画範囲の周囲1マスに描画値を設置し、描画範囲の列数が偶数の時[列数-2列目]のマスに描画値を設置し、
			行数が偶数の時[行数-2行目]のマスに描画値を設置する(※行/列は0から数える)" 機能を持つクラスである。
#######################################################################################*/
		template<typename Matrix_Int_>
		class BorderOdd : public ::dtl::range::RectBaseWithValue< ::dtl::shape::BorderOdd<Matrix_Int_>, Matrix_Int_> {
		private:


			///// エイリアス /////

			using Index_Size = ::dtl::type::size;
			using ShapeBase_t = ::dtl::range::RectBaseWithValue< ::dtl::shape::BorderOdd<Matrix_Int_>, Matrix_Int_>;


			///// 代入処理 /////

			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void assignSTL(Matrix_&& matrix_, const Index_Size end_x_, const Index_Size end_y_) const noexcept {
				matrix_[end_y_][end_x_] = this->draw_value;
			}
			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void assignArray(Matrix_&& matrix_, const Index_Size end_x_, const Index_Size end_y_, const Index_Size max_x_) const noexcept {
				matrix_[end_y_ * max_x_ + end_x_] = this->draw_value;
			}
			template<typename Matrix_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void assignLayer(Matrix_&& matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_) const noexcept {
				matrix_[end_y_][end_x_][layer_] = this->draw_value;
			}

			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void assignSTL(Matrix_&& matrix_, const Index_Size end_x_, const Index_Size end_y_, Function_&& function_) const noexcept {
				if (function_(matrix_[end_y_][end_x_])) matrix_[end_y_][end_x_] = this->draw_value;
			}
			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void assignArray(Matrix_&& matrix_, const Index_Size end_x_, const Index_Size end_y_, const Index_Size max_x_, Function_&& function_) const noexcept {
				if (function_(matrix_[end_y_ * max_x_ + end_x_])) matrix_[end_y_ * max_x_ + end_x_] = this->draw_value;
			}
			template<typename Matrix_, typename Function_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				inline void assignLayer(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_, Function_ && function_) const noexcept {
				if (function_(matrix_[end_y_][end_x_][layer_])) matrix_[end_y_][end_x_][layer_] = this->draw_value;
			}


			///// 基本処理 /////

			//STL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawSTL(Matrix_ && matrix_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_y_ == 0) return true;
				for (Index_Size col{ this->start_x }; col < matrix_[this->start_y].size(); ++col)
					this->assignSTL(matrix_, col, this->start_y, args_...);
				for (Index_Size col{ this->start_x }; col < matrix_[end_y_ - 1].size(); ++col) {
					if ((end_y_ - this->start_y) % 2 == 0) this->assignSTL(matrix_, col, end_y_ - 2, args_...);
					this->assignSTL(matrix_, col, end_y_ - 1, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					if (matrix_[row].size() == 0) continue;
					this->assignSTL(matrix_, this->start_x, row, args_...);
					if ((matrix_[row].size() - this->start_x) % 2 == 0) this->assignSTL(matrix_, matrix_[row].size() - 2, row, args_...);
					this->assignSTL(matrix_, matrix_[row].size() - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawWidthSTL(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_y_ < 2) return true;
				for (Index_Size col{ this->start_x }; col < end_x_ && col < matrix_[this->start_y].size(); ++col)
					this->assignSTL(matrix_, col, this->start_y, args_...);
				for (Index_Size col{ this->start_x }; col < end_x_ && col < matrix_[end_y_ - 1].size(); ++col) {
					if ((end_y_ - this->start_y) % 2 == 0) this->assignSTL(matrix_, col, end_y_ - 2, args_...);
					this->assignSTL(matrix_, col, end_y_ - 1, args_...);
				}
				if (end_x_ < 2) return true;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					if (matrix_[row].size() == 0) continue;
					this->assignSTL(matrix_, this->start_x, row, args_...);
					if (matrix_[row].size() <= end_x_) {
						if ((matrix_[row].size() - this->start_x) % 2 == 0) this->assignSTL(matrix_, matrix_[row].size() - 2, row, args_...);
						this->assignSTL(matrix_, matrix_[row].size() - 1, row, args_...);
					}
					else {
						if ((end_x_ - this->start_x) % 2 == 0) this->assignSTL(matrix_, end_x_ - 2, row, args_...);
						this->assignSTL(matrix_, end_x_ - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
					}
				}
				return true;
			}

			//LayerSTL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_y_ < 2) return true;
				for (Index_Size col{ this->start_x }; col < matrix_[this->start_y].size(); ++col)
					this->assignLayer(matrix_, layer_, col, this->start_y, args_...);
				for (Index_Size col{ this->start_x }; col < matrix_[end_y_ - 1].size(); ++col) {
					if ((end_y_ - this->start_y) % 2 == 0) this->assignLayer(matrix_, layer_, col, end_y_ - 2, args_...);
					this->assignLayer(matrix_, layer_, col, end_y_ - 1, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					if (matrix_[row].size() < 2) continue;
					this->assignLayer(matrix_, layer_, this->start_x, row, args_...);
					if ((matrix_[row].size() - this->start_x) % 2 == 0) this->assignLayer(matrix_, layer_, matrix_[row].size() - 2, row, args_...);
					this->assignLayer(matrix_, layer_, matrix_[row].size() - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerWidthSTL(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_y_ < 2) return true;
				for (Index_Size col{ this->start_x }; col < end_x_ && col < matrix_[this->start_y].size(); ++col)
					this->assignLayer(matrix_, layer_, col, this->start_y, args_...);
				for (Index_Size col{ this->start_x }; col < end_x_ && col < matrix_[end_y_ - 1].size(); ++col) {
					if ((end_y_ - this->start_y) % 2 == 0) this->assignLayer(matrix_, layer_, col, end_y_ - 2, args_...);
					this->assignLayer(matrix_, layer_, col, end_y_ - 1, args_...);
				}
				if (end_x_ < 2) return true;
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					if (matrix_[row].size() == 0) continue;
					this->assignLayer(matrix_, layer_, this->start_x, row, args_...);
					if (matrix_[row].size() <= end_x_) {
						if ((matrix_[row].size() - this->start_x) % 2 == 0) this->assignLayer(matrix_, layer_, matrix_[row].size() - 2, row, args_...);
						this->assignLayer(matrix_, layer_, matrix_[row].size() - 1, row, args_...);
					}
					else {
						if ((end_x_ - this->start_x) % 2 == 0) this->assignLayer(matrix_, layer_, end_x_ - 2, row, args_...);
						this->assignLayer(matrix_, layer_, end_x_ - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
					}
				}
				return true;
			}

			//Normal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawNormal(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_x_ < 2 || end_y_ < 2) return true;
				for (Index_Size col{ this->start_x }; col < end_x_; ++col) {
					this->assignSTL(matrix_, col, this->start_y, args_...);
					if ((end_y_ - this->start_y) % 2 == 0) this->assignSTL(matrix_, col, end_y_ - 2, args_...);
					this->assignSTL(matrix_, col, end_y_ - 1, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					this->assignSTL(matrix_, this->start_x, row, args_...);
					if ((end_x_ - this->start_x) % 2 == 0) this->assignSTL(matrix_, end_x_ - 2, row, args_...);
					this->assignSTL(matrix_, end_x_ - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}

			//LayerNormal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawLayerNormal(Matrix_ && matrix_, const Index_Size layer_, const Index_Size end_x_, const Index_Size end_y_, Args_ && ... args_) const noexcept {
				if (end_x_ < 2 || end_y_ < 2) return true;
				for (Index_Size col{ this->start_x }; col < end_x_; ++col) {
					this->assignLayer(matrix_, layer_, col, this->start_y, args_...);
					if ((end_y_ - this->start_y) % 2 == 0) this->assignLayer(matrix_, layer_, col, end_y_ - 2, args_...);
					this->assignLayer(matrix_, layer_, col, end_y_ - 1, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					this->assignLayer(matrix_, layer_, this->start_x, row, args_...);
					if ((end_y_ - this->start_y) % 2 == 0) this->assignLayer(matrix_, layer_, end_x_ - 2, row, args_...);
					this->assignLayer(matrix_, layer_, end_x_ - 1, row, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}

			//Array
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				bool drawArray(Matrix_ && matrix_, const Index_Size end_x_, const Index_Size end_y_, const Index_Size max_x_, Args_ && ... args_) const noexcept {
				if (end_x_ < 2 || end_y_ < 2) return true;
				for (Index_Size col{ this->start_x }; col < end_x_; ++col) {
					this->assignArray(matrix_, col, this->start_y, max_x_, args_...);
					if ((end_y_ - this->start_y) % 2 == 0) this->assignArray(matrix_, col, end_y_ - 2, max_x_, args_...);
					this->assignArray(matrix_, col, end_y_ - 1, max_x_, args_...);
				}
				for (Index_Size row{ this->start_y }; row < end_y_; ++row) {
					this->assignArray(matrix_, this->start_x, row, max_x_, args_...);
					if ((end_y_ - this->start_y) % 2 == 0) this->assignArray(matrix_, end_x_ - 2, row, max_x_, args_...);
					this->assignArray(matrix_, end_x_ - 1, row, max_x_, DTL_TYPE_FORWARD<Args_>(args_)...);
				}
				return true;
			}

		public:


			///// 生成呼び出し /////

			//STL
			template<typename Matrix_>
			constexpr bool draw(Matrix_&& matrix_) const noexcept {
				return (this->width == 0) ? this->drawSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), this->calcEndY(matrix_.size())) : this->drawWidthSTL(matrix_, this->start_x + this->width, this->calcEndY(matrix_.size()));
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, Function_ && function_) const noexcept {
				return (this->width == 0) ? this->drawSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), this->calcEndY(matrix_.size()), function_) : this->drawWidthSTL(matrix_, this->start_x + this->width, this->calcEndY(matrix_.size()), function_);
			}

			//LayerSTL
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size layer_) const noexcept {
				return (this->width == 0) ? this->drawLayerSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, this->calcEndY(matrix_.size())) : this->drawLayerWidthSTL(matrix_, layer_, this->start_x + this->width, this->calcEndY(matrix_.size()));
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size layer_, Function_ && function_) const noexcept {
				return (this->width == 0) ? this->drawLayerSTL(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, this->calcEndY(matrix_.size()), function_) : this->drawLayerWidthSTL(matrix_, layer_, this->start_x + this->width, this->calcEndY(matrix_.size()), function_);
			}

			//Normal
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), this->calcEndX(max_x_), this->calcEndY(max_y_));
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), this->calcEndX(max_x_), this->calcEndY(max_y_), function_);
			}

			//LayerNormal
			template<typename Matrix_>
			constexpr bool draw(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawLayerNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, this->calcEndX(max_x_), this->calcEndY(max_y_));
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperator(Matrix_ && matrix_, const Index_Size layer_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawLayerNormal(DTL_TYPE_FORWARD<Matrix_>(matrix_), layer_, this->calcEndX(max_x_), this->calcEndY(max_y_), function_);
			}

			//Array
			template<typename Matrix_>
			constexpr bool drawArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_) const noexcept {
				return this->drawArray(DTL_TYPE_FORWARD<Matrix_>(matrix_), this->calcEndX(max_x_), this->calcEndY(max_y_), max_x_);
			}
			template<typename Matrix_, typename Function_>
			constexpr bool drawOperatorArray(Matrix_ && matrix_, const Index_Size max_x_, const Index_Size max_y_, Function_ && function_) const noexcept {
				return this->drawArray(DTL_TYPE_FORWARD<Matrix_>(matrix_), this->calcEndX(max_x_), this->calcEndY(max_y_), max_x_, function_);
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

			///// コンストラクタ /////

			using ShapeBase_t::ShapeBase_t;
		};
	}
}

#endif //Included Dungeon Template Library