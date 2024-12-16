#pragma once
#include <raylib/raylib.h>
#include <vector>
#include <string>
#include <fstream>

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
    FoundItem = 2
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

    void RequestSystemMessage(SystemMessageID messageID, SystemMessageType type = SystemMessageType::Default, float time = 0.15f);

private:
    void SetRequestedMessage(uint16 messageID);
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