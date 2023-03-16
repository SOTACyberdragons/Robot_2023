#include <chrono>
#include <functional>
#include <iostream>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/SubsystemBase.h>

namespace cb {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    class TimedCommand 
      : public frc2::CommandHelper<frc2::CommandBase, TimedCommand>  
    {
    private:
        frc2::Subsystem* m_base;

        high_resolution_clock::time_point m_startTime;

        milliseconds m_time = 0ms;

        std::function<void()> m_initialize, m_execute, m_end;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool override);
    public:
        TimedCommand(frc2::Subsystem* base, std::function<void()> initialize, std::function<void()> execute, std::function<void()> end, milliseconds time);
    };
}