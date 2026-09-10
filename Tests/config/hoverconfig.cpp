#include <gtest/gtest.h>
#include "config/config.hpp"

TEST(HoverConfig, DefaultsMatchDesktopHoverAndMaximizedRequirements)
{
	const Config config;
	EXPECT_EQ(config.DesktopAppearance.Accent, ACCENT_ENABLE_TRANSPARENTGRADIENT);
	EXPECT_EQ(config.DesktopAppearance.Color.A, 0);
	EXPECT_TRUE(config.HoveredAppearance.Enabled);
	EXPECT_EQ(config.HoveredAppearance.Accent, ACCENT_ENABLE_ACRYLICBLURBEHIND);
	EXPECT_TRUE(config.MaximisedWindowAppearance.Enabled);
	EXPECT_EQ(config.MaximisedWindowAppearance.Accent, ACCENT_ENABLE_ACRYLICBLURBEHIND);
	EXPECT_FALSE(config.VisibleWindowAppearance.Enabled);
}

TEST(HoverConfig, ReadsHoverAppearanceWithoutOverridingExplicitMaximizedPreference)
{
	rj::GenericDocument<rj::UTF16LE<>> doc;
	doc.Parse(LR"({"hovered_appearance":{"enabled":false,"accent":"acrylic","color":"#10203080"},"maximized_window_appearance":{"enabled":false}})");
	ASSERT_FALSE(doc.HasParseError());
	Config config;
	config.Deserialize(doc);
	EXPECT_FALSE(config.HoveredAppearance.Enabled);
	EXPECT_EQ(config.HoveredAppearance.Color.A, 0x80);
	EXPECT_FALSE(config.MaximisedWindowAppearance.Enabled);
}
