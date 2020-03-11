#ifndef ATTRIBUTE_MANAGER_H
#define ATTRIBUTE_MANAGER_H

#include <map>

#include "Attribute_Manager_Interface.hpp"

/**
 *  @brief Class to manage one attribute for all nodes handling their ids.
 *         Records if a node with id node_id has the attribute the manager is managing
 *         and what the value of that attribute is.
 * @author nsr
 */
template <class T>
class Attribute_Manager : public Attribute_Manager_Interface
{
public:
    Attribute_Manager(const T& default_value = T{})
        : default_value_(default_value) {}

    ~Attribute_Manager() override = default;

    Attribute_Manager(const Attribute_Manager& lhs)
        : node_T_map_(lhs.node_T_map_)
        , default_value_(lhs.default_value_) {}
                                                                                    /* Rule of 5 (C++) */
    Attribute_Manager(Attribute_Manager&& lhs)
        : node_T_map_(std::move(lhs.node_T_map_))
        , default_value_(std::move(lhs.default_value_)) {}

    Attribute_Manager& operator = (const Attribute_Manager& lhs) {
        node_T_map_ = lhs.node_T_map_;
        default_value_ = lhs.default_value_;
        return *this;
    }

    Attribute_Manager& operator = (Attribute_Manager&& lhs) {
        node_T_map_ = std::move(lhs.node_T_map_);
        default_value_ = std::move(lhs.default_value_);
        return *this;
    }

    /**
     * @brief Checks if the manager has a record of a node with id node_id.
     * @param node_id Id of the node whose record is being searched.
     * @return true, if the manager has a record of a node with id node_id.
     * @return false, if the manager doesn't have a record of a node with id node_id.
     */
    bool HasNode(const io_file::Id& node_id) override {
        return node_T_map_.find(node_id) != node_T_map_.end() ? true : false;
    }

    /**
     * @brief Creates or updates a record for a node with id node_id.
     * @param node_id Id of the node for which a new record is being created or existing record is being updated.
     * @param value, the value of the attribute the manager stores or updates corresponding to the node with id node_id.
     */
    void AddNode(const io_file::Id& node_id, T value) {
        node_T_map_[node_id] = value;
        return;
    }

    /**
     * @brief Deletes the record of the node with id node_id.
     * @param node_id Id of the node whose record is being deleted.
     * @return true, if the record of the node with id node_id existed.
     * @return false, if the record of the node with id node_id did not exist.
     */
    bool RemoveNode(const io_file::Id& node_id) override {
        if (!HasNode(node_id)) return false;
        node_T_map_.erase(node_id);
        return true;
    }

    /**
     * @brief Gets the value of the attribute corresponding to the node with id node_id,
     *        and puts it into getter, the parameter passed-by-reference.
     * @param node_id Id of the node whose attribute value is being accessed.
     * @param getter parameter passed-by-reference to get the value of the attribute
     *        corresponding to the node with id node_id. If the record did not exist,
     *        a default value is put into the getter.
     * @return true, if the record of the node with id node_id existed.
     * @return false, if the record of the node with id node_id did not exist.
     */
    bool GetValue(const io_file::Id& node_id, T& getter) {
        getter = default_value_;
        if (!HasNode(node_id)) return false;
        getter = node_T_map_[node_id];
        return true;
    }

    /**
     * @brief Updates the default value for an attribute for those nodes without a record.
     * @param value the new default value for those nodes without a record.
     */
    void SetNewDefaultValue(const T& value) {
        default_value_ = value;
    }

private:
    std::map<io_file::Id, T> node_T_map_;
    T default_value_;
};

#endif // ATTRIBUTE_MANAGER_H
