#ifndef EXTRACT_STRATEGY_SIMPLE_HPP
#define EXTRACT_STRATEGY_SIMPLE_HPP

/*

Osmium -- OpenStreetMap data manipulation command line tool
https://osmcode.org/osmium-tool/

Copyright (C) 2013-2025  Jochen Topf <jochen@topf.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "strategy.hpp"

#include <osmium/index/id_set.hpp>

#include <memory>
#include <vector>

namespace strategy_simple {

    struct Data {
        osmium::index::IdSetDense<osmium::unsigned_object_id_type> node_ids;
        osmium::index::IdSetDense<osmium::unsigned_object_id_type> way_ids;
    };

    class Strategy : public ExtractStrategy {

        template<typename S, typename T> friend class ::Pass;
        friend class Pass1;

        using extract_data = ExtractData<Data>;
        std::vector<extract_data> m_extracts;

    public:

        explicit Strategy(const std::vector<std::unique_ptr<Extract>>& extracts, const osmium::Options& /*options*/);

        const char* name() const noexcept override final;

        void run(osmium::VerboseOutput& vout, bool display_progress, const osmium::io::File& input_file) override final;

    }; // class Strategy

} // namespace strategy_simple

#endif // EXTRACT_STRATEGY_SIMPLE_HPP
