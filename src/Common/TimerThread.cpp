/*
Copyright (C) 2008-2012 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "TimerThread.h"
#include "Timer.h"
#include "TimerContainer.h"
#include "TimeUtilities.h"
#include <chrono>
#include <functional>

namespace Timer {

using std::bind;

Thread * Thread::singleton = nullptr;

Thread::Thread() :
	m_resortTimer(false),
	m_terminate(false),
	m_container(new Container)
{
	m_thread.reset(new std::thread(bind(&Thread::runThread, this)));
}

Thread::~Thread() {
	m_terminate = true;
}

void Thread::registerTimer(Timer *timer) {
	std::unique_lock<std::recursive_mutex> l(m_timersMutex);
	m_resortTimer = true;
	m_timers.push_back(timer);
	m_mainLoopCondition.notify_one();
}

void Thread::removeTimer(Timer *timer) {
	std::unique_lock<std::recursive_mutex> l(m_timersMutex);
	m_timers.remove(timer);
	m_mainLoopCondition.notify_one();
}

bool less_than (const Timer *t1, const Timer *t2) {
	return (t1->getRunAt() < t2->getRunAt());
}

Timer * Thread::findMin() {
	// Unsynchronized
	if (m_timers.size() == 0) {
		return nullptr;
	}

	if (m_resortTimer) {
		m_timers.sort(less_than);
		m_resortTimer = false;
	}

	return *m_timers.begin();
}

void Thread::forceReSort() {
	std::unique_lock<std::recursive_mutex> l(m_timersMutex);
	m_resortTimer = true;
	m_mainLoopCondition.notify_one();
}

void Thread::runThread() {
	std::unique_lock<std::recursive_mutex> l(m_timersMutex);
	while (!m_terminate) {
		// Find minimum wakeup time
		Timer *minTimer = findMin();
		// Be certain the time stays in milliseconds
		int64_t msec = (minTimer == nullptr) ? 1000000000 : minTimer->getRunAt() - TimeUtilities::getTickCount();
		if (msec <= 0) {
			minTimer->run();
			continue;
		}

		if (m_mainLoopCondition.wait_for(l, std::chrono::milliseconds(msec))) {
			continue;
		}

		if (minTimer != nullptr) {
			minTimer->run();
		}
	}
}

}