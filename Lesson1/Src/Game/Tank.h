#pragma once

/*
������: ������������ ������� ���������� ��� ����������� �������������� �����-����
�������� � ����.
*/

// �������������� ����� � ��� ����� ����������.

/*
������� ���������� ��� �� �������������� ��� ����������� ���������� ���� �����
�������� �� ����. �� ��� ����� ���������� �������� ������� ������� ��������������.
������� �������� ������.
�����������, ��� ������� ������ �������� ������������� ����������� � ����� �������
���, ����� ��� ����� �������� ��������� ��������� �� ����� ������������: ��������,
�������� ������ ��� �������, ������� �� �������.
*/

// Tank::SendMessage() const;

/*
���������� ������� � ������ LevelGUI ������� ���������� ��������� ��� ������ ��
�����. 
*/

//    � AbstractLevelGUI std::queue<TankMessage> messages{};

/*
������� ��������� � ������� ����� ������ ������ Mediator. 
*/

// Mediator::SendMessage(std::unique_ptr<TankMessage>&& mes);

/*
�� �� ����� ���������� � ������ ������� ����� (����� ������� ���� ����������� ����������). 
*/

// � Tank std::shared_ptr<Mediator> mediator;

/*
��� ���������
����� ����� ������� ����� � � ����������� ������������ �������� �����-����
��������� ��� ������ ������� (������������) ����� ���������� ������� LevelGUI.
*/

// � Tank::Draw ���������� Tank::SendMessage, � ������� �� ������� ���������� ����� � �������� ����������
// Mediator::SendMessage, ������� � ���� ������� �������� ������� AbstractLevelGUI �����
// AbstractLevelGUI::AddMessage

/*
��� ��������� GUI ����� LevelGUI::Draw() ����� ��������� ������ ��������� �� ������� �
�������� ��� �� ������ ����� ������ �����-�� ��������� ����� (3-5 ���). ����� ����
��������� ��������� ��������� �� �������.
*/
// � LevelGUI1::Draw() const � LevelGUI2::Draw() const ������� �� ����� ������� �����, ������� ���������������
// �� ������� � AbstractLevelGUI::ChangeMessage()

// � ����� SBomber ��������� ��������� std::shared_ptr<Mediator> mediator, ������� ���������� ����������� ������
// 
//    std::shared_ptr<Tank> pTank1 = std::make_shared<Tank>(mediator);
//    std::shared_ptr<Tank> pTank2 = std::make_shared<Tank>(mediator);
//
// �� � � ����� � SBomber::DrawFrame() �������� ����� AbstractLevelGUI::ChangeMessage()
//
// ��� ��� ��� ������� �� ���. ������� � ���. ������� :) 
// ������ ����� ���������� :)


class Tank : public DestroyableGroundObject
{
public:
    Tank(std::shared_ptr<Mediator> med) : 
        mediator(med)
    {
    }

    bool IsInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override
    {
        return score;
    }

    void Draw() const override;
    void SendMessage() const;

private:
    const uint16_t score = 30;
    std::shared_ptr<Mediator> mediator;
    static std::vector<std::string> messages;
};

