#ifndef NODE_H
#define NODE_H

#include <utility>
#include <stdint.h>

#include "Globals.hpp"

/**
 * @brief Class that user of IO_File would use to handle data in IO_File.
 * @author nsr
 */
class IO_Node
{
public:
    IO_Node() noexcept = default;
    IO_Node(io_file::Id id)
        : node_id_(id) {}

    ~IO_Node() = default;

    IO_Node(const IO_Node& lhs)
        : node_id_(lhs.node_id_) {}                                             /* Rule of 5 (C++) */

    IO_Node(IO_Node&& lhs)
        : node_id_(std::move(lhs.node_id_)) {}

    IO_Node& operator = (const IO_Node& lhs) {
        node_id_ = lhs.node_id_;
        return *this;
    }

    IO_Node& operator = (IO_Node&& lhs) {
        node_id_ = std::move(lhs.node_id_);
        return *this;
    }

    friend bool operator <  (const IO_Node& lhs, const IO_Node& rhs);
    friend bool operator >  (const IO_Node& lhs, const IO_Node& rhs);
    friend bool operator <= (const IO_Node& lhs, const IO_Node& rhs);           /* To allow IO_Node to be used as keys in maps. */
    friend bool operator >= (const IO_Node& lhs, const IO_Node& rhs);
    friend bool operator == (const IO_Node& lhs, const IO_Node& rhs);
    friend bool operator != (const IO_Node& lhs, const IO_Node& rhs);

    const io_file::Id& GetId() const {
        return node_id_;
    }

private:
    io_file::Id node_id_;
};

#endif // IO_NODE_H
