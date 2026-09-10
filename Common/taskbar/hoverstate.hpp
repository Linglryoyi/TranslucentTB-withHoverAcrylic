#pragma once
#include <chrono>

// One instance per taskbar. Time is supplied by the caller so debounce can be
// tested without sleeping or depending on the Windows message queue.
class TaskbarHoverState {
public:
	using Clock = std::chrono::steady_clock;
	static constexpr auto EnterDelay = std::chrono::milliseconds(40);
	static constexpr auto LeaveDelay = std::chrono::milliseconds(80);

	bool Update(bool inside, Clock::time_point now) noexcept
	{
		if (inside != m_Candidate)
		{
			m_Candidate = inside;
			m_CandidateSince = now;
		}

		if (m_Hovered != m_Candidate && now - m_CandidateSince >= (inside ? EnterDelay : LeaveDelay))
		{
			m_Hovered = m_Candidate;
			return true;
		}
		return false;
	}

	bool Hovered() const noexcept { return m_Hovered; }

private:
	bool m_Hovered = false;
	bool m_Candidate = false;
	Clock::time_point m_CandidateSince = {};
};
