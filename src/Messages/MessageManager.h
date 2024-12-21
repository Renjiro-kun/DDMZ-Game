#pragma once
#include <raylib/raylib.h>
#include <vector>
#include <string>
#include <fstream>
#include <Input/InputContextManager.h>

struct Message
{
    short ID;
    std::string Message;
};

enum class SystemMessageType : char
{
    Default = 0,
    Blocking = 1,
    Timed = 2,
    Interactive = 3
};

enum class SystemMessageID : uint16_t
{
    SaveData = 0,
    LoadData = 1,
    FoundItem = 2,
    SaveFailed = 3,
    LoadFailed = 4,
    ResponseYes = 5,
    ResponseNo = 6,
    EmptyChest = 7,
    ItemRequired = 8
};

class MessageManager
{
public:
    static MessageManager& GetInstance()
    {
        static MessageManager instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    void Update();
    void OnDraw2D();
    template<typename... Args>
    void RequestSystemMessage(SystemMessageID messageID, SystemMessageType type = SystemMessageType::Default, float time = 0.15f, Args... args)
    {
        if(!m_DialogRequested)
        {
            m_DialogRequested = true;
            SetRequestedMessage(static_cast<uint16_t>(messageID), args...);
            InputContextManager::GetInstance().SetInputContext(InputContext::Message);
        }
    }

private:
    template<typename... Args>
    void SetRequestedMessage(uint16 messageID, Args... args)
    {
        for (size_t i = 0; i < m_SystemMessages.size(); i++)
        {
            if(m_SystemMessages[i].ID == messageID)
            {
                m_RequestedString = TextFormat(m_SystemMessages[i].Message.c_str(), args...);
                return;
            }
        }
        m_RequestedString = TextFormat("Message %d not found", messageID);
    }

    void ReadScriptIntoMemory(std::ifstream& file, std::vector<Message>& sourceArray);
private:
    MessageManager() = default;
    ~MessageManager() = default;
    MessageManager(const MessageManager&) = delete;
    MessageManager& operator=(const MessageManager&) = delete;
private:
    const int16_t DIALOGBOX_TILES = 3;
    Font m_MsgFont;
    Texture2D* m_DialogBoxTextures;
    bool m_DialogRequested;
    std::string m_RequestedString;
    std::vector<Message> m_SystemMessages;
};