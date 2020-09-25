#ifndef QUINCE_SQLITE__database_h
#define QUINCE_SQLITE__database_h

//          Copyright Michael Shepanski 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include <quince/database.h>
#include <quince/mapping_customization.h>
#include <quince/sqlite/detail/session.h>


namespace quince::sqlite {

class table_base;
class dialect_sql;

// See http://quince-lib.com/quince_sqlite.html#quince_sqlite.constructor
//
class database : public quince::database {
public:
    typedef std::map<std::string, boost::filesystem::path> filename_map;

    database(
        std::string filename,
        bool may_write = true,
        bool mutex = true,
        bool share_cache = true,
        std::optional<std::string> vfs_module_name = std::nullopt,
        const std::optional<quince::mapping_customization> &customization_for_db = std::nullopt,
        const filename_map &attachable_database_filenames = filename_map()
    );

    virtual ~database();


    // --- Everything from here to end of class is for quince internal use only. ---

    virtual std::unique_ptr<quince::sql>    make_sql() const override;
    virtual std::optional<std::string>    get_default_enclosure() const override;
    void                                    make_enclosure_available(const std::optional<std::string> &enclosure_name) const override;
    virtual quince::new_session             make_session() const override;
    virtual std::vector<std::string>        retrieve_column_titles(const quince::binomen &table) const override;
    virtual quince::serial                  insert_with_readback(std::unique_ptr<quince::sql> insert, const quince::serial_mapper &unused) const override;
    virtual std::string                     column_type_name(quince::column_type) const override;

    virtual bool supports_join(quince::conditional_junction_type) const override;
    virtual bool supports_combination(quince::combination_type, bool all) const override;
    virtual bool supports_nested_combinations() const override                              { return false; }
    virtual bool supports_index(const quince::index_spec &) const override;
    virtual bool imposes_combination_precedence() const override                            { return false; }

    std::unique_ptr<dialect_sql> make_dialect_sql() const;

private:
    std::shared_ptr<session_impl> get_session_impl() const;

    const session_impl::spec _spec;
    const std::map<std::string, boost::filesystem::path> _attachable_database_absolute_filenames;
};

}

#endif
