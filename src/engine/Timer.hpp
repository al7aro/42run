#pragma once

#include <chrono>

namespace FT {
    class Timer
    {
    private:
        std::chrono::steady_clock::time_point _start;
        std::chrono::steady_clock::time_point _end;
        bool _running;
    public:
        Timer(bool start = true)
            : _start(std::chrono::steady_clock::now()),
             _end(std::chrono::steady_clock::now()), _running(start)
        {
        }
        void Start()
        {
			this->_running = true;
            this->_start = std::chrono::steady_clock::now();
            this->_end = std::chrono::steady_clock::now();
        }
        void Stop()
        {
            this->_running = false;
			this->_end = std::chrono::steady_clock::now();
        }
        float EllapsedMiliseconds() const
        {
            std::chrono::steady_clock::time_point end;
			if (!this->_running)
				end = this->_end;
            else
                end = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsed_seconds(end - this->_start);
            return (static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - this->_start).count()));
        }
        float EllapsedSeconds() const
        {
            return (this->EllapsedMiliseconds() / 1000.0f);
        }
    };
}
