#ifndef ATTRIBUTE_MANAGER_INTERFACE_H
#define ATTRIBUTE_MANAGER_INTERFACE_H

#include "Globals.hpp"

/**
 * @brief Abstract class for all attribute managers.
 * @author nsr
 */
class Attribute_Manager_Interface
{
public:
    virtual ~Attribute_Manager_Interface() = default;

    /**
     * @brief Checks if the attribute manager has node with id node_id.
     * @param node_id Unique Id of a node.
     * @return true, if the attribute manager has the node with id node_id.
     * @return false, if the attribute manager doesn't have node with id node_id.
     */
    virtual bool HasNode(const io_file::Id& node_id) = 0;

    /**
     * @brief Removes node with id node_id from the attribute manager.
     * @param node_id Unique Id of a node.
     * @return true, if the node with id node_id was present in the attribute manager.
     * @return false, if the node with id node_id wasn't found in the attribute manager, and thus not removed.
     */
    virtual bool RemoveNode(const io_file::Id& node_id) = 0;
};

#endif // ATTRIBUTE_MANAGER_INTERFACE_H
