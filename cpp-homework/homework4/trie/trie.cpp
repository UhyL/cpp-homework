#include "trie.h"
#include <string_view>

template <class T>
auto Trie::Get(std::string_view key) const -> const T * {
    // You should walk through the trie to find the node corresponding to the key. If the node doesn't exist, return
    // nullptr. After you find the node, you should use `dynamic_cast` to cast it to `const TrieNodeWithValue<T> *`. If
    // dynamic_cast returns `nullptr`, it means the type of the value is mismatched, and you should return nullptr.
    // Otherwise, return the value.
    // throw "Trie::Get is not implemented.";

    std::shared_ptr<const TrieNode> node = root_;
    for (char c : key) {
        if (node == nullptr || node->children_.find(c) == node->children_.end())
            return nullptr;

        auto it = node->children_.find(c);
        node = it->second;
    }

    if (node != nullptr && node->is_value_node_) {
        const TrieNodeWithValue<T> *temp = dynamic_cast<const TrieNodeWithValue<T> *>(node.get());
        if (temp != nullptr)
            return temp->value_.get();
    }

    return nullptr;
}

template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie {
    // Note that `T` might be a non-copyable type. Always use `std::move` when creating `shared_ptr` on that value.
    // You should walk through the trie and create new nodes if necessary. If the node corresponding to the key already
    // exists, you should create a new `TrieNodeWithValue`.
    // throw "Trie::Put is not implemented.";
    std::shared_ptr<T> new_value = std::make_shared<T>(std::move(value));
    // for root op
    if (key.empty()) {
        std::unique_ptr<TrieNodeWithValue<T>> new_root = nullptr;
        if (!root_ || root_->children_.empty())
            new_root = std::make_unique<TrieNodeWithValue<T>>(std::move(new_value));
        else
            new_root = std::make_unique<TrieNodeWithValue<T>>(root_->children_, std::move(new_value));

        return Trie(std::shared_ptr<const TrieNode>(std::move(new_root)));
    }

    std::shared_ptr<TrieNode> root_copy = nullptr;
    if (root_)
        root_copy = std::shared_ptr<TrieNode>(std::move(root_->Clone()));
    else
        root_copy = std::make_shared<TrieNode>();

    std::shared_ptr<TrieNode> curr_node = root_copy;

    for (int i = 0; i < key.length(); ++i) {
        char c = key[i];
        if (i == key.length() - 1) {
            if (curr_node->children_.find(c) == curr_node->children_.end()) {
                std::shared_ptr<TrieNode> new_node = std::make_shared<TrieNodeWithValue<T>>(std::move(new_value));
                curr_node->children_[c] = new_node;
            } else {
                std::shared_ptr<TrieNode> new_node = std::make_shared<TrieNodeWithValue<T>>(curr_node->children_[c]->children_, std::move(new_value));
                curr_node->children_[c] = new_node;
            }

        } else {
            if (curr_node->children_.find(c) == curr_node->children_.end()) {
                std::shared_ptr<TrieNode> new_node = std::make_shared<TrieNode>();
                curr_node->children_[c] = new_node;
            } else
                curr_node->children_[c] = std::shared_ptr<TrieNode>(std::move(curr_node->children_[c]->Clone()));

            curr_node = std::const_pointer_cast<TrieNode>(curr_node->children_[c]);
        }
    }

    return Trie(root_copy);
}

auto Trie::Remove(std::string_view key) const -> Trie {
    // You should walk through the trie and remove nodes if necessary. If the node doesn't contain a value any more,
    // you should convert it to `TrieNode`. If a node doesn't have children any more, you should remove it.
    // throw "Trie::Remove is not implemented.";
    if (!root_)
        return *this;

    auto clone_remove = [&](auto &&clone_remove, std::shared_ptr<const TrieNode> node, size_t depth) -> std::shared_ptr<TrieNode> {
        if (!node)
            return nullptr;
        std::shared_ptr<TrieNode> new_node = std::shared_ptr<TrieNode>(std::move(node->Clone()));

        if (depth == key.length()) {
            if (new_node->is_value_node_)
                new_node = std::make_shared<TrieNode>(new_node->children_);
        } else {
            char c = key[depth];
            if (new_node->children_.find(c) != new_node->children_.end()) {
                auto cloned_child = clone_remove(clone_remove, new_node->children_[c], depth + 1);
                if (cloned_child)
                    new_node->children_[c] = cloned_child;
                else
                    new_node->children_.erase(c);
            }
        }

        if (new_node->children_.empty() && !new_node->is_value_node_)
            return nullptr;

        return new_node;
    };

    auto new_root = clone_remove(clone_remove, root_, 0);

    return Trie(new_root);
}

// Below are explicit instantiation of template functions.
//
// Generally people would write the implementation of template classes and functions in the header file. However, we
// separate the implementation into a .cpp file to make things clearer. In order to make the compiler know the
// implementation of the template functions, we need to explicitly instantiate them here, so that they can be picked up
// by the linker.

template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint32_t *;

template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint64_t *;

template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const std::string *;

// If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.

using Integer = std::unique_ptr<uint32_t>;

template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const Integer *;

template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;
