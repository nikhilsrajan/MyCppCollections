#include "IO_Node.hpp"

bool operator <  (const IO_Node& lhs, const IO_Node& rhs) { return lhs.node_id_ < rhs.node_id_; }
bool operator >  (const IO_Node& lhs, const IO_Node& rhs) { return rhs < lhs; }
bool operator <= (const IO_Node& lhs, const IO_Node& rhs) { return !(lhs > rhs); }
bool operator >= (const IO_Node& lhs, const IO_Node& rhs) { return !(lhs < rhs); }
bool operator == (const IO_Node& lhs, const IO_Node& rhs) { return lhs.node_id_ == rhs.node_id_; }
bool operator != (const IO_Node& lhs, const IO_Node& rhs) { return !(lhs == rhs); }

