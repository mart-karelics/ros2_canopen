#include <memory>
#include "canopen_device_base.hpp"



namespace ros2_canopen
{
    class MotionControllerDriver : canopen::FiberDriver
    {
    public:
        using FiberDriver::FiberDriver;
        MotionControllerDriver(ev_exec_t *exec, canopen::AsyncMaster &master, uint8_t id) : FiberDriver(exec, master, id)
        {
        }

    private:
        void
        OnBoot(canopen::NmtState state, char es,
               const std::string &whatisit) noexcept override
        {
            // What to do when device signaled that it booted.
        }

        void
        OnConfig(std::function<void(std::error_code ec)> res) noexcept override
        {
            // Seems to be called before or during boot of slave device. Clean up all local data related to slave (mainly registers?).
        }

        void
        OnState(canopen::NmtState state) noexcept override
        {
            // When NmtState of device changes
            switch (state)
            {
            case canopen::NmtState::PREOP:
                break;

            case canopen::NmtState::START:
                break;
            }
        }

        void
        OnRpdoWrite(uint16_t idx, uint8_t subidx) noexcept override
        {
            // Handle data sent via RPDO
        }

        void
        OnEmcy(uint16_t eec, uint8_t er, uint8_t *msef) noexcept override
        {
            // Handle emergency message
        }
    };

    class MotionController : public CANopenDevice
    {
        public:
        void registerDriver(ev_exec_t *exec, canopen::AsyncMaster &master, uint8_t id)
        {
            /// Setup driver
            driver_ = std::make_unique<MotionControllerDriver>(exec, master, id);
        }
        private:
        std::unique_ptr<MotionControllerDriver> driver_;
    };
}

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(ros2_canopen::MotionController, ros2_canopen::CANopenDevice)