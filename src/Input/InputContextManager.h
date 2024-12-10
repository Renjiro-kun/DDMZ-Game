#pragma once

enum class InputContext : unsigned char
{
    Default = 0,
    Message = 1,
    PauseMenu = 2,
    Invalid = 254
};

class InputContextManager
{
public:
    static InputContextManager& GetInstance()
    {
        static InputContextManager instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    InputContext CurrentInputComtext() { return m_CurrentContext; }
    void SetInputContext(InputContext context) 
    {
        m_PreviousContext = m_CurrentContext;
        m_CurrentContext = context;
    } 
    
    void RestoreContext() 
    {
        if(m_PreviousContext != InputContext::Invalid)
            m_CurrentContext = m_PreviousContext; 
    }

private:
    InputContextManager() = default;
    ~InputContextManager() = default;
    InputContextManager(const InputContextManager&) = delete;
    InputContextManager& operator=(const InputContextManager&) = delete;
private:
    InputContext m_CurrentContext = InputContext::Invalid;
    InputContext m_PreviousContext = InputContext::Invalid;
};