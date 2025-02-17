//
// Created by uralg on 14.02.2025.
//

#ifndef HELIUM_UTILS_ARRAY_HPP
#define HELIUM_UTILS_ARRAY_HPP
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <He/Log.hpp>

namespace He::Utils {
	template<typename  T> class Array {
	private:
		T* _data;
		std::size_t _size;
	public:
		class Iterator {
		public:
			// iterator_trait associated types
			typedef Iterator itr_type;
			typedef T value_type;
			typedef T &reference;
			typedef T *pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t difference_type;

			Iterator(pointer ptr) : m_itr_ptr(ptr) {}
			itr_type operator++() {
				itr_type old_itr = *this;
				++m_itr_ptr;
				return old_itr;
			}

			itr_type operator++(int dummy) {
				++m_itr_ptr;
				return *this;
			}

			itr_type operator--() {
				itr_type old_itr = *this;
				--m_itr_ptr;
				return old_itr;
			}

			itr_type operator--(int dummy) {
				--m_itr_ptr;
				return *this;
			}

			reference operator*() const { return *m_itr_ptr; }

			pointer operator->() const { return m_itr_ptr; }

			bool operator==(const itr_type &rhs) { return m_itr_ptr == rhs.m_itr_ptr; }

			bool operator!=(const itr_type &rhs) { return m_itr_ptr != rhs.m_itr_ptr; }

		private:
			pointer m_itr_ptr;
		};
		class ConstIterator {
		public:
			// iterator_trait associated types
			typedef ConstIterator itr_type;
			typedef const T value_type;
			typedef const T &reference;
			typedef const T *pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef std::ptrdiff_t difference_type;

			ConstIterator(pointer ptr) : m_itr_ptr(ptr) {}
			ConstIterator(Iterator itr) : m_itr_ptr(itr.m_itr_ptr) {}
			itr_type operator++() {
				itr_type old_itr = *this;
				++m_itr_ptr;
				return old_itr;
			}

			itr_type operator++(int dummy) {
				++m_itr_ptr;
				return *this;
			}

			itr_type operator--() {
				itr_type old_itr = *this;
				--m_itr_ptr;
				return old_itr;
			}

			itr_type operator--(int dummy) {
				--m_itr_ptr;
				return *this;
			}

			reference operator*() const { return *m_itr_ptr; }

			pointer operator->() const { return m_itr_ptr; }

			bool operator==(const itr_type &rhs) { return m_itr_ptr == rhs.m_itr_ptr; }

			bool operator!=(const itr_type &rhs) { return m_itr_ptr != rhs.m_itr_ptr; }

		private:
			pointer m_itr_ptr;
		};



		T &operator[](unsigned int idx) {
#if _DEBUG
			if (idx >= _size)
				throw std::runtime_error("Index out of range");
#endif
			return _data[idx];
		}

		const T &operator[](unsigned int idx) const {
#if _DEBUG
			if (idx >= _size)
				throw std::runtime_error("Index out of range");
#endif
			return _data[idx];
		}

		std::size_t size() const { return _size; }
		T* raw_ptr() const { return _data; }

		Iterator begin() { return Iterator(_data); }

		Iterator end() { return Iterator(_data + _size); }

		ConstIterator cbegin() const { return ConstIterator(_data); }

		ConstIterator cend() const { return ConstIterator(_data + _size); }

		Array() : _data(nullptr), _size(0) {}
		explicit Array(std::size_t size) : _data(new T[size]), _size(size) {}
		Array(const Array& other) : _data(new T[other.size()]), _size(other.size()) {
			std::copy(other.cbegin(), other.cend(), _data);
		}
		Array(std::initializer_list<T> init): _data(new T[init.size()]), _size(init.size()) {
			std::copy(init.begin(), init.end(), _data);
		}
		~Array() {
			DEBUG_INFO("~Array<{}>() here _data = {}, _size = {}", typeid(T).name(), (void*)_data, _size);
			delete[] _data;
			_data = nullptr;
			_size = 0;
		}

		Array& operator=(Array&& other) noexcept {
			if (this != &other) {
				delete[] _data;
				_data = other._data;
				_size = other._size;
				other._data = nullptr;
				other._size = 0;
			}
			return *this;
		}

	}; 
}

#endif //HELIUM_UTILS_ARRAY_HPP
