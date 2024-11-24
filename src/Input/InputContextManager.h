#pragma once

enum class InputContext : unsigned char
{
    Default = 0,
    Message = 1,
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
    void SetInputContext(InputContext context) { m_CurrentContext = context; } 

private:
    InputContextManager() = default;
    ~InputContextManager() = default;
    InputContextManager(const InputContextManager&) = delete;
    InputContextManager& operator=(const InputContextManager&) = delete;
private:
    InputContext m_CurrentContext = InputContext::Invalid;
};