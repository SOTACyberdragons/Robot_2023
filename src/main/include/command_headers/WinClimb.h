#ifndef WIN_CLIMB
#define WIN_CLIMB

#include <math.h>
#include <chrono>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/voltage.h>

#include "subsystem_headers/Drivetrain.h"

namespace cb
{
    using namespace std::chrono;
    using namespace std::chrono_literals;

    // Sliding window. This can be used to (a) smooth a series of unstable
    // values, (b) find the previous value over the window size, and (c)
    // provide a moving delta. Note that if you want previous values or deltas
    // over smoothed values, you must use TWO DIFFERENT INSTANCES. Example:
    //
    //      Window w_smoothing(100); // smooth over 100 samples
    //      Window w_deltas(10);     // deltas over 10 smoothed values
    //      ...
    //      current = get_unstable_value();
    //      w_smoothing::Insert(x);
    //      smooth = w_smoothing::Mean();
    //      w_deltas::Insert(smooth);
    //      delta = w_deltas::Delta();
    //
    class Window
    {
        public:
            Window(int size): size_(size), sum_(0), window_(size, 0) { }

            // Set all values to zero.
            void Clear() { 
                std::fill(window_.begin(), window_.end(), 0);
            }

            // Insert new value into window.
            void Insert(double value)
            {
                sum_ += value - window_[index_]; // difference between new and old
                window_[index_] = value;        // update value at index
                index_ = next_index();          // bump index mod size
            }
            // The mean value over the window.
            double Mean() const
            {
                return sum_ / size_;
            }
            // The previous value over the window.
            double Oldest() const
            {
                return window_[index_];
            }
        private:
            int next_index() { return (index_ + 1) % size_; }
            int size_;   // number of elements held in window
            int index_;  // current index into window: 0 <= index_ < size_
            double sum_; // sum of all elements in window
            std::vector<double> window_;
    };

/*
There are 2 states of climbing: getting onto the ramp and then driving to the middle.
A change in the roll of the gyro of more than 0.3 signifies a change, the first one being 
when the backside of the ramp goes up, and the second one being when the robot rotates down to the 
middle. The command ends when the 2nd change happens
*/

    class WinClimb
        : public frc2::CommandHelper<frc2::CommandBase, WinClimb>
    {
    private:
        // Roll smoothing and delta.
        // Timings in the comments assume 10 msec / execute cycle.
        // TODO: Validate these window sizes in the field. They need not be the same.
        Window m_rollSmoothWindow { 10 }; // Smooth over 10 cycles = 100 msec = 0.1 seconds.
        Window m_rollHistoryWindow { 10 };  // Delta  over 10 cycles = 100 msec = 0.1 seconds.

        // Robot states for the climbing command.
        enum class State
        {
            Approach, // on the flat, approaching the ramp
            Ascend,   // climbing the ramp
            Balance,  // on top of the ramp
            Clear,    // leaving the ramp for another attempt
            Orient,   // turning to face the ramp after clearing
        };
        State m_state;

        // Robot direction of travel.
        enum class Direction
        {
            Forward,  // moving in the direction of the "mouth"
            Backward, // moving in the direction of the "arm"
        };
        Direction m_direction;

        double m_minRoll = 0, m_maxRoll = 0;

        units::meter_t m_yCoord = 0_m, m_goal = 0_m;

        double m_deltaRoll = 0;
        double m_lastRoll = 0;

        bool m_onRamp = false;
        bool m_isFinished = false;

        units::volt_t m_voltage = 0_V;

        //Point in time when robot moved onto the ramp
        time_point<high_resolution_clock> m_rampTime;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool) override;
    public:
        void setGoal(units::meter_t meters);
        WinClimb(units::meter_t meters);
    };
}

#endif //WIN_CLIMB