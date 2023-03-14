#include <chrono>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

namespace cb {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    class Wait : public frc2::CommandHelper<frc2::CommandBase, Wait> {
    private:
        high_resolution_clock::time_point m_startTime; 
        milliseconds m_waitTime;

        void Initialize() override;
        bool IsFinished() override;
    public:
        //# of seconds to wait
        Wait(milliseconds waitTime);
    };
}