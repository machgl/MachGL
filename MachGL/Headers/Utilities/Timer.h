#pragma once

#include "../Core/Includes.h"

namespace MachGL {

	class Timer {

		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;
			bool m_running = false;
			double m_lastTime;
			double m_timer;
			double m_nowTime = 0;
			int m_frameCount = 0;
			double m_frameTimeCount = 0;

			void start() {

				m_startTime = std::chrono::high_resolution_clock::now();
				m_running = true;
			}

			void stop() {

				m_endTime = std::chrono::high_resolution_clock::now();
				m_running = false;
			}

		public:	
			
			Timer() {
				start();
				m_lastTime = elapsedTimeSeconds();
				m_timer = m_lastTime;
			}

			~Timer() {
				stop();
			}

			void reset() {

				m_startTime = std::chrono::high_resolution_clock::now();
			}

			const double& elapsedTime() const {

				std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

				if (m_running)
					endTime = std::chrono::high_resolution_clock::now();
				else
					endTime = m_endTime;

				return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime).count();
			}

			const double& elapsedTimeMilliseconds() const {

				return elapsedTime() / 1000000;
			}

			const double& elapsedTimeSeconds() const {

				return elapsedTime() / 1000000000;
			}

			void getFPS() {

				m_nowTime = elapsedTimeSeconds();
				m_frameTimeCount += (m_nowTime - m_lastTime);
				m_lastTime = m_nowTime;
				m_frameCount++;

				if (elapsedTimeSeconds() - m_timer > 1.0) {

					m_timer++;
					std::cout << "FPS: " << m_frameCount << " | Avg. frame time: " << (m_frameTimeCount / (double) m_frameCount) * 1000 << "ms" << std::endl;	
					m_frameCount = 0;
					m_frameTimeCount = 0;
				}
			}
	};
}
