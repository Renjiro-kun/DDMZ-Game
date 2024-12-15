#include <Defines.h>
#include <Messages/MessageManager.h>
#include <Input/InputContextManager.h>

void MessageManager::Init()
{
    m_DialogBoxTextures = new Texture2D[DIALOGBOX_TILES];
    for (size_t i = 0; i < DIALOGBOX_TILES; i++)
    {
        m_DialogBoxTextures[i] = LoadTexture(TextFormat("/rd/dlgbox%0i.png", i+1));
    }
    m_MsgFont = LoadFont("/rd/font_ui.png");
    std::ifstream file("/rd/msg_system.scr", std::ios::binary);
	if (!file)
	{
		// error handling
	}
    ReadScriptIntoMemory(file, m_SystemMessages);
}

void MessageManager::Shutdown()
{
    m_DialogRequested = false;
    for (size_t i = 0; i < DIALOGBOX_TILES; i++)
    {
        UnloadTexture(m_DialogBoxTextures[i]);
    }
    delete[] m_DialogBoxTextures;
}

void MessageManager::ReadScriptIntoMemory(std::ifstream& file, std::vector<Message>& sourceRepository)
{
    char header[4];
    file.read(header, sizeof(char)*4);
    char type;
    file.read(&type, sizeof(char));
    uint16_t size = 0;
    file.read((char*)&size, sizeof(uint16_t));
    sourceRepository.reserve(size);
    for (size_t i = 0; i < size; i++)
    {
        Message msg;
        file.read((char*)&msg.ID, sizeof(short));
        char msgType = 0;
        file.read(&msgType, sizeof(char));
        char lenght = 0;
        file.read(&lenght, sizeof(char));
        char* tempStr = new char[lenght];
        file.read(tempStr, sizeof(char)*lenght);
        msg.Message = tempStr;
        sourceRepository.push_back(msg);
        delete[] tempStr;
    }   
}

void MessageManager::OnDraw2D()
{
    if(m_DialogRequested)
    {
        for (size_t i = 0; i < DIALOGBOX_TILES; i++)
        {
            DrawTexture(m_DialogBoxTextures[i], i * 256, HEIGHT-256, WHITE);
        }
        //DrawText(m_RequestedString.c_str(), 0, 256, 32, BLACK);
        DrawTextEx(m_MsgFont, m_RequestedString.c_str(), Vector2{31, HEIGHT-161}, 32, 1, BLACK);
    }
}

void MessageManager::RequestSystemMessage(SystemMessageID messageID, SystemMessageType type, float time)
{
    if(!m_DialogRequested)
    {
        m_DialogRequested = true;
        SetRequestedMessage(static_cast<uint16_t>(messageID));
        InputContextManager::GetInstance().SetInputContext(InputContext::Message);
    }
}

void MessageManager::SetRequestedMessage(uint16_t messageID)
{
    for (size_t i = 0; i < m_SystemMessages.size(); i++)
    {
        if(m_SystemMessages[i].ID == messageID)
        {
            m_RequestedString = m_SystemMessages[i].Message;
            return;
        }
    }
    m_RequestedString = TextFormat("Message %d not found", messageID);
}

void MessageManager::Update()
{
    if(IsGamepadAvailable(0) && InputContextManager::GetInstance().CurrentInputComtext() == InputContext::Message)
    {
        if(m_DialogRequested && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        {
            m_DialogRequested = false;
            InputContextManager::GetInstance().SetInputContext(InputContext::Default);
        }
    }
}