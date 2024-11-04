/*
** EPITECH PROJECT, 2024
** R-Type - ComponentManager : SparceArray
** File description:
** SparseArray is a data structure to hold and index the components
** that an Entity is composed of.
*/
#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <optional>
#include <memory>

namespace ECS {
    namespace ComponentManager {

        template <typename Component>
        class SparseArray {
        public:
            using value_type = std::optional<Component>;
            using cc_type = Component &;
            using reference_type = value_type &;
            using const_reference_type = value_type const &;
            using container_t = std::vector<value_type>;
            using size_type = typename container_t::size_type;

            using iterator = typename container_t::iterator;
            using const_iterator = typename container_t::const_iterator;

            SparseArray() = default;

            SparseArray(SparseArray const & other): _data(other._data) {};
            SparseArray(SparseArray && other) noexcept: _data(std::move(other._data)) {};
            ~SparseArray() = default;

            SparseArray & operator=(SparseArray const & other) {
                _data = other._data;
                return this;
            };
            SparseArray & operator=(SparseArray && other) noexcept {
                _data = std::move(other._data);
                return this;
            };

            /**
             * @brief Encapsulated call to the class access operator.
             *
             * @param[in] idx Index of the object to be accessed
             * @return The object at the given index.
             */
            reference_type operator[](std::size_t idx) {
                return _data[idx];
            };

            /**
             * @brief Encapsulated call to the class const access operator.
             *
             * @param[in] idx Index of the object to be accessed
             * @return A const reference to the object at the given index.
             */
            const_reference_type operator[](std::size_t idx) const{
                return _data[idx];
            };

            iterator begin() {
                return _data.begin();
            };
            const_iterator begin() const {
                return _data.begin();
            };
            const_iterator cbegin() const {
                return _data.cbegin();
            };

            iterator end() {
                return _data.end();
            };
            const_iterator end() const {
                return _data.end();
            };
            const_iterator cend() const {
                return _data.cend();
            };

            /**
             * @brief Encapsulated call to the class container.
             *
             * @return The size of the class container.
             */
            size_type size() const {
                return _data.size();
            };

            /**
             * @brief Assigns an object to an index in the class container.
             *
             * The class container will adapt its size to the given index.
             *
             * @return The reference to the created object in the class container.
             */
            reference_type insertAt(size_type pos, Component const & component) {
                if (pos >= size())
                    _data.resize(pos+ 1);
                _data[pos] = component;
                return _data[pos];
            };

            cc_type insertAt(size_type pos, std::optional<Component> component) {
                if (pos >= size())
                    _data.resize(pos+ 1);
                _data[pos] = component;
                return _data[pos];
            };
            /**
             * @brief Moves an object to an index in the class container.
             *
             * The class container will adapt its size to the given index.
             *
             * @return The reference to the created object in the class container.
             */
            reference_type insertAt(size_type pos, Component && component) {
                if (pos >= size())
                    _data.resize(pos+ 1);
                _data[pos] = std::move(component);
                return _data[pos];
            };

            /**
             * @brief Constructs an object at the given index.
             *
             * The class container will adapt its size to the given index.
             *
             * @tparam Variadic templating to carry the objects constructor parameters.
             * @return The reference to the created object in the class container.
             */
            template <class... Params>
            reference_type emplaceAt(size_type pos, Params &&... args) {
                if (pos >= size())
                    _data.resize(pos+ 1);
                _data[pos].emplace(std::forward<Params>(args)...);
                return _data[pos];
            };

            /**
             * @brief Destroys the object at the given index.
             */
            void erase(size_type pos) {
                if (pos > size())
                    return;
                _data[pos].reset();
            };

            /**
             * @brief Returns the index of the given object.
             *
             * @return If the given toSearch object is found, its index is returned. If it is not found, size() is returned.
             */
            size_type getIndex(value_type const & toSearch) const {
                for (size_type index = 0; index < size(); index++)
                    if (_data[index].has_value())
                        if (std::addressof(_data[index].value()) ==
                            std::addressof(toSearch.value()))
                            return index;
                return size();
            };

            void clear() {
                _data.clear();
            };

        private:
            container_t _data;
        };

        /**
         * @brief ostream operator overload.
         *
         * This is used to display the content of a SparseArray.
         * If the type used in the SparseArray does not provide an ostream operator overload, an exception is raised.
         *
         * @tparam Component Compoennt type of the SparseArray to be displayed.
         * @return The ostream used.
         */
        template <typename Component>
        std::ostream & operator<<(std::ostream & stream, const SparseArray<Component> & array) {
            try {
                if (array[0].has_value())
                    stream << array[0].value();
                else
                    stream << "Empty";
            } catch(std::exception e) {
                stream << "This component does not support '<<' operator." << std::endl;
            }
            for (std::size_t index = 1; index < array.size(); index++) {
                stream << ", ";
                if (array[index].has_value())
                    stream << array[index].value();
                else
                    stream << "Empty";
            }
            stream << std::endl;
            return stream;
        };
    }
}
