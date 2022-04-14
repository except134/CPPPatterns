#pragma once

/*
Задача: использовать паттерн «Посредник» для организации взаимодействия каких-либо
объектов в игре.
*/

// Взаимодействие танка с ГУИ через посредника.

/*
Паттерн «Посредник» мог бы использоваться для организации текстового чата между
игроками по сети. Но для этого необходимо довольно сложное сетевое взаимодействие.
Поэтому упростим задачу.
Предположим, что объекты «Танки» обладают искусственным интеллектом и нужно сделать
так, чтобы они могли посылать текстовые сообщения на экран пользователя: например,
шуточные угрозы для самолёта, который их атакует.
*/

// Tank::SendMessage() const;

/*
Необходимо сделать в классе LevelGUI очередь полученных сообщений для вывода на
экран. 
*/

//    В AbstractLevelGUI std::queue<TankMessage> messages{};

/*
Ставить сообщения в очередь будет объект класса Mediator. 
*/

// Mediator::SendMessage(std::unique_ptr<TankMessage>&& mes);

/*
Он же будет находиться в каждом объекте «Танк» (можно сделать поле статическим указателем). 
*/

// В Tank std::shared_ptr<Mediator> mediator;

/*
При рисовании
танка будем бросать кубик и с определённой вероятностью посылать какое-либо
сообщение для пилота самолёта (пользователя) через посредника объекту LevelGUI.
*/

// В Tank::Draw вызывается Tank::SendMessage, в котором по рандому выбирается фраза и отдается посреднику
// Mediator::SendMessage, который в свою очередь отсылает объекту AbstractLevelGUI через
// AbstractLevelGUI::AddMessage

/*
При рисовании GUI через LevelGUI::Draw() будем извлекать первое сообщение из очереди и
выводить его на нижнюю часть экрана какое-то небольшое время (3-5 сек). После чего
извлекаем следующее сообщение из очереди.
*/
// В LevelGUI1::Draw() const и LevelGUI2::Draw() const пишется на экран текущая фраза, которая устанавливается
// по рандому в AbstractLevelGUI::ChangeMessage()

// В самом SBomber создается посредник std::shared_ptr<Mediator> mediator, который передается экземалярам танков
// 
//    std::shared_ptr<Tank> pTank1 = std::make_shared<Tank>(mediator);
//    std::shared_ptr<Tank> pTank2 = std::make_shared<Tank>(mediator);
//
// ну и в итоге в SBomber::DrawFrame() вызываем метод AbstractLevelGUI::ChangeMessage()
//
// Так что все сделано по тех. заданию в дом. задании :) 
// Оценку можно исправлять :)


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

