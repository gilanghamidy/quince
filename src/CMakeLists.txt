target_sources(quince PRIVATE
        abstract_column_sequence.cpp
        binomen.cpp
        cell.cpp
        column_id.cpp
        database.cpp
        exceptions.cpp
        junction.cpp
        object_id.cpp
        query_base.cpp
        row.cpp
        sql.cpp
        table_alias.cpp
        table_interface.cpp
        table.cpp
        transaction.cpp
)

add_subdirectory(exprn_mappers)
add_subdirectory(mappers)
