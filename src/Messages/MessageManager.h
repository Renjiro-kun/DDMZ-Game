#pragma once
#include <raylib/raylib.h>
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

    void Request();

private:
    MessageManager() = default;
    ~MessageManager() = default;
    MessageManager(const MessageManager&) = delete;
    MessageManager& operator=(const MessageManager&) = delete;
private:
    const int16_t DIALOGBOX_TILES = 3;
    Texture2D* m_DialogBoxTextures;
    bool m_DialogRequested;
};