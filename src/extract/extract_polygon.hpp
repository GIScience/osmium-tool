#ifndef EXTRACT_EXTRACT_POLYGON_HPP
#define EXTRACT_EXTRACT_POLYGON_HPP

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

#include "extract.hpp"

#include <osmium/osm/area.hpp>
#include <osmium/osm/segment.hpp>

#include <vector>

class ExtractPolygon : public Extract {

    const osmium::memory::Buffer& m_buffer;
    std::size_t m_offset;

    std::vector<std::vector<osmium::Segment>> m_bands;
    int32_t m_dy = 0;

    const osmium::Area& area() const noexcept;

    int32_t y_max() const noexcept {
        return envelope().top_right().y();
    }

    int32_t y_min() const noexcept {
        return envelope().bottom_left().y();
    }

public:

    ExtractPolygon(const osmium::io::File& output_file, const std::string& description, const osmium::memory::Buffer& buffer, std::size_t offset);

    bool contains(const osmium::Location& location) const noexcept override final;

    const char* geometry_type() const noexcept override final;

    std::string geometry_as_text() const override final;

}; // class ExtractPolygon

#endif // EXTRACT_EXTRACT_POLYGON_HPP
