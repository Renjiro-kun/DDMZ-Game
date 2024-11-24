#include <pch.h>
#include <Input/InputContextManager.h>


void InputContextManager::Init()
{
    m_CurrentContext = InputContext::Default;
}

void InputContextManager::Shutdown()
{

}