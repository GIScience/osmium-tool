#ifndef COMMAND_GETID_HPP
#define COMMAND_GETID_HPP

/*

Osmium -- OpenStreetMap data manipulation command line tool
http://osmcode.org/osmium

Copyright (C) 2013-2016  Jochen Topf <jochen@topf.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <map>
#include <set>
#include <string>
#include <vector>

#include <osmium/fwd.hpp>
#include <osmium/osm/entity_bits.hpp>
#include <osmium/osm/item_type.hpp>
#include <osmium/osm/types.hpp>

#include "cmd.hpp"

class CommandGetId : public Command, public with_single_osm_input, public with_osm_output {

    osmium::item_type m_default_item_type = osmium::item_type::node;

    bool m_add_referenced_objects = false;
    bool m_work_with_history = false;
    bool m_verbose_ids = false;

    std::set<osmium::object_id_type> m_ids[3];

    std::set<osmium::object_id_type>& ids(osmium::item_type type) noexcept;
    const std::set<osmium::object_id_type>& ids(osmium::item_type type) const noexcept;

    void parse_and_add_id(const std::string& s);

    void read_id_osm_file(const std::string& file_name);
    void read_id_file(std::istream& stream);

    osmium::osm_entity_bits::type get_needed_types() const;
    bool no_ids() const;
    size_t count_ids() const;

    void find_referenced_objects();

    void add_nodes(const osmium::Way& way);
    void add_members(const osmium::Relation& relation);

    void mark_rel_ids(const std::multimap<osmium::object_id_type, osmium::object_id_type>& rel_in_rel, osmium::object_id_type id);
    bool find_relations_in_relations();
    void find_nodes_and_ways_in_relations();
    void find_nodes_in_ways();

public:

    CommandGetId() = default;

    bool setup(const std::vector<std::string>& arguments) override final;

    void show_arguments() override final;

    bool run() override final;

    const char* name() const noexcept override final {
        return "getid";
    }

    const char* synopsis() const noexcept override final {
        return "osmium getid [OPTIONS] OSM-FILE ID...\n"
               "       osmium getid [OPTIONS] OSM-FILE -i ID-FILE\n"
               "       osmium getid [OPTIONS] OSM-FILE -I ID-OSM-FILE";
    }

}; // class CommandGetId


#endif // COMMAND_GETID_HPP
