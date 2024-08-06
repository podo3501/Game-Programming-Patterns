#include "VirtualMachine.h"

#include <sstream>

Wizard::Wizard(int health, int agility, int wisdom) :
	m_health{ health },
    m_agility{ agility },
    m_wisdom{ wisdom }
{}

int Wizard::GetHealth() { return m_health; }
int Wizard::GetAgility() { return m_agility; }
int Wizard::GetWisdom() { return m_wisdom; }

void Wizard::SetHealth(int health) { m_health = health; }

///////////////////////////////////////////////////////////////////

std::vector<std::string> Split(std::string str, char Delimiter) {
    std::istringstream iss(str);
    std::string buffer;

    std::vector<std::string> result;

    while (std::getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);
    }

    return result;
}

Wizard wizardAlly(45, 7, 11);
Wizard wizardEnemy(32, 4, 7);

Wizard* GetWizard(int idxWizard)
{
    if (idxWizard == 0)
        return &wizardAlly;
    else if (idxWizard == 1)
        return &wizardEnemy;

    return nullptr;
}

int GetHealth(int idxWizard)
{
    Wizard* wizard = GetWizard(idxWizard);
    if (wizard == nullptr)
        return 0;

    return wizard->GetHealth();
}

int GetAgility(int idxWizard)
{
    Wizard* wizard = GetWizard(idxWizard);
    if (wizard == nullptr)
        return 0;

    return wizard->GetAgility();
}

int GetWisdom(int idxWizard)
{
    Wizard* wizard = GetWizard(idxWizard);
    if (wizard == nullptr)
        return 0;

    return wizard->GetWisdom();
}

void SetHealth(int idxWizard, int health)
{
    Wizard* wizard = GetWizard(idxWizard);
    if (wizard == nullptr)
        return;

    wizard->SetHealth(health);
}

enum Instruction
{
    INST_NONE,
    INST_LITERAL,
    INST_ADD,
    INST_DIVIDE,
    INST_SET_HEALTH,
    INST_GET_HEALTH,
    INST_GET_AGILITY,
    INST_GET_WISDOM,
};

Instruction GetInstruction(const std::string& strInstruction)
{
    if (strInstruction == "LITERAL") return INST_LITERAL;
    if (strInstruction == "ADD") return INST_ADD;
    if (strInstruction == "DIVIDE") return INST_DIVIDE;
    if (strInstruction == "SET_HEALTH") return INST_SET_HEALTH;
    if (strInstruction == "GET_HEALTH") return INST_GET_HEALTH;
    if (strInstruction == "GET_AGILITY") return INST_GET_AGILITY;
    if (strInstruction == "GET_WISDOM") return INST_GET_WISDOM;

    return INST_NONE;
}

VM::VM()
{}

int VM::Pop()
{
    int value = m_stack.top();
    m_stack.pop();

    return value;
}

void VM::Push(int value)
{
    m_stack.push(value);
}

void VM::Excute(std::vector<std::string> cmdList)
{
	for (auto strCmd : cmdList)
	{
        auto cmd = Split(strCmd, ' ');
        if (cmd.empty())
            break;

        auto instruction = GetInstruction(cmd[0]);

        switch (instruction)
        {
        case INST_LITERAL:
            Push(std::stoi(cmd[1]));
            break;
        case INST_ADD: {
            int b = Pop();
            int a = Pop();
            Push(a + b);
            break; }
        case INST_DIVIDE: {
            int b = Pop();
            int a = Pop();
            Push(a / b);
            break; }
        case INST_SET_HEALTH: {
            int health = Pop();
            int wizard = Pop();
            SetHealth(wizard, health);
            break; }
        case INST_GET_HEALTH: {
            int wizard = Pop();
            Push(GetHealth(wizard));
            break; }
        case INST_GET_AGILITY: {
            int wizard = Pop();
            Push(GetAgility(wizard));
            break; }
        case INST_GET_WISDOM: {
            int wizard = Pop();
            Push(GetWisdom(wizard));
            break; }
        }
	}
}

