#pragma once
#include <array>
#include <string>
#include <vector>


struct InventoryItem
{
    size_t Id;
    std::string name;
    std::string description;
};


class InventoryManager
{
public:
    static InventoryManager& GetInstance()
    {
        static InventoryManager instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    void AddItem(size_t id) { m_PlayerItems.push_back(id); }
    bool HasItem(size_t id);
    void UseItem(size_t id);
    InventoryItem& GetItemInfo(size_t id);

    const std::vector<size_t>& GetPlayerItems() { return m_PlayerItems; }

private:
    InventoryManager() = default;
    ~InventoryManager() = default;
    InventoryManager(const InventoryManager&) = delete;
    InventoryManager& operator=(const InventoryManager&) = delete;
private:
    std::array<InventoryItem, 2> m_AvailableItems
    {
        InventoryItem{0, "Invalid item", ""},
        InventoryItem{1, "Test key", "Key description"}
    };

    std::vector<size_t> m_PlayerItems;
};