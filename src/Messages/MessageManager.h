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

    void Request(uint16_t messageID);

private:
    void SetRequestedMessage(uint16 messageID);
    void ReadScriptIntoMemory(std::ifstream& file);
private:
    MessageManager() = default;
    ~MessageManager() = default;
    MessageManager(const MessageManager&) = delete;
    MessageManager& operator=(const MessageManager&) = delete;
private:
    const int16_t DIALOGBOX_TILES = 3;
    Texture2D* m_DialogBoxTextures;
    bool m_DialogRequested;
    std::string m_RequestedString;
    std::vector<Message> m_LoadedMessage;
};