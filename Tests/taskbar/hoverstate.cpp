#include <gtest/gtest.h>
#include "taskbar/hoverstate.hpp"

using namespace std::chrono_literals;

TEST(TaskbarHover, ConfirmsEntryAndExitWithDifferentDelays)
{
	TaskbarHoverState hover;
	const auto t = TaskbarHoverState::Clock::time_point{};
	EXPECT_FALSE(hover.Update(true, t));
	EXPECT_FALSE(hover.Update(true, t + 39ms));
	EXPECT_TRUE(hover.Update(true, t + 40ms));
	EXPECT_TRUE(hover.Hovered());
	EXPECT_FALSE(hover.Update(false, t + 50ms));
	EXPECT_FALSE(hover.Update(false, t + 129ms));
	EXPECT_TRUE(hover.Update(false, t + 130ms));
	EXPECT_FALSE(hover.Hovered());
	EXPECT_FALSE(hover.Update(false, t + 1s));
}

TEST(TaskbarHover, RejectsBoundaryJitterAndCancelsPendingLeave)
{
	TaskbarHoverState hover;
	const auto t = TaskbarHoverState::Clock::time_point{};
	EXPECT_FALSE(hover.Update(true, t));
	EXPECT_FALSE(hover.Update(false, t + 30ms));
	EXPECT_FALSE(hover.Update(true, t + 40ms));
	EXPECT_FALSE(hover.Update(true, t + 60ms));
	EXPECT_TRUE(hover.Update(true, t + 80ms));
	EXPECT_FALSE(hover.Update(false, t + 100ms));
	EXPECT_FALSE(hover.Update(true, t + 150ms));
	EXPECT_FALSE(hover.Update(true, t + 300ms));
	EXPECT_TRUE(hover.Hovered());
}

TEST(TaskbarHover, TaskbarsAreIndependentAndRecreationStartsClear)
{
	TaskbarHoverState primary, secondary;
	const auto t = TaskbarHoverState::Clock::time_point{};
	primary.Update(true, t);
	EXPECT_TRUE(primary.Update(true, t + 40ms));
	EXPECT_FALSE(secondary.Update(false, t + 40ms));
	EXPECT_TRUE(primary.Hovered());
	EXPECT_FALSE(secondary.Hovered());
	primary = {};
	EXPECT_FALSE(primary.Hovered());
	EXPECT_FALSE(primary.Update(true, t + 1s));
	EXPECT_TRUE(primary.Update(true, t + 1040ms));
}
